# 8. Să se genereze toate numerele (în reprezentare binară) cuprinse între 1 și n. De ex. dacă n = 4, numerele sunt: 1,
# 10, 11, 100.
from typing import List


class Binary:
    def __init__(self, integer_representation: int):
        self.__integer_representation = integer_representation
        self.__string_representation = ""
        while integer_representation > 0:
            self.__string_representation = str(integer_representation % 2) + self.__string_representation
            integer_representation //= 2

    @property
    def string_representation(self):
        return self.__string_representation

    @property
    def integer_representation(self):
        return self.__integer_representation

    def increment(self):
        self.__integer_representation += 1
        index = len(self.__string_representation) - 1
        while index >= 0 and self.__string_representation[index] == '1':
            index -= 1
        if index == -1:
            self.__string_representation = '1' + '0' * len(self.__string_representation)
        else:
            self.__string_representation = self.__string_representation[:index] + '1' \
                                           + self.__string_representation[index + 1:]


def binary_list(n: int) -> List[str]:
    ans = []
    current = Binary(1)
    while current.integer_representation <= n:
        ans.append(current.string_representation)
        current.increment()
    return ans
