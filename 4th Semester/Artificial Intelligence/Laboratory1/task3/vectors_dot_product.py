# 3. Să se determine produsul scalar a doi vectori rari care conțin numere reale. Un vector este rar atunci când conține
# multe elemente nule. Vectorii pot avea oricâte dimensiuni. De ex. produsul scalar a 2 vectori unisimensionali
# [1,0,2,0,3] și [1,2,0,3,1] este 4.
from typing import List


def vectors_dot_product(vector1: List[float], vector2: List[float]) -> float:
    product = 0
    for i in range(0, len(vector1)):
        if vector1[i] and vector2[i]:
            product += vector1[i] * vector2[i]

    return product
