# 4. Să se determine cuvintele unui text care apar exact o singură dată în acel text. De ex. cuvintele care apar o
# singură dată în ”ana are ana are mere rosii ana" sunt: 'mere' și 'rosii'.
from typing import List


def single_occurrence(text: str) -> List[str]:
    words = text.split(' ')
    words_map = {}

    for word in words:
        words_map[word] = words_map.get(word) is None

    return [key for key in words_map.keys() if words_map[key] is True]
