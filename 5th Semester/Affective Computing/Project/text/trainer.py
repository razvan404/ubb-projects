import torch
import torch.nn as nn
import logging

from core.config import device
from core.trainer import AbstractTrainer

logger = logging.getLogger(__name__)


class TextTrainer(AbstractTrainer):
    def __init__(
        self,
        text_model: nn.Module,
        num_epochs: int = 3,
        learning_rate: float = 2e-5,
        loss: callable = nn.CrossEntropyLoss(),
    ):
        super(TextTrainer, self).__init__(
            text_model,
            num_epochs,
            torch.optim.AdamW(text_model.parameters(), lr=learning_rate, eps=1e-8),
            loss,
            "text",
        )

    def _get_logits_and_real(self, batch) -> (torch.Tensor, torch.Tensor):
        text, emotion = batch[1], batch[2]
        text = text.to(device)
        emotion = emotion.to(device)
        logits = self.model(text)[0]
        return logits, emotion
