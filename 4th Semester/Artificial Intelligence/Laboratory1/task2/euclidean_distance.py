# 2. Să se determine distanța Euclideană între două locații identificate prin perechi de numere. De ex. distanța între
# (1,5) și (4,1) este 5.0
from math import sqrt


def euclidean_distance(point1: [int, int], point2: [int, int]) -> float:
    return sqrt((point1[0] - point2[0]) ** 2 + (point1[1] - point2[1]) ** 2)
