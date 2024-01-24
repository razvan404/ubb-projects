import torch
import torch.nn as nn
import torchvision.transforms.functional as F


def TwoConv2d(in_channels: int, out_channels: int) -> nn.Module:
    return nn.Sequential(
        nn.Conv2d(in_channels, out_channels, 3, 1, 1, bias=False),
        nn.BatchNorm2d(out_channels),
        nn.ReLU(inplace=True),
        nn.Conv2d(out_channels, out_channels, 3, 1, 1, bias=False),
        nn.BatchNorm2d(out_channels),
        nn.ReLU(inplace=True),
    )


class UpSamplingBlock(nn.Module):
    def __init__(self, in_channels: int, skip_channels: int, out_channels: int):
        super(UpSamplingBlock, self).__init__()
        self.convT = nn.ConvTranspose2d(in_channels, out_channels, 2, 2)
        self.conv = TwoConv2d(skip_channels + out_channels, out_channels)

    def forward(self, skip_connection: torch.Tensor, x: torch.Tensor):
        x = self.convT(x)
        if x.shape != skip_connection.shape:
            x = F.resize(x, size=skip_connection.shape[2:], antialias=True)
        x = torch.cat((skip_connection, x), dim=1)
        x = self.conv(x)
        return x


class SegmentationUNet(nn.Module):
    def __init__(
        self,
        in_channels: int,
        out_channels: int,
        features: list[int] = None,
    ):
        super(SegmentationUNet, self).__init__()
        if features is None:
            features = [32, 64, 128, 256]

        self.down_sampling = nn.ModuleList()
        for feature in features:
            self.down_sampling.append(TwoConv2d(in_channels, feature))
            in_channels = feature

        self.max_pool = nn.MaxPool2d(2, 2)
        self.bottleneck = TwoConv2d(features[-1], features[-1] * 2)

        self.up_sampling = nn.ModuleList()
        for feature in reversed(features):
            self.up_sampling.append(UpSamplingBlock(feature * 2, feature, feature))

        self.last_conv = nn.Conv2d(features[0], out_channels, 1)
        self.num_features = len(features)

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        skip_connections = []
        for layer in self.down_sampling:
            x = layer(x)
            skip_connections.append(x)
            x = self.max_pool(x)
        skip_connections.reverse()
        x = self.bottleneck(x)
        for i, layer in enumerate(self.up_sampling):
            x = layer(skip_connections[i], x)
        x = self.last_conv(x)
        return x


def test_segmentation_unet():
    with torch.no_grad():
        img_size = 240
        num_channels = 3
        num_classes = 10
        batch_size = 16
        x = torch.rand((batch_size, num_channels, img_size, img_size))
        model = SegmentationUNet(num_channels, num_classes)
        x = model(x)
        assert x.shape == (batch_size, num_classes, img_size, img_size)


if __name__ == "__main__":
    test_segmentation_unet()
