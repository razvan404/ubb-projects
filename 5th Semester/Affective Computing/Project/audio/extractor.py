import torch
import librosa
import librosa.display
import numpy as np
import matplotlib.pyplot as plt

from scipy import signal
from scipy.io import wavfile
from transformers import Wav2Vec2Processor


class AudioExtractor:
    @classmethod
    def extract(cls, audio_path: str):
        pass


class MfccExtractor(AudioExtractor):
    nb_features = 13

    @classmethod
    def extract(cls, audio_path: str):
        x, sample_rate = librosa.load(audio_path, res_type="kaiser_fast", sr=22050 * 2)
        mfccs = librosa.feature.mfcc(y=x, sr=sample_rate, n_mfcc=cls.nb_features)
        return np.mean(mfccs, axis=0)


class Spectrogram3DExtractor(AudioExtractor):
    @classmethod
    def _log_specgram(cls, audio, sample_rate, window_size=40, step_size=20, eps=1e-10):
        nperseg = int(round(window_size * sample_rate / 1e3))
        noverlap = int(round(step_size * sample_rate / 1e3))
        freqs, _, spec = signal.spectrogram(
            audio,
            fs=sample_rate,
            window="hann",
            nperseg=nperseg,
            noverlap=noverlap,
            detrend=False,
        )
        return freqs, np.log(spec.T.astype(np.float32) + eps)

    @classmethod
    def _audio2spectrogram(cls, audio_path: str):
        samplerate, test_sound = wavfile.read(audio_path, mmap=True)
        _, spectrogram = cls._log_specgram(test_sound, samplerate)
        return spectrogram

    @classmethod
    def _get_3d_spec(cls, Sxx_in, moments=None):
        if moments is not None:
            (
                base_mean,
                base_std,
                delta_mean,
                delta_std,
                delta2_mean,
                delta2_std,
            ) = moments
        else:
            base_mean, delta_mean, delta2_mean = (0, 0, 0)
            base_std, delta_std, delta2_std = (1, 1, 1)
        h, w = Sxx_in.shape
        right1 = np.concatenate([Sxx_in[:, 0].reshape((h, -1)), Sxx_in], axis=1)[:, :-1]
        delta = (Sxx_in - right1)[:, 1:]
        delta_pad = delta[:, 0].reshape((h, -1))
        delta = np.concatenate([delta_pad, delta], axis=1)
        right2 = np.concatenate([delta[:, 0].reshape((h, -1)), delta], axis=1)[:, :-1]
        delta2 = (delta - right2)[:, 1:]
        delta2_pad = delta2[:, 0].reshape((h, -1))
        delta2 = np.concatenate([delta2_pad, delta2], axis=1)
        base = (Sxx_in - base_mean) / base_std
        delta = (delta - delta_mean) / delta_std
        delta2 = (delta2 - delta2_mean) / delta2_std
        stacked = [arr.reshape((h, w, 1)) for arr in (base, delta, delta2)]
        return np.concatenate(stacked, axis=2)

    @classmethod
    def extract(cls, audio_path: str):
        spector = cls._audio2spectrogram(audio_path)
        spector = cls._get_3d_spec(spector)
        npimg = np.transpose(spector, (2, 0, 1))
        return torch.tensor(npimg)


class Wav2Vec2Extractor(AudioExtractor):
    _processor = Wav2Vec2Processor.from_pretrained("facebook/wav2vec2-base-960h")

    @classmethod
    def extract(cls, audio_path: str):
        import torchaudio

        raw_audio, sample_rate = torchaudio.load(audio_path)
        input_features = cls._processor(
            raw_audio, return_tensors="pt", sampling_rate=sample_rate
        ).input_values
        return input_features.flatten()
