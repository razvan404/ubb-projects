import torch
import torch.nn as nn
from torch.hub import load_state_dict_from_url


class AlexNet(nn.Module):
    def __init__(self, num_classes: int = 1000):
        super(AlexNet, self).__init__()
        self.num_classes = num_classes
        self.features = nn.Sequential(
            nn.Conv2d(3, 64, kernel_size=11, stride=4, padding=2),
            nn.ReLU(inplace=True),
            nn.MaxPool2d(kernel_size=3, stride=2),
            nn.Conv2d(64, 192, kernel_size=5, padding=2),
            nn.ReLU(inplace=True),
            nn.MaxPool2d(kernel_size=3, stride=2),
            nn.Conv2d(192, 384, kernel_size=3, padding=1),
            nn.ReLU(inplace=True),
            nn.Conv2d(384, 256, kernel_size=3, padding=1),
            nn.ReLU(inplace=True),
            nn.Conv2d(256, 256, kernel_size=3, padding=1),
            nn.ReLU(inplace=True),
            nn.MaxPool2d(kernel_size=3, stride=2),
        )
        self.avgpool = nn.AdaptiveAvgPool2d((12, 12))
        self.classifier = nn.Sequential(
            nn.Dropout(),
            nn.Linear(256 * 6 * 6, 4096),
            nn.ReLU(inplace=True),
            nn.Dropout(),
            nn.Linear(4096, 4096),
            nn.ReLU(inplace=True),
            nn.Linear(4096, num_classes),
        )

    def forward(self, x):
        x = self.features(x)
        x = self.avgpool(x)
        x = torch.flatten(x, 1)
        x = self.classifier(x)
        return x


class ModifiedAlexNet(AlexNet):
    def __init__(self, num_classes: int):
        super(ModifiedAlexNet, self).__init__(num_classes)
        self.avgpool = None
        self.classifier = None
        self.classif = nn.Sequential(nn.Dropout(0.5), nn.Linear(256, num_classes))
        self.softmax = nn.Softmax(dim=1)

    def forward(self, x):
        x = self.features(x)
        x = torch.flatten(x, start_dim=2)
        x = torch.sum(x, dim=2)
        x = self.classif(x)
        x = self.softmax(x)
        return x


def alexnet(
    model_url: str = None, pretrained: bool = False, progress: bool = True, **kwargs
):
    model = AlexNet(**kwargs)
    if pretrained:
        state_dict = load_state_dict_from_url(model_url, progress=progress)
        model.load_state_dict(state_dict)
    return model


def modified_alexnet(
    model_url: str = None, pretrained: bool = False, progress: bool = True, **kwargs
):
    model = ModifiedAlexNet(**kwargs)
    if pretrained:
        state_dict = load_state_dict_from_url(model_url, progress=progress)
        model.load_state_dict(state_dict)
    return model


def get_pretrained_alexnet_model(alexnet_url, num_classes: int):
    original_model = alexnet(alexnet_url, pretrained=True)
    original_dict = original_model.state_dict()
    modified_model = modified_alexnet(pretrained=False, num_classes=num_classes)
    modified_model_dict = modified_model.state_dict()
    pretrained_modified_model_dict = {
        key: value for key, value in original_dict.items() if key in modified_model_dict
    }
    modified_model_dict.update(pretrained_modified_model_dict)
    modified_model.load_state_dict(modified_model_dict)
    return modified_model
