import os

import torch
import yaml


device = "cuda" if torch.cuda.is_available() else "cpu"


class CONFIG:
    _dict: dict

    @classmethod
    def load_config(cls, filename: str):
        with open(filename, "r") as file:
            cls._dict = yaml.safe_load(file)

    @classmethod
    def _path_from_data(cls, path: str):
        return os.path.join(cls._dict["data_source"]["path"], path)

    @classmethod
    def dataset_path(cls):
        return cls._path_from_data(cls._dict["dataset"]["name"])

    @classmethod
    def dataloader_dict(cls):
        return cls._dict["dataloader"]

    @classmethod
    def dataset_preprocessed_dir_path(cls):
        return os.path.join(
            cls.dataset_path(),
            cls._dict["dataset_specific"][cls._dict["dataset"]["name"]][
                "preprocessed_dir"
            ],
        )

    @classmethod
    def dataset_emotions(cls):
        return cls._dict["dataset_specific"][cls._dict["dataset"]["name"]]["emotions"]

    @classmethod
    def saved_models_location(cls):
        save_path = cls._dict["models"]["save_location"]
        if not os.path.exists(save_path):
            os.mkdir(save_path)
        return save_path

    @classmethod
    def pretrained_alexnet_url(cls):
        return cls._dict["models"]["pretrained_alexnet"]

    @classmethod
    def save_plots_location(cls):
        save_path = cls._dict["plots"]["save_location"]
        if not os.path.exists(save_path):
            os.mkdir(save_path)
        return save_path
