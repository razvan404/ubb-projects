# 1. Să se determine ultimul (din punct de vedere alfabetic) cuvânt care poate apărea într-un text care conține mai
# multe cuvinte separate prin ” ” (spațiu). De ex. ultimul (dpdv alfabetic) cuvânt din ”Ana are mere rosii si galbene”
# este cuvântul "si".
from typing import List


def find_maximum_char_at(words: List[str], position: int) -> chr:
    maximum_char = '\0'
    for word in words:
        if len(word) > position and word[position] > maximum_char:
            maximum_char = word[position]
    return maximum_char


def find_last_lexicographically(text: str) -> str:
    words = text.split(' ')
    current_in_word_index = 0

    while len(words) > 1:
        maximum_char_in_words = find_maximum_char_at(words, current_in_word_index)
        if maximum_char_in_words == '\0':
            return words[0]
        words_index = 0
        while words_index < len(words):
            if len(words[words_index]) <= current_in_word_index \
                    or words[words_index][current_in_word_index] != maximum_char_in_words:
                words.pop(words_index)
            else:
                words_index += 1
        current_in_word_index += 1

    return words[0]
