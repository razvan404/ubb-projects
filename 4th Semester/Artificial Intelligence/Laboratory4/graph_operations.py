from typing import List, Union

from genetic_algorithm import GeneticAlgorithm
from my_chromosome import TSPChromosome, SPChromosome
from my_graph import MyGraph

import networkx as nx
import numpy as np
import matplotlib.pyplot as plt
import matplotlib


class GraphOperations:
    @staticmethod
    def read_graph(file: str, route=None) -> MyGraph:
        """
        Reads a graph from a given file
        :param file: the file to read the graph from
        :param route: the route, should be:
         1) 'file' if the source and destination will be read from the file,
         2) an integer if the source and the destination are the same,
         3) a pair of integers with both of them,
         4) nothing if there is not an exact source / destination
        :return: the graph read from the file
        """
        with open(file) as input_file:
            no_nodes = int(input_file.readline())
            adjacency_matrix = [[int(elem) for elem in input_file.readline().split(',')]
                                for _ in range(no_nodes)]

            if route is 'file':
                source = int(input_file.readline())
                destination = int(input_file.readline())
            elif isinstance(route, int):
                source = route
                destination = route
            elif isinstance(route, (int, int)):
                source, destination = route
            else:
                source, destination = None, None

            return MyGraph(no_nodes, adjacency_matrix, source, destination)

    @staticmethod
    def plot_graph(given_graph: MyGraph, path: List[int] = None, text: str = None, node_size: int = 200):
        if path is None:
            path = [i for i in range(given_graph.no_nodes)]
        graph = nx.DiGraph(np.matrix(given_graph.adjacency_matrix))
        path_edges = [(path[i], path[i + 1]) for i in range(len(path) - 1)]

        pos = nx.spring_layout(graph)
        plt.figure(figsize=(5, 5))
        nx.draw_networkx_nodes(graph, pos, node_size=node_size, cmap='plasma',
                               node_color=[i for i in range(given_graph.no_nodes)], edgecolors='black')
        if node_size > 100:
            nx.draw_networkx_labels(graph, pos, labels={i: str(i + 1) for i in range(given_graph.no_nodes)})
        nx.draw_networkx_edges(graph, pos, alpha=0.4, edge_color='black', width=1)
        # nx.draw_networkx_edge_labels(graph, pos, edge_labels={
        #     (i, j): given_graph.adjacency_matrix[i][j]
        #     for i in range(given_graph.no_nodes) for j in range(given_graph.no_nodes)
        # }, font_color='orange')
        nx.draw_networkx_edges(graph, pos, alpha=0.8, edgelist=path_edges, edge_color='red', width=2)

        if text is not None:
            plt.title(text, horizontalalignment='center')
        plt.show()

    @staticmethod
    def apply_genetic_algorithm(graph: MyGraph, population_size: int = 100, algorithm: str = None,
                                population_type: str = 'set',
                                generations_count: int = None, generations_plot_step: int = 10,
                                generations_stop_step: int = 100, node_size: int = 50,
                                plot_graph: bool = True):
        if algorithm is None:
            raise ValueError('Select an algorithm!')
        elif algorithm == 'TSP':
            ga = GeneticAlgorithm[TSPChromosome](graph, constructor=lambda x, s=None: TSPChromosome(x),
                                                 algorithm=algorithm, population_size=population_size,
                                                 population_type=population_type)
        elif algorithm == 'SP':
            ga = GeneticAlgorithm[SPChromosome](graph, constructor=lambda x, s=None: SPChromosome(x),
                                                algorithm=algorithm, population_size=population_size,
                                                population_type=population_type)
        else:
            raise ValueError('Invalid algorithm!')

        if generations_count is not None and generations_count < 0:
            raise ValueError('Invalid number of generations!')

        current_generation = 0
        best_chromosomes = None
        while generations_count is None or current_generation <= generations_count:
            best_chromosomes_current_generation = ga.best_chromosomes()
            print('Best chromosomes in generation ' + str(current_generation) + ':')
            for i, chromosome in enumerate(best_chromosomes_current_generation):
                if algorithm == 'TSP':
                    print('- path ' + str(i + 1) + ':', [i + 1 for i in chromosome.path] + [chromosome.path[0] + 1])
                else:
                    print('- path ' + str(i + 1) + ':', [i + 1 for i in chromosome.path])
            print('Fitness:', best_chromosomes_current_generation[0].fitness, end='\n\n')

            if best_chromosomes is None or \
                    best_chromosomes_current_generation[0].fitness < best_chromosomes[0].fitness \
                    or len(best_chromosomes_current_generation) > len(best_chromosomes):
                best_chromosomes = best_chromosomes_current_generation

            if current_generation % generations_plot_step == 0:
                if algorithm == 'TSP':
                    path = best_chromosomes[0].path + [best_chromosomes[0].path[0] + 1]
                else:
                    path = best_chromosomes[0].path
                if plot_graph:
                    GraphOperations.plot_graph(graph, path=path,
                                               text='Best chromosome in generation ' + str(current_generation),
                                               node_size=node_size)

            if generations_count is None and current_generation % generations_stop_step == 0 and current_generation > 0:
                continue_value = None
                while continue_value is None:
                    inp = input('Do you want to continue? [Y/n]: ')
                    continue_value = True if inp == 'Y' else False if inp == 'n' else None
                if not continue_value:
                    break

            current_generation += 1
            ga.next_generation()

        if algorithm == 'TSP':
            path = best_chromosomes[0].path + [best_chromosomes[0].path[0]]
        else:
            path = best_chromosomes[0].path
        if plot_graph:
            matplotlib.use('TkAgg')
            GraphOperations.plot_graph(graph, path=path,
                                       text='Best chromosome in ' + str(current_generation) + ' generations:',
                                       node_size=node_size)
        print('=' * 50, '\nBest chromosomes in', current_generation, 'generations:')
        for index, chromosome in enumerate(best_chromosomes):
            if algorithm == 'SP':
                print('- path ' + str(index + 1) + ':', [i + 1 for i in chromosome.path])
            else:
                print('- path ' + str(index + 1) + ':', [i + 1 for i in chromosome.path] + [chromosome.path[0] + 1])
        print('Fitness:', best_chromosomes[0].fitness, '\n', '=' * 50)
