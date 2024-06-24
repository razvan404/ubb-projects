import numpy as np
import tqdm
import logging

import torch
import torch.nn as nn
import transformers
from matplotlib import pyplot as plt
from sklearn.metrics import confusion_matrix
from typing import List

from torch.utils.data import DataLoader

from vizualisers.plots import PlotVisualizer

logger = logging.getLogger(__name__)


class AbstractTrainer:
    def __init__(
        self,
        model: nn.Module,
        num_epochs: int,
        optimizer,
        loss: callable,
        name: str,
    ):
        self.model = model
        self._num_epochs = num_epochs
        self._optimizer = optimizer
        self._loss = loss
        self._name = name

    def _get_logits_and_real(self, batch) -> (torch.Tensor, torch.Tensor):
        pass

    def train(self, train_dataloader: DataLoader):
        total_steps = len(train_dataloader) * self._num_epochs
        scheduler = transformers.get_linear_schedule_with_warmup(
            self._optimizer, num_warmup_steps=0, num_training_steps=total_steps
        )

        history_loss = []
        history_acc = []

        logger.info(f"Training the {self._name} model...")
        self.model.train()
        for epoch in range(1, self._num_epochs + 1):
            loader = tqdm.tqdm(train_dataloader, desc=f"Epoch {epoch}")
            for batch in loader:
                # Forward
                logits, real = self._get_logits_and_real(batch)
                loss = self._loss(logits, real)

                # Backward
                self._optimizer.zero_grad()
                loss.backward()
                torch.nn.utils.clip_grad_norm_(self.model.parameters(), 1.0)
                self._optimizer.step()
                scheduler.step()

                # Perform the accuracy
                preds = torch.argmax(logits, dim=1)
                accuracy = torch.mean((preds == real).float())

                # Register the metrics
                loss = loss.item()
                accuracy = accuracy.item()
                history_loss.append(loss)
                history_acc.append(accuracy)
                loader.set_postfix(loss=loss, accuracy=accuracy)

        self.plot_histories(history_loss, history_acc)

    def plot_histories(
        self, history_losses: List[float], history_accuracies: List[float]
    ):
        PlotVisualizer.plot_many(
            (1, 2),
            lambda: PlotVisualizer.plot_history(
                history_losses, f"{self._name} loss history"
            ),
            lambda: PlotVisualizer.plot_history(
                history_accuracies, f"{self._name} accuracy history"
            ),
            filename=f"{self._name}-losses.png",
        )

    def eval(self, test_dataloader: DataLoader, labels: List[str] = None):
        y_actual = []
        y_pred = []
        self.model.eval()
        with torch.no_grad():
            loader = tqdm.tqdm(test_dataloader, "Evaluating the model")
            for batch in loader:
                logits, real = self._get_logits_and_real(batch)
                preds = torch.argmax(logits, dim=1)
                y_actual += real.cpu().numpy().tolist()
                y_pred += preds.cpu().numpy().tolist()

        possible_values = sorted({*y_actual, *y_pred})
        possible_labels = [
            label for i, label in enumerate(labels) if i in possible_values
        ]
        if len(possible_labels) < len(possible_values):
            possible_labels += ["unknown"] * (
                len(possible_values) - len(possible_labels)
            )
        conf_matrix = confusion_matrix(y_actual, y_pred)
        print("Accuracy:", np.sum(np.diag(conf_matrix)) / np.sum(conf_matrix))
        PlotVisualizer.plot_confusion_matrix(
            conf_matrix, possible_labels, filename=f"{self._name}-conf_matrix.png"
        )
