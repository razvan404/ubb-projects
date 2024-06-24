import torch
import torch.nn as nn
import logging

from core.config import device
from core.trainer import AbstractTrainer

logger = logging.getLogger(__name__)


class FusionTrainer(AbstractTrainer):
    def __init__(
        self,
        fusion_model: nn.Module,
        num_epochs: int = 3,
        learning_rate: float = 1e-5,
        loss: callable = nn.CrossEntropyLoss(),
    ):
        super(FusionTrainer, self).__init__(
            fusion_model,
            num_epochs,
            torch.optim.AdamW(fusion_model.parameters(), lr=learning_rate, eps=1e-8),
            loss,
            "fusion",
        )

    def _get_logits_and_real(self, batch) -> (torch.Tensor, torch.Tensor):
        audio, text, emotion = batch
        audio = audio.to(device)
        text = text.to(device)
        emotion = emotion.to(device)
        logits = self.model(text, audio)
        return logits, emotion
