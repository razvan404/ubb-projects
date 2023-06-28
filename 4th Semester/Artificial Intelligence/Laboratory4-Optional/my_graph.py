from math import sqrt
from typing import List


class Coordinate:
    def __init__(self, x: float, y: float):
        self.__x = x
        self.__y = y

    @property
    def x(self) -> float:
        return self.__x

    @property
    def y(self) -> float:
        return self.__y

    def __eq__(self, other):
        return self.__x == other.__x and self.__y == other.__y

    def distance(self, other) -> float:
        return sqrt((self.__x - other.__x) ** 2 + (self.__y - other.__y) ** 2)


class MyGraph:
    def __init__(self, no_nodes: int, coords: List[Coordinate] = None,tau0: float = 0.5):
        self.__no_nodes = no_nodes
        self.__adjacency_matrix = [[0] * no_nodes for _ in range(no_nodes)]
        for i in range(no_nodes):
            for j in range(i):
                self.__adjacency_matrix[i][j] = coords[i].distance(coords[j])
                self.__adjacency_matrix[j][i] = coords[i].distance(coords[j])
        self.__coords = coords

        self.__pheromone = [[tau0] * no_nodes for _ in range(no_nodes)]

    @property
    def no_nodes(self) -> int:
        return self.__no_nodes

    @property
    def adjacency_matrix(self) -> List[List[float]]:
        return self.__adjacency_matrix

    @property
    def coords(self) -> List[Coordinate]:
        return self.__coords

    @property
    def pheromone(self) -> List[List[float]]:
        return self.__pheromone
