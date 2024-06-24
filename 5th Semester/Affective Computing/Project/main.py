import random
import numpy as np
import torch

# from audio.extractor import Wav2Vec2Extractor
from core.config import CONFIG
from scripts.preprocess_data import (
    process_audio_data_to_pickle,
    process_raw_data_to_pickle,
    process_text_data_to_pickle,
)
from scripts.run_model import TrainerOps
import logging

logging.basicConfig(level=logging.INFO)

logger = logging.getLogger(__name__)


def prepare_env():
    torch.manual_seed(0)
    np.random.seed(0)
    random.seed(0)
    CONFIG.load_config("config.yaml")


if __name__ == "__main__":
    # 0. Prepare the environment
    prepare_env()
    # 1. Prepare audio paths and raw text
    # process_raw_data_to_pickle("audio_and_text.pkl")
    # 2. Turn the raw audio file names into mfccs
    # process_audio_data_to_pickle(
    #     "audio_and_text.pkl", "w2v2_and_text.pkl", Wav2Vec2Extractor()
    # )
    # 3. Turn the raw text file into tokens
    # process_text_data_to_pickle(
    #     "w2v2_and_text.pkl", "w2v2_and_tokens.pkl", DebertaV3Tokenizer()
    # )
    # 4. Get the text trainer
    text_trainer = TrainerOps.create_or_load_text_trainer("deberta_model3.pt")
    # 4.1. Train and save the text model
    # TrainerOps.train(text_trainer)
    # TrainerOps.save(text_trainer, "deberta_model3.pt")
    # 4.2. Evaluate the text model
    # TrainerOps.evaluate(text_trainer)
    # 5. Get the audio trainer
    audio_trainer = TrainerOps.create_or_load_audio_trainer(
        "wav2vec2_state_dict2.pt", load_state_dict=True
    )
    # 5.1. Train and save the audio model
    # TrainerOps.train(audio_trainer)
    # TrainerOps.save(audio_trainer, "wav2vec2_state_dict3.pt", save_state_dict=True)
    # 5.2. Evaluate the audio model
    # TrainerOps.evaluate(audio_trainer)
    # 6. Get the fusion trainer
    fusion_trainer = TrainerOps.create_or_load_fusion_trainer(
        audio_model=audio_trainer.model, text_model=text_trainer.model
    )
    # 6.1. Train and save the fusion model
    TrainerOps.train(fusion_trainer)
    TrainerOps.save(fusion_trainer, "fusion_state_dict.pt", save_state_dict=True)
    # 6.2. Evaluate the fusion model
    TrainerOps.evaluate(fusion_trainer)
