from typing import List


class MyGraph:
    def __init__(self, no_nodes: int, adjacency_matrix: List[List[int]], source: int = None, destination: int = None):
        self.__no_nodes = no_nodes
        self.__adjacency_matrix = adjacency_matrix
        if source is None and destination is None:
            self.__source = None
            self.__destination = None
        elif not isinstance(source, int) or not isinstance(destination, int):
            raise ValueError('Illegal argument given to MyGraph constructor!')
        else:
            self.__source = source - 1
            self.__destination = destination - 1

    @property
    def no_nodes(self) -> int:
        return self.__no_nodes

    @property
    def adjacency_matrix(self) -> List[List[int]]:
        return self.__adjacency_matrix

    @property
    def source(self) -> int:
        return self.__source

    @property
    def destination(self) -> int:
        return self.__destination
