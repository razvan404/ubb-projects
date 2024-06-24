from transformers import BertForSequenceClassification, BertTokenizer as Tokenizer

BERT_MODEL_NAME = "bert-base-uncased"


def Bert(num_classes: int):
    return BertForSequenceClassification.from_pretrained(
        BERT_MODEL_NAME,
        num_labels=num_classes,
        output_attentions=False,
        output_hidden_states=False,
    )


def BertTokenizer():
    return Tokenizer.from_pretrained(BERT_MODEL_NAME)
