from typing import List


class MyNetwork:
    def __init__(self, matrix: List[List[int]], no_nodes: int = None, no_edges: int = None, degrees: List[int] = None):
        self.__matrix = matrix
        self.__no_nodes = no_nodes if no_nodes is not None else len(matrix)

        if no_edges is not None and degrees is not None:
            self.__no_edges = no_edges
            self.__degrees = degrees
        else:
            self.__no_edges = 0
            self.__degrees = []

            for node1_index in range(self.__no_nodes):
                degree = 0
                for node2_index in range(self.__no_nodes):
                    self.__no_edges += matrix[node1_index][node2_index] if node1_index > node2_index else 0
                    degree += matrix[node1_index][node2_index]
                self.__degrees.append(degree)

    @property
    def matrix(self) -> List[List[int]]:
        return self.__matrix

    @property
    def no_nodes(self) -> int:
        return self.__no_nodes

    @property
    def no_edges(self) -> int:
        return self.__no_edges

    @property
    def degrees(self) -> List[int]:
        return self.__degrees
