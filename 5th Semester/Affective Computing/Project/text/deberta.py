from transformers import (
    AutoModelForSequenceClassification,
    AutoTokenizer,
)

DEBERTA_V3_MODEL_NAME = "microsoft/deberta-v3-small"


def DebertaV3(num_classes: int):
    return AutoModelForSequenceClassification.from_pretrained(
        DEBERTA_V3_MODEL_NAME, num_labels=num_classes
    )


def DebertaV3Tokenizer():
    return AutoTokenizer.from_pretrained(DEBERTA_V3_MODEL_NAME)
