from typing import Tuple

import os
import torch
from torchvision import transforms
from torch.utils.data import Dataset

from utils import load_image, load_mask


class FlameDataset(Dataset):
    def __init__(
        self,
        base_dir: str,
        image_transform: transforms.Compose,
        mask_transform: transforms.Compose,
        split: str | None = None,
    ):
        self._images_dir = os.path.join(base_dir, "Images")
        self._masks_dir = os.path.join(base_dir, "Masks")

        self._start = 0
        self._num_images = len(os.listdir(self._images_dir))
        if split == "train":
            self._num_images = int(self._num_images * 0.8)
        elif split == "validation":
            self._start = int(self._num_images * 0.8)
            self._num_images = self._num_images - self._start
        elif split is not None:
            raise ValueError('The split must be either "train" or "validation"!')

        self._image_transform = image_transform
        self._mask_transform = mask_transform

    def __len__(self):
        return self._num_images

    def __getitem__(self, idx: int) -> Tuple[torch.Tensor, torch.Tensor]:
        idx += self._start
        image_path = os.path.join(self._images_dir, f"image_{idx}.jpg")
        mask_path = os.path.join(self._masks_dir, f"image_{idx}.png")
        image = load_image(image_path)
        image = self._image_transform(image)
        mask = load_mask(mask_path)
        mask = self._mask_transform(mask)
        return image, mask


def build_image_transform(min_resolution: int = 2160, work_resolution: int = 512, size: (int, int) = None):
    return transforms.Compose(
        [
            transforms.ToTensor(),
            *(
                [transforms.Resize(size, antialias=True)] if size is not None else [
                    transforms.CenterCrop(min_resolution),
                    transforms.Resize((work_resolution, work_resolution), antialias=True),
                ]
            ),
            transforms.Normalize(mean=[0.5, 0.5, 0.5], std=[0.5, 0.5, 0.5]),
        ]
    )


def build_mask_transform(min_resolution: int = 2160, work_resolution: int = 512):
    return transforms.Compose(
        [
            transforms.ToTensor(),
            transforms.CenterCrop(min_resolution),
            transforms.Resize(
                (work_resolution, work_resolution),
                interpolation=transforms.InterpolationMode.NEAREST,
                antialias=True,
            ),
        ]
    )


def flame_dataset_splits(
    dataset_dir: str, min_resolution: int = 2160, work_resolution: int = 512
):
    image_transform = build_image_transform(min_resolution, work_resolution)
    mask_transform = build_mask_transform(min_resolution, work_resolution)

    return (
        FlameDataset(dataset_dir, image_transform, mask_transform, "train"),
        FlameDataset(dataset_dir, image_transform, mask_transform, "validation"),
    )
