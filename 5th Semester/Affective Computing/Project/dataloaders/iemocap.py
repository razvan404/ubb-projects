import logging

import numpy as np
import pandas as pd
import torch.nn.functional
from typing import List

from torch.utils.data import Dataset, DataLoader

logger = logging.getLogger(__name__)


class IemocapDataset(Dataset):
    def __init__(
        self,
        dataset_path: str,
        dataframe: pd.DataFrame,
        emotions: List[str],
        split: str,
    ):
        self._dataset_path = dataset_path
        self._emotions = np.array(emotions)
        self._dataframe = dataframe

        self._dataframe = self._dataframe.loc[self._dataframe["emotion"].isin(emotions)]

        rows_80_percent = int(0.8 * len(self._dataframe))
        if split == "train":
            self._dataframe = self._dataframe.iloc[:rows_80_percent, :]
        elif split == "test":
            self._dataframe = self._dataframe.iloc[rows_80_percent:, :]
        else:
            raise ValueError("Invalid dataset split")

        logger.info(f"Loaded {split} dataset. Size: {len(self)}")
        emotions_str = ""
        for emotion in emotions:
            emotions_str += f"{emotion} - {self._dataframe[self._dataframe['emotion'] == emotion]['emotion'].count()} | "
        emotions_str = emotions_str[:-3]
        logger.info(f"Each emotion percentages: {emotions_str}")
        logger.info(
            f"Shapes: audio - {self._dataframe['audio'].iloc[0].shape}; text - {self._dataframe['text'].iloc[0].shape}"
        )

    def __getitem__(self, index: int):
        audio, text, emotion = self._dataframe.iloc[index]
        emotion_index = torch.tensor(np.where(self._emotions == emotion)[0][0])
        return audio, text, emotion_index

    def __len__(self):
        return len(self._dataframe)


def IemocapDataLoader(
    dataset_path: str,
    dataframe: pd.DataFrame,
    emotions: List[str],
    split: str,
    **kwargs,
):
    return DataLoader(
        IemocapDataset(dataset_path, dataframe, emotions, split),
        **kwargs,
    )
