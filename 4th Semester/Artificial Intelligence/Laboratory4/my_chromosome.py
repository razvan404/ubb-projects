from random import randint
from typing import List

from my_graph import MyGraph


class AbstractChromosome:
    def __init__(self, graph: MyGraph, path: List[int] = None):
        self.__graph = graph
        if path is None:
            self.__path = self.__generate_path()
            pos_rnd1 = randint(1, self.graph.no_nodes - 2)
            pos_rnd2 = randint(1, self.graph.no_nodes - 2)
            self.path[pos_rnd1], self.path[pos_rnd2] = self.path[pos_rnd2], self.path[pos_rnd1]
        else:
            self.__path = path

        self.__fitness = 0

    @property
    def graph(self):
        return self.__graph

    @property
    def path(self):
        return self.__path

    def __generate_path(self) -> List[int]:
        path = [i for i in range(self.__graph.no_nodes)]
        if self.graph.source is None or self.graph.destination is None:
            pass
        elif self.__graph.source != self.__graph.destination:
            path[self.__graph.source], path[0] = path[0], path[self.__graph.source]
            path[self.__graph.destination], path[-1] = path[-1], path[self.__graph.destination]
        else:
            path[self.__graph.source], path[0] = path[0], path[self.__graph.source]
        return path

    @property
    def fitness(self):
        return self.__fitness

    @fitness.setter
    def fitness(self, value: int):
        self.__fitness = value

    def crossover(self, other):
        pass

    def mutate(self):
        pass

    def __eq__(self, other):
        return self.__path == other.__path

    def __hash__(self):
        return hash(tuple(self.__path))

    def __lt__(self, other):
        return self.__fitness < other.__fitness


# Traveling Salesman Problem Chromosome
class TSPChromosome(AbstractChromosome):
    def crossover(self, other):
        parent1 = self.path
        parent2 = other.path
        cut = randint(1, self.graph.no_nodes - 2)
        new_path1 = parent1[:cut]
        new_path1 += [i for i in parent2 if i not in new_path1]

        new_path2 = parent2[:cut]
        new_path2 += [i for i in parent1 if i not in new_path2]

        return TSPChromosome(self.graph, path=new_path1),\
            TSPChromosome(self.graph, path=new_path2)

    def mutate(self):
        if self.graph.source is not None and self.graph.destination is not None:
            pos_rnd1 = randint(1, self.graph.no_nodes - 2)
            pos_rnd2 = randint(1, self.graph.no_nodes - 2)
        else:
            pos_rnd1 = randint(0, self.graph.no_nodes - 1)
            pos_rnd2 = randint(0, self.graph.no_nodes - 1)
        self.path[pos_rnd1], self.path[pos_rnd2] = self.path[pos_rnd2], self.path[pos_rnd1]
        return self


# Shortest Path Chromosome
class SPChromosome(AbstractChromosome):
    def crossover(self, other):
        parent1 = self.path
        parent2 = other.path

        common_members = []

        for i in range(1, len(parent1) - 1):
            for j in range(1, len(parent2) - 1):
                if parent1[i] == parent2[j]:
                    common_members.append((i, j))

        if len(common_members) == 0:
            return None, None

        cut1, cut2 = common_members[randint(0, len(common_members) - 1)]
        return SPChromosome(self.graph, parent1[:cut1] + parent2[cut2:]),\
            SPChromosome(self.graph, parent2[:cut2] + parent1[cut1:])

    def mutate(self):
        if len(self.path) < self.graph.no_nodes:
            pos_rnd = randint(1, len(self.path) - 2)
            value = self.path[pos_rnd]
            while value in self.path:
                value = randint(0, self.graph.no_nodes - 1)
            self.path[pos_rnd] = value
        return self
