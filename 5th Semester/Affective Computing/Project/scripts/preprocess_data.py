import os

import numpy as np
import pandas as pd
from joblib import Parallel, delayed
from tqdm import tqdm

from core.config import CONFIG
from preprocessing.iemocap import IemocapPreprocessor


def process_raw_data_to_pickle(out_filename: str):
    preprocessor = IemocapPreprocessor(CONFIG.dataset_path())
    df = preprocessor.generate_dataframe()

    preprocessed_path = CONFIG.dataset_preprocessed_dir_path()
    if not os.path.exists(preprocessed_path):
        os.makedirs(preprocessed_path)

    df.to_pickle(
        os.path.join(preprocessed_path, out_filename),
    )


def process_audio_data_to_pickle(in_filename: str, out_filename: str, extractor):
    dataset_path = CONFIG.dataset_path()
    preprocessed_dir = CONFIG.dataset_preprocessed_dir_path()
    dataframe = pd.read_pickle(os.path.join(preprocessed_dir, in_filename))

    def _extract_data_from_audio(audio_path: str):
        session_id = int(audio_path[3:5])
        wav_path = os.path.join(
            dataset_path,
            f"Session{session_id}",
            "sentences",
            "wav",
            audio_path[:-5],
            f"{audio_path}.wav",
        )
        return extractor.extract(wav_path)

    extracted_features = Parallel(n_jobs=-1)(
        delayed(_extract_data_from_audio)(audio_path)
        for audio_path in tqdm(dataframe["audio"], desc="Turning audio into W2V2s")
    )
    max_audio_length = np.max([audio.shape[0] for audio in extracted_features])
    extracted_features = list(
        map(
            lambda audio: np.pad(
                audio,
                (0, max_audio_length - audio.shape[0]),
                "constant",
                constant_values=0,
            )[..., : max_audio_length // 10],
            extracted_features,
        )
    )
    dataframe["audio"] = extracted_features
    dataframe.to_pickle(os.path.join(preprocessed_dir, out_filename))


def process_text_data_to_pickle(in_filename: str, out_filename: str, tokenizer):
    preprocessed_dir = CONFIG.dataset_preprocessed_dir_path()
    dataframe = pd.read_pickle(os.path.join(preprocessed_dir, in_filename))

    max_text_length = dataframe["text"].apply(len).max()
    dataframe["text"] = dataframe["text"].apply(
        lambda text: np.array(
            tokenizer.encode(
                text,
                add_special_tokens=True,
                truncation=True,
                padding="max_length",
                max_length=max_text_length,
            )
        )
    )
    dataframe.to_pickle(os.path.join(preprocessed_dir, out_filename))
