import logging

import torch
import torch.nn as nn

from core.config import device
from core.trainer import AbstractTrainer

logger = logging.getLogger(__name__)


class AudioTrainer(AbstractTrainer):
    def __init__(
        self,
        audio_model: nn.Module,
        num_epochs: int = 3,
        learning_rate: float = 2e-5,
        loss: callable = nn.CrossEntropyLoss(),
    ):
        super(AudioTrainer, self).__init__(
            audio_model,
            num_epochs,
            torch.optim.AdamW(audio_model.parameters(), lr=learning_rate, eps=1e-8),
            loss,
            name="audio",
        )
        audio_model.freeze_feature_extractor()

    def _get_logits_and_real(self, batch) -> (torch.Tensor, torch.Tensor):
        audio, emotion = batch[0], batch[2]
        audio = audio.to(device)
        emotion = emotion.to(device)
        logits = self.model(audio)
        return logits, emotion
