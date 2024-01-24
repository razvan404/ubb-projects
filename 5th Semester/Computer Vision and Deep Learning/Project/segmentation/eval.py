import torch
import torch.nn as nn

from core.config import load_config
from .utils import binary_predictions
from .metrics import frequency_weighted_intersection_over_union
from .model import SegmentationUNet


if __name__ == "__main__":
    config = load_config("segmentation")
    device = "cuda" if torch.cuda.is_available() else "cpu"

    model = SegmentationUNet(3, 1).to(device)
    loss_function = nn.BCEWithLogitsLoss()
    accuracy_function = frequency_weighted_intersection_over_union
    predictions_function = binary_predictions
