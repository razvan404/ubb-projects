import os.path

import numpy as np
import torch
import torch.nn as nn
import torch.optim as optim
import tqdm
import wandb

from torch.utils.data import DataLoader

from core.config import load_config
from segmentation.utils import (
    get_dataloaders,
    binary_predictions,
    load_checkpoint,
    save_checkpoint,
    save_to_binaries,
)
from segmentation.metrics import (
    frequency_weighted_intersection_over_union,
    mean_pixels_accuracy,
    intersection_over_union,
    confusion_matrix,
)
from segmentation.model import SegmentationUNet
from segmentation.visualizer import Visualizer


def compute_metrics(targets: np.ndarray, preds: np.ndarray):
    conf_matrix = confusion_matrix(targets, preds)
    mpa = mean_pixels_accuracy(conf_matrix=conf_matrix)
    iou = intersection_over_union(conf_matrix=conf_matrix)
    fwiou = frequency_weighted_intersection_over_union(conf_matrix=conf_matrix)
    return mpa, iou, fwiou


def train_step(
    loader: DataLoader,
    model: nn.Module,
    optimizer,
    loss_function: callable,
    predictions_function: callable,
    scaler,
    device: str,
    desc: str = None,
    return_metrics: bool = False,
):
    loop = tqdm.tqdm(loader, desc=desc)
    total_loss = 0.0
    targets = []
    predictions = []
    for batch_idx, (images, masks) in enumerate(loop):
        images = images.to(device)
        masks = masks.to(device)

        # forward
        preds = model(images)
        loss = loss_function(preds, masks)

        # backward
        if optimizer is not None and scaler is not None:
            optimizer.zero_grad()
            scaler.scale(loss).backward()
            scaler.step(optimizer)
            scaler.update()

        # display metrics
        preds = predictions_function(preds.cpu().detach()).numpy()
        masks = masks.cpu().numpy()

        loss = loss.cpu().item()
        mpa, iou, fwiou = compute_metrics(masks, preds)

        loop.set_postfix(loss=loss, mpa=mpa, miou=iou, fwiou=fwiou)
        total_loss += loss
        if return_metrics:
            targets.append(masks)
            predictions.append(preds)

    total_loss /= len(loader)
    if return_metrics:
        targets = np.concatenate(targets, axis=0)
        predictions = np.concatenate(predictions, axis=0)
        mpa, iou, fwiou = compute_metrics(targets, predictions)

        return total_loss, mpa, iou, fwiou
    return total_loss


def train(wandb_config=None):
    with wandb.init(config=wandb_config):
        wandb_config = wandb.config
        project_config = load_config("segmentation")
        device = "cuda" if torch.cuda.is_available() else "cpu"
        experiment = project_config["experiment"]
        learning_rate = wandb_config["learning_rate"]
        experiment_plots = os.path.join(
            project_config["plots_path"],
            f"id_{experiment}",
            f"lr_{str(learning_rate).replace('.', '_')}",
        )

        print("Training on device:", device)

        if not os.path.exists(experiment_plots):
            os.makedirs(experiment_plots)

        train_dataloader, val_dataloader, test_dataloader = get_dataloaders(
            project_config["dataset_path"], wandb_config["batch_size"]
        )
        Visualizer.visualise_dataloader_samples(
            test_dataloader,
            3,
            4,
            title="Some samples",
            save_path=os.path.join(experiment_plots, "samples.png"),
        )

        num_epochs = wandb_config["num_epochs"]
        model = SegmentationUNet(3, 1).to(device)
        loss_function = nn.BCEWithLogitsLoss()
        predictions_function = binary_predictions
        optimizer = optim.Adam(model.parameters(), lr=wandb_config["learning_rate"])
        scaler = torch.cuda.amp.GradScaler()

        checkpoint_format = "model_checkpoint_e{}"
        model_binary_format = "model_binary_e{}"
        models_path = os.path.join(
            project_config["save_checkpoints_path"],
            f"id_{experiment}",
            f"lr_{str(learning_rate).replace('.', '_')}",
        )

        if not os.path.exists(models_path):
            os.makedirs(models_path)

        if (checkpoint := project_config["load_checkpoint"]) is not None and isinstance(
            checkpoint, str
        ):
            load_checkpoint(
                model, os.path.join(project_config["save_checkpoints_path"], checkpoint)
            )

        Visualizer.visualize_model_predictions(
            model,
            val_dataloader,
            4,
            predictions_function,
            device,
            f"Epoch 0/{num_epochs}",
            save_path=os.path.join(experiment_plots, "results_e0.png"),
        )

        for epoch in range(1, num_epochs + 1):
            model.train()
            train_loss = train_step(
                train_dataloader,
                model,
                optimizer,
                loss_function,
                predictions_function,
                scaler,
                device,
                desc=f"Train epoch {epoch}/{num_epochs}",
            )
            model.eval()
            with torch.no_grad():
                val_loss, mpa, iou, fwiou = train_step(
                    val_dataloader,
                    model,
                    None,
                    loss_function,
                    predictions_function,
                    None,
                    device,
                    desc=f"Validation epoch {epoch}/{num_epochs}",
                    return_metrics=True,
                )
                Visualizer.visualize_model_predictions(
                    model,
                    val_dataloader,
                    4,
                    predictions_function,
                    device,
                    f"Epoch {epoch}/{num_epochs}",
                    save_path=os.path.join(experiment_plots, f"results_e{epoch}.png"),
                )

            save_checkpoint(
                model.state_dict(),
                os.path.join(models_path, checkpoint_format.format(epoch)),
            )
            save_to_binaries(
                model, os.path.join(models_path, model_binary_format.format(epoch))
            )

            table = Visualizer.wandb_predictions_table(
                model, val_dataloader, device, predictions_function
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
                "Epoch {}: Train Loss: {:.4f} | Validation Loss: {:.4f} | "
                "MPA: {:.4f} | MIoU: {:.4f} | FWIoU: {:.4f}".format(
                    epoch, train_loss, val_loss, mpa, iou, fwiou
                )
            )


def sweep(api_key: str = None):
    sweep_config = {
        "method": "grid",
        "metric": {
            "name": "val_loss",
            "goal": "minimize",
        },
        "parameters": {
            "learning_rate": {"values": [0.01, 0.001, 0.0001]},
            "num_epochs": {"value": 5},
            "batch_size": {"values": [32, 128]},
        },
    }
    if api_key is None:
        from dotenv import load_dotenv

        load_dotenv()
        api_key = os.getenv("WANDB_API_KEY")

    wandb.login(key=api_key)
    sweep_id = wandb.sweep(sweep_config, project="hair-color-changer")
    wandb.agent(sweep_id, train)


if __name__ == "__main__":
    sweep()
