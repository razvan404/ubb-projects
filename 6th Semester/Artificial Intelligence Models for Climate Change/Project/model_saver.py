import json
import os
import uuid

import torch
import torch.nn as nn


class ModelSaver:
    def __init__(self, base_path: str, config: dict):
        if not os.path.exists(base_path):
            os.mkdir(base_path)
        model_path = os.path.join(base_path, str(uuid.uuid4()))
        while os.path.exists(model_path):
            model_path = os.path.join(base_path, str(uuid.uuid4()))
        os.mkdir(model_path)
        self._model_path = model_path
        with open(os.path.join(base_path, "paths.jsonl"), "a") as f:
            f.write(f'{json.dumps({**config, "model_path": model_path})}\n')

    def save(self, model: nn.Module, name: str):
        torch.save(model, os.path.join(self._model_path, name))
