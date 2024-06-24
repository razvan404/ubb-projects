import torch
import torch.nn as nn
import torch.nn.functional as F
from typing import List


class TemporalAwareBlock(nn.Module):
    def __init__(
        self,
        in_channels: int,
        out_channels: int,
        kernel_size: int,
        dilation_rate: int = 1,
        dropout_rate: float = 0,
    ):
        super(TemporalAwareBlock, self).__init__()

        self.conv1_1 = nn.Conv1d(
            in_channels=in_channels,
            out_channels=out_channels,
            kernel_size=kernel_size,
            dilation=dilation_rate,
            padding=dilation_rate * (kernel_size - 1),
        )
        self.bn1_1 = nn.BatchNorm1d(out_channels)
        self.activation = nn.ReLU()
        self.dropout1_1 = nn.Dropout(p=dropout_rate)

        self.conv2_1 = nn.Conv1d(
            in_channels=out_channels,
            out_channels=out_channels,
            kernel_size=kernel_size,
            dilation=dilation_rate,
            padding=dilation_rate * (kernel_size - 1),
        )
        self.bn2_1 = nn.BatchNorm1d(out_channels)
        self.dropout2_1 = nn.Dropout(p=dropout_rate)

        self.conv_out = nn.Conv1d(
            in_channels=in_channels,
            out_channels=out_channels,
            kernel_size=1,
            padding=dilation_rate * (kernel_size - 1),
        )

    def forward(self, x):
        original_x = x

        x = self.conv1_1(x)
        x = self.bn1_1(x)
        x = self.activation(x)
        x = self.dropout1_1(x)

        x = self.conv2_1(x)
        x = self.bn2_1(x)
        x = self.activation(x)
        x = self.dropout2_1(x)

        if original_x.shape[-1] != x.shape[-1]:
            original_x = self.conv_out(original_x)

        x = torch.sigmoid(x)
        x = original_x * x

        return x


class TimNet(nn.Module):
    def __init__(
        self,
        in_channels: int,
        filters_size: List[int] = None,
        kernel_size: int = 2,
        stack_size: int = 1,
        dilation_size: int = 4,
        dropout_rate: float = 0.1,
    ):
        super(TimNet, self).__init__()

        if filters_size is None:
            filters_size = [64, 64, 64, 64, 64]
        self.dropout_rate = dropout_rate
        self.stack_size = stack_size

        self.forward_convd = nn.Conv1d(
            in_channels=in_channels,
            out_channels=filters_size[0],
            kernel_size=1,
            dilation=1,
        )
        self.backward_convd = nn.Conv1d(
            in_channels=in_channels,
            out_channels=filters_size[0],
            kernel_size=1,
            dilation=1,
        )

        self.tabs = nn.ModuleList()
        for i in range(dilation_size):
            self.tabs.append(
                TemporalAwareBlock(
                    filters_size[i],
                    filters_size[i + 1],
                    kernel_size,
                    2**i,
                    self.dropout_rate,
                )
            )

    def forward(self, x: torch.Tensor):
        forward = x
        backward = torch.flip(x, dims=[-1])

        forward_conv = self.forward_convd(forward)
        backward_conv = self.backward_convd(backward)

        final_skip_connection = []

        skip_out_forward = forward_conv
        skip_out_backward = backward_conv

        for s in range(self.stack_size):
            for temporal_aware_block in self.tabs:
                skip_out_forward = temporal_aware_block(skip_out_forward)
                skip_out_backward = temporal_aware_block(skip_out_backward)

                temp_skip = skip_out_forward + skip_out_backward
                temp_skip = F.avg_pool1d(temp_skip, kernel_size=temp_skip.shape[-1])
                temp_skip = temp_skip.unsqueeze(1)
                final_skip_connection.append(temp_skip)

        x = final_skip_connection[0]
        for i, item in enumerate(final_skip_connection):
            if i == 0:
                continue
            x = torch.cat([x, item], dim=-2)
        return x.squeeze()


class TimNetClassifier(nn.Module):
    def __init__(
        self,
        in_filters: int,
        num_classes: int,
        filters_size: List[int] = None,
        kernel_size: int = 2,
        stack_size: int = 1,
        dilation_size: int = 4,
        dropout_rate: float = 0.1,
    ):
        super(TimNetClassifier, self).__init__()
        self.multi_decision_layer = TimNet(
            in_filters,
            filters_size,
            kernel_size,
            stack_size,
            dilation_size,
            dropout_rate,
        )
        self.classifier = nn.Linear(960, num_classes, bias=True)
        self.softmax = nn.Softmax(dim=1)

    def forward(self, x: torch.Tensor):
        x = self.multi_decision_layer(x)
        x = self.classifier(x)
        x = self.softmax(x)
        return x
