import torch
import torch.nn as nn
import matplotlib.pyplot as plt
import numpy as np
import wandb

from torch.utils.data import DataLoader


class Visualizer:
    @classmethod
    def _plotable_image(cls, img: torch.Tensor, is_normalized: bool = False):
        if len(img.shape) != 3:
            return img
        img = np.transpose(img.numpy(), (1, 2, 0))
        if is_normalized:
            img = (img + 1) / 2
            img = np.clip(img, 0, 1)
        return img

    @classmethod
    def build_one_sample(
        cls,
        model: nn.Module,
        dataloader: DataLoader,
        device: str,
        predictions_function: callable,
    ):
        sample_images, sample_masks = next(iter(dataloader))
        preds = model(sample_images.to(device))
        preds = predictions_function(preds)
        return sample_images, sample_masks, preds

    @classmethod
    def wandb_predictions_table(
        cls,
        model: nn.Module,
        dataloader: DataLoader,
        device: str,
        predictions_function: callable,
    ):
        sample_images, sample_masks, binary_preds = cls.build_one_sample(
            model, dataloader, device, predictions_function
        )
        table = wandb.Table(columns=["Image", "True Mask", "Predicted Mask"])
        for img, true_mask, pred_mask in zip(sample_images, sample_masks, binary_preds):
            table.add_data(
                wandb.Image(img), wandb.Image(true_mask), wandb.Image(pred_mask)
            )
        return table

    @classmethod
    def visualise_dataloader_samples(
        cls,
        dataloader: DataLoader,
        batches_to_plot: int,
        max_items_per_batch: int = None,
        title: str = None,
        save_path: str = None,
    ):
        batch_size = dataloader.batch_size
        rows, cols = min(batch_size, max_items_per_batch), batches_to_plot * 2
        if title is not None:
            plt.title(title)
        plt.axis("off")
        for i_batch, batch in enumerate(dataloader):
            imgs, masks = batch
            for i in range(0, batch_size):
                plt.subplot(rows, cols, cols * i + i_batch * 2 + 1)
                plt.axis("off")
                plt.imshow(cls._plotable_image(imgs[i], is_normalized=True))

                plt.subplot(rows, cols, cols * i + i_batch * 2 + 2)
                plt.axis("off")
                plt.imshow(cls._plotable_image(masks[i]), cmap="binary")

                if max_items_per_batch is not None and i == max_items_per_batch - 1:
                    break

            if i_batch == batches_to_plot - 1:
                break
        if save_path is not None:
            plt.savefig(save_path)
        plt.show()

    @classmethod
    def visualize_model_predictions(
        cls,
        model: nn.Module,
        loader: DataLoader,
        examples_count: int,
        predictions_function: callable,
        device: str,
        title: str = None,
        save_path: str = None,
    ):
        shown_so_far = 0
        batch_size = loader.batch_size

        for images, masks in loader:
            device_images = images.to(device)
            preds = model(device_images).cpu()
            preds = predictions_function(preds)
            for i in range(batch_size):
                plt.subplot(examples_count, 3, 3 * shown_so_far + 1)
                if shown_so_far == 0:
                    plt.title("Image")
                plt.imshow(cls._plotable_image(images[i], is_normalized=True))
                plt.axis("off")

                plt.subplot(examples_count, 3, 3 * shown_so_far + 2)
                if shown_so_far == 0:
                    plt.title(
                        "\n".join([title, "GT Mask"])
                        if title is not None
                        else "GT Mask"
                    )
                plt.imshow(cls._plotable_image(masks[i]), cmap="binary")
                plt.axis("off")

                plt.subplot(examples_count, 3, 3 * shown_so_far + 3)
                if shown_so_far == 0:
                    plt.title("Pred Mask")
                plt.imshow(cls._plotable_image(preds[i]), cmap="binary")
                plt.axis("off")

                shown_so_far += 1
                if shown_so_far == examples_count:
                    if save_path is not None:
                        plt.savefig(save_path)
                    plt.show()
                    return
