import cv2
import numpy as np
import torch


def load_image(image_path: str) -> np.ndarray:
    image = cv2.imread(image_path)
    image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
    return image


def load_mask(mask_path: str) -> np.ndarray:
    mask = cv2.imread(mask_path, cv2.IMREAD_GRAYSCALE)
    mask[mask == 1] = 255
    return mask


def torch_image_to_numpy(torch_image: torch.Tensor) -> np.ndarray:
    np_image = torch_image.numpy()
    np_image = np.moveaxis(np_image, 0, -1)
    np_image = (np_image + 1) / 2
    return np_image


def binary_predictions(raw_preds: torch.Tensor) -> torch.Tensor:
    return (torch.sigmoid(raw_preds) >= 0.5).float()


def multiclass_predictions(raw_preds: torch.Tensor) -> torch.Tensor:
    return torch.argmax(raw_preds, dim=1)


def save_model_to_binaries(model_path: str, save_path: str):
    model = torch.load(model_path)
    script = torch.jit.script(model)
    script.save(save_path)


def load_binaries(bin_path):
    return torch.jit.load(bin_path)
