from random import randint
from typing import List, Union

import matplotlib.pyplot as plt

from ant import Ant
from my_graph import MyGraph


class ACO:
    def __init__(self, graph: MyGraph, ants_count: int, alpha: float = 0.5,
                 beta: float = 0.5, q0: float = 0.1, q: float = 2, rho: float = 0.95, dynamic_rate: int = 0):
        self.__graph = graph
        self.__ants_count = ants_count
        self.__alpha = alpha
        self.__beta = beta
        self.__q0 = q0
        self.__q = q
        self.__rho = rho
        self.__dynamic_rate = dynamic_rate
        self.__removed_edges = []

    def __generate_ants(self, best_path_last_generation: List[int] = None) -> List[Ant]:
        ants = [Ant(self.__graph, self.__alpha, self.__beta, self.__q0) for _ in range(self.__graph.no_nodes)]
        if best_path_last_generation is not None:
            ants[0].path = best_path_last_generation
        return ants

    def __update_pheromones_before_explore(self):
        for i in range(self.__graph.no_nodes):
            for j in range(self.__graph.no_nodes):
                self.__graph.pheromone[i][j] *= 1 - self.__rho

    def __update_pheromone_after_ant(self, ant: Ant) -> None:
        for i in range(self.__graph.no_nodes):
            for j in range(self.__graph.no_nodes):
                self.__graph.pheromone[i][j] += ant.pheromone_delta[i][j]

    def __remove_edge_from_best_path(self, path: List[int]):
        i = randint(0, len(path) - 2)
        self.__graph.adjacency_matrix[path[i]][path[i + 1]] = 0
        self.__graph.adjacency_matrix[path[i + 1]][path[i]] = 0
        self.__removed_edges.append((path[i], path[i + 1]))
        print(f'Removed edge [{path[i]}, {path[i + 1]}]')

    def plot_path(self, path: List[int], title: str = None):
        path = path + [path[0]]
        x = []
        y = []
        for coord in self.__graph.coords:
            x.append(coord.x)
            y.append(coord.y)
        plt.plot(x, y, '.', markersize=10)
        for i in range(len(path) - 1):
            plt.arrow(x[path[i]], y[path[i]], x[path[i + 1]] - x[path[i]], y[path[i + 1]] - y[path[i]],
                      color='g', head_width=0.1)
            # plt.annotate(i, (x[i], y[i]), textcoords="offset points", xytext=(2, -2), ha='center')

        for edge in self.__removed_edges:
            plt.arrow(x[edge[0]], y[edge[0]], x[edge[1]] - x[edge[0]], y[edge[1]] - y[edge[0]], color='r')

        if title is not None:
            plt.title(title)

        plt.show()

    def plot_evolution(self, generations: List[int], costs: List[float], title: str):
        plt.plot(generations, costs, color='b')
        plt.xlabel('generations axis')
        plt.ylabel('costs axis')
        plt.title(title)
        plt.show()

    def find_best_path(self, generations_count: int, generations_plot_jump: int) -> [List[int], float]:
        best_cost = float('INF')
        best_path = None
        best_generation = 0
        generations = [i for i in range(generations_count)]
        costs = []
        for generation in generations:
            if self.__dynamic_rate != 0 and generation % self.__dynamic_rate == 0 and generation != 0:
                self.__remove_edge_from_best_path(best_path)
                best_cost = float('INF')

            ants = self.__generate_ants()

            best_cost_this_generation = ants[0].cost
            best_path_this_generation = ants[0].path

            self.__update_pheromones_before_explore()
            for ant in ants:
                if ant.cost < best_cost:
                    best_cost_this_generation = ant.cost
                    best_path_this_generation = ant.path
                ant.update_pheromone_delta(self.__q)
                self.__update_pheromone_after_ant(ant)

            costs.append(best_cost_this_generation)

            if best_cost_this_generation < best_cost:
                best_cost = best_cost_this_generation
                best_path = best_path_this_generation
                best_generation = generation

            print(f'Generation {generation}:\n Best path: {best_path_this_generation + [best_path_this_generation[0]]}'
                  f'\n Cost: {best_cost_this_generation}\n\n')
            if generation % generations_plot_jump == 0:
                self.plot_path(best_path_this_generation, f'Best path in generation {generation}\n'
                                                          f'(cost: {best_cost_this_generation})')

        self.plot_evolution(generations, costs, f'Evolution in {generations_count} generations')
        self.plot_path(best_path, f'Best path in {generations_count} generations (generation {best_generation})'
                                  f'\n(cost: {best_cost})')
        return best_generation, best_path, best_cost
