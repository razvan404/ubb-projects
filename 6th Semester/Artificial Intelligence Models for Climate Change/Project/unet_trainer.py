import numpy as np
import torch
import torch.nn as nn
import torch.optim as optim
from torch.nn.modules.loss import _Loss
from torch.utils.data import DataLoader

import tqdm
import wandb
from dataloader import flame_dataset_splits
from metrics import ImageMetrics

from unet import SegmentationUNet
from model_saver import ModelSaver
from utils import binary_predictions, multiclass_predictions


class UNetTrainer:
    @classmethod
    def _compute_metrics(cls, targets: np.ndarray, preds: np.ndarray):
        conf_matrix = ImageMetrics.confusion_matrix(targets, preds)
        mpa = ImageMetrics.mean_pixels_accuracy(conf_matrix=conf_matrix)
        iou = ImageMetrics.intersection_over_union(conf_matrix=conf_matrix)
        fwiou = ImageMetrics.frequency_weighted_intersection_over_union(
            conf_matrix=conf_matrix
        )
        return mpa, iou, fwiou

    @classmethod
    def _train_step(
        cls,
        model: nn.Module,
        dataloader: DataLoader,
        loss_function: _Loss,
        optimizer: torch.optim.Optimizer,
        scaler: torch.cuda.amp.GradScaler | None,
        device: torch.device,
        desc: str = None,
    ):
        model.train()
        loader = tqdm.tqdm(dataloader, desc)
        total_loss = 0.0

        for images, masks in loader:
            images = images.to(device)
            masks = masks.to(device)

            # forward
            preds = model(images)
            loss = loss_function(preds, masks)

            # backward
            optimizer.zero_grad()
            if scaler is not None:
                scaler.scale(loss).backward()
                scaler.step(optimizer)
                scaler.update()
            else:
                loss.backward()
                optimizer.step()
            loss = loss.cpu().item()
            loader.set_postfix(loss=loss)
            total_loss += loss

        total_loss /= len(loader)
        return total_loss

    @classmethod
    def _validate_step(
        cls,
        model: nn.Module,
        dataloader: DataLoader,
        loss_function: _Loss,
        predictions_function: callable,
        device: torch.device,
        desc: str = None,
    ):
        model.eval()
        loader = tqdm.tqdm(dataloader, desc)
        total_loss = 0.0
        targets = []
        predictions = []

        for images, masks in loader:
            images = images.to(device)
            masks = masks.to(device)

            # forward
            preds = model(images)
            loss = loss_function(preds, masks)
            loss = loss.cpu().item()

            preds = predictions_function(preds.cpu().detach()).numpy()
            masks = masks.cpu().numpy()
            mpa, iou, fwiou = cls._compute_metrics(masks, preds)

            loader.set_postfix(loss=loss, mpa=mpa, miou=iou, fwiou=fwiou)
            total_loss += loss

            targets.append(masks)
            predictions.append(preds)

        total_loss /= len(loader)
        targets = np.concatenate(targets, axis=0)
        predictions = np.concatenate(predictions, axis=0)
        mpa, iou, fwiou = cls._compute_metrics(targets, predictions)

        return total_loss, mpa, iou, fwiou

    @classmethod
    def _predictions_table(
        cls,
        model: nn.Module,
        dataloader: DataLoader,
        predictions_function: callable,
        device: torch.device,
    ):
        model.eval()
        sample_images, sample_masks = next(iter(dataloader))
        preds = model(sample_images.to(device))
        preds = predictions_function(preds)

        table = wandb.Table(columns=["Image", "True Mask", "Predicted Mask"])
        for img, true_mask, pred_mask in zip(sample_images, sample_masks, preds):
            table.add_data(
                wandb.Image(img), wandb.Image(true_mask), wandb.Image(pred_mask)
            )
        return table

    @classmethod
    def train(cls, wandb_config=None):
        with wandb.init(config=wandb_config):
            wandb_config = wandb.config
            device = (
                torch.device("cuda")
                if torch.cuda.is_available()
                else torch.device("cpu")
            )

            seed = wandb_config["seed"]
            resolution = wandb_config["resolution"]
            num_epochs = wandb_config["num_epochs"]
            batch_size = wandb_config["batch_size"]
            in_channels = wandb_config["in_channels"]
            out_channels = wandb_config["out_channels"]
            learning_rate = wandb_config["learning_rate"]

            print("=== Run Configuration ===")

            print(f"{device = }")
            print(f"{seed = }")
            print(f"{resolution = }")

            print(f"{num_epochs = }")
            print(f"{batch_size = }")
            print(f"{in_channels = }")
            print(f"{out_channels = }")
            print(f"{learning_rate = }")

            torch.manual_seed(seed)

            train_dataset, validation_dataset = flame_dataset_splits(
                "dataset", work_resolution=resolution
            )
            train_dataloader = DataLoader(
                train_dataset, batch_size=batch_size, shuffle=True
            )
            validation_dataloader = DataLoader(
                validation_dataset, batch_size=8, shuffle=False
            )

            model = SegmentationUNet(in_channels, out_channels).to(device)
            loss_function = nn.BCEWithLogitsLoss()
            if out_channels == 1:
                predictions_function = binary_predictions
            else:
                predictions_function = multiclass_predictions
            optimizer = optim.Adam(model.parameters(), lr=learning_rate)
            scaler = torch.cuda.amp.GradScaler() if torch.cuda.is_available() else None
            saver = ModelSaver("saved_models", wandb_config)

            for epoch in range(num_epochs):
                train_loss = cls._train_step(
                    model,
                    train_dataloader,
                    loss_function,
                    optimizer,
                    scaler,
                    device,
                    f"Epoch {epoch} - Train",
                )
                val_loss, mpa, iou, fwiou = cls._validate_step(
                    model,
                    validation_dataloader,
                    loss_function,
                    predictions_function,
                    device,
                    f"Epoch {epoch} - Validation",
                )
                saver.save(model, f"checkpoint_{epoch}.pt")

                table = cls._predictions_table(
                    model, validation_dataloader, predictions_function, device
                )
                log_data = {
                    "train_loss": train_loss,
                    "val_loss": val_loss,
                    "mean_pixels_accuracy": mpa,
                    "intersection_over_union": iou,
                    "frequency_weighted_intersection_over_union": fwiou,
                    f"predictions_table_epoch{epoch}": table,
                }
                wandb.log(log_data)
                print(
                    f"Epoch {epoch}: Train Loss: {train_loss:.4f} | Validation Loss: {val_loss:.4f}"
                    f" | MPA: {mpa:.4f} | MIoU: {iou:.4f} | FWIoU: {fwiou:.4f}"
                )
