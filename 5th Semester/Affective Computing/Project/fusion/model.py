import torch
from torch import nn

from typing import List

from audio.wav2vec2 import Wav2Vec2
from text.deberta import DebertaV3


class FusionModel(nn.Module):
    def __init__(
        self,
        num_classes: int,
        deberta_model: DebertaV3,
        wav2vec2_model: Wav2Vec2,
        hidden_layers: List[int] = None,
        freeze_weights: bool = True,
    ):
        super(FusionModel, self).__init__()
        if freeze_weights:
            for param in deberta_model.parameters():
                param.requires_grad = False
            for param in wav2vec2_model.parameters():
                param.requires_grad = False
        if hidden_layers is None:
            hidden_layers = [512, 128, 32]
        self.num_classes = num_classes
        self.text_model = deberta_model
        self.audio_model = wav2vec2_model

        self.mlp_head = nn.Sequential(
            # TODO: Remove + 4 because is from the old DeBERTa model
            nn.Linear(170 * 768 + 768 + num_classes * 2 + 4, hidden_layers[0])
        )
        for i in range(0, len(hidden_layers) - 1):
            self.mlp_head.append(nn.Linear(hidden_layers[i], hidden_layers[i + 1]))
        self.cls_head = nn.Linear(hidden_layers[-1], num_classes + 1)
        self.softmax = nn.Softmax(dim=1)

    def forward(self, text: torch.Tensor, audio: torch.Tensor):
        audio_features = self.audio_model.flatten(
            self.audio_model.wav2vec2(audio).last_hidden_state
        )
        audio_classification = self.audio_model.softmax(
            self.audio_model.cls_head(self.audio_model.lm_head(audio_features))
        )
        deberta_features = self.text_model.deberta(text).last_hidden_state
        text_features = self.text_model.pooler(deberta_features)
        text_classification = self.text_model.dropout(
            self.text_model.classifier(text_features)
        )
        x = torch.cat(
            [audio_features, audio_classification, text_features, text_classification],
            dim=1,
        )
        x = self.mlp_head(x)
        x = self.cls_head(x)
        x = self.softmax(x)
        return x
