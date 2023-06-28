from random import randint, random
from typing import List

from my_graph import MyGraph


class Ant:
    def __init__(self, graph: MyGraph, alpha: float, beta: float, q0: float):
        self.__graph = graph
        self.__pheromone_delta = []
        self.__path = [randint(0, graph.no_nodes - 1)]
        self.__not_visited = [i for i in range(graph.no_nodes)]
        self.__not_visited.remove(self.__path[-1])

        for _ in range(graph.no_nodes - 1):
            selected = self.__select_next_in_path(alpha, beta, q0)
            self.__path.append(selected)
            self.__not_visited.remove(selected)

        self.__cost = self.__calculate_cost()

    def __calculate_cost(self):
        cost = 0.0
        path = self.__path + [self.__path[0]]
        for i in range(len(path) - 1):
            road_cost = self.__graph.adjacency_matrix[path[i]][path[i + 1]]
            if road_cost == 0:
                cost += 1000000
            else:
                cost += road_cost
        return cost

    @property
    def cost(self) -> float:
        return self.__cost

    @property
    def path(self) -> List[int]:
        return self.__path

    @path.setter
    def path(self, value: List[int]):
        self.__path = value
        self.__cost = self.__calculate_cost()

    @property
    def pheromone_delta(self):
        return self.__pheromone_delta

    def __hash__(self):
        return hash(tuple(self.__path))

    def __eq__(self, other):
        return self.__path == other.__path

    def __select_next_in_path(self, alpha: float, beta: float, q0: float) -> int:
        last = self.__path[-1]

        if random() < q0:
            results = [0] * self.__graph.no_nodes
            results_sum = 0

            for i in self.__not_visited:
                if self.__graph.adjacency_matrix[last][i] != 0:
                    results[i] = (self.__graph.pheromone[last][i] ** alpha) * \
                                 ((1 / self.__graph.adjacency_matrix[last][i]) ** beta)
                    results_sum += results[i]

            possible_nodes = []
            if results_sum == 0:
                return self.__not_visited[0]
            for i in self.__not_visited:
                possible_nodes.append((i, results[i] / results_sum))
            possible_nodes.sort(reverse=True, key=lambda x: x[1])

            rand = random()

            for node in possible_nodes:
                rand -= node[1]
                if rand <= 0:
                    return node[0]
            return -1

        else:
            possible_nodes = []
            for i in self.__not_visited:
                result = float('INF')
                if self.__graph.adjacency_matrix[last][i] != 0:
                    result = (self.__graph.pheromone[last][i] ** alpha) * \
                            ((1 / self.__graph.adjacency_matrix[last][i]) ** beta)
                possible_nodes.append((i, result))
            return max(possible_nodes, key=lambda x: x[1])[0]

    def update_pheromone_delta(self, q: float):
        self.__pheromone_delta = [[0] * self.__graph.no_nodes for _ in range(self.__graph.no_nodes)]
        for k in range(0, len(self.__path) - 1):
            i = self.__path[k]
            j = self.__path[k + 1]
            self.__pheromone_delta[i][j] = q / self.__cost

    def __lt__(self, other):
        return self.__cost < other.__cost
