import random
from typing import List

import numpy as np
import networkx as nx

from my_graph import MyGraph


class GraphGenerator:
    @staticmethod
    def __shortest_path(adj_matrix: List[List[int]], source: int, destination: int) -> (List[int], int):
        graph = nx.from_numpy_array(np.array(adj_matrix))
        return nx.shortest_path(graph, source, destination, weight='weight'), \
            nx.shortest_path_length(graph, source, destination, weight='weight')

    @staticmethod
    def generate_directed_weighted_graph(no_nodes: int) -> (MyGraph, List[int]):
        adj_matrix = [[0] * no_nodes for _ in range(no_nodes)]
        for i in range(no_nodes):
            for j in range(no_nodes):
                # Generate a random weight between 0 and 90 with a chance of 40%
                if i != j and random.random() < 0.4:
                    adj_matrix[i][j] = random.randint(0, 90)

        path = np.random.permutation([i for i in range(no_nodes)])
        path_sum = 0
        for i in range(len(path) - 1):
            adj_matrix[path[i]][path[i + 1]] = random.randint(3, 20)
            path_sum += adj_matrix[path[i]][path[i + 1]]
        adj_matrix[path[-1]][path[0]] = random.randint(3, 20)
        path_sum += adj_matrix[path[-1]][path[0]]

        return MyGraph(no_nodes, adj_matrix), path, path_sum

    @staticmethod
    def print_random_directed_weighted_graph_in_file(filename: str, no_nodes: int):
        with open(filename, 'w') as f:
            graph, path, path_sum = GraphGenerator.generate_directed_weighted_graph(no_nodes)
            f.write(str(graph.no_nodes) + '\n')
            for i in range(graph.no_nodes):
                line = ''
                for j in range(graph.no_nodes):
                    line += str(graph.adjacency_matrix[i][j]) + ','
                f.write(line[:-1] + '\n')
            f.write(str(path[0] + 1) + '\n' + str(path[-2] + 1) + '\n')
            f.write('TSP path (random chosen, may be minimum): ' + str([i + 1 for i in path] + [path[0] + 1]) + '\n')
            f.write('TSP sum: ' + str(path_sum) + '\n')
            sp, sp_len = GraphGenerator.__shortest_path(graph.adjacency_matrix, path[0], path[-2])
            f.write('Shortest path: ' + str([i + 1 for i in sp]) + '\n')
            f.write('Shortest path length: ' + str(sp_len) + '\n')
