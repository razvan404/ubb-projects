import torch.utils.checkpoint
from transformers import AutoModel
from torch import nn


class Wav2Vec2(nn.Module):
    def __init__(self, num_classes: int, hidden_size: int = 256):
        super(Wav2Vec2, self).__init__()
        self.wav2vec2 = AutoModel.from_pretrained(
            "facebook/wav2vec2-base-960h", mask_time_prob=0
        )
        self.flatten = nn.Flatten()
        self.lm_head = nn.Linear(170 * 768, hidden_size)
        self.cls_head = nn.Linear(hidden_size, num_classes)
        self.softmax = nn.Softmax(dim=1)

    def freeze_feature_extractor(self):
        self.wav2vec2.freeze_feature_encoder()

    def forward(self, x: torch.Tensor):
        x = self.wav2vec2(x).last_hidden_state
        x = self.flatten(x)
        x = self.lm_head(x)
        x = self.cls_head(x)
        x = self.softmax(x)
        return x
