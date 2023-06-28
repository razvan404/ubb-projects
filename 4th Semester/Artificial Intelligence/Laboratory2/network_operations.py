from typing import List

import networkx as nx
import numpy as np
from matplotlib import pyplot as plt

from network import Network


class NetworkOperations:
    @staticmethod
    def read_network_from_in(file_name: str) -> Network:
        with open(file_name) as file_input:
            no_nodes = int(file_input.readline())
            matrix = [[int(elem) for elem in file_input.readline().split(" ")] for _ in range(no_nodes)]
            return Network(matrix)

    @staticmethod
    def read_network_from_gml(file_name: str) -> Network:
        gml_network = nx.read_gml(file_name, label='id')
        adj_matrix = nx.adjacency_matrix(gml_network)

        return Network(matrix=adj_matrix.toarray(), no_nodes=len(gml_network.nodes),
                       no_edges=len(gml_network.edges()), degrees=[degree[1] for degree in gml_network.degree])

    @staticmethod
    def greedy_communities_by_tool(network: Network) -> List[int]:
        from networkx.algorithms import community
        graph = nx.from_numpy_matrix(np.matrix(network.matrix))
        communities_generator = community.girvan_newman(graph)
        top_level_communities = next(communities_generator)
        sorted(map(sorted, top_level_communities))
        communities = [0] * network.no_nodes
        for index, community in enumerate(sorted(map(sorted, top_level_communities)), start=1):
            for node in community:
                communities[node] = index
        return communities

    @staticmethod
    def __most_crossed_edge(graph) -> (int, int):
        edge_tuple = list(nx.edge_betweenness_centrality(graph).items())  # [(edge, coefficient)]
        return max(edge_tuple, key=lambda item: item[1])[0]  # highest coefficient = most crossed in the shortest path

    @staticmethod
    def greedy_communities_custom(network: Network, no_of_communities: int = 2) -> List[int]:
        graph = nx.from_numpy_matrix(np.matrix(network.matrix))
        while len(list(nx.connected_components(graph))) < no_of_communities:
            source, destination = NetworkOperations.__most_crossed_edge(graph)
            graph.remove_edge(source, destination)

        communities = [0] * network.no_nodes
        for color, community in enumerate(nx.connected_components(graph), start=1):
            for node in community:
                communities[node] = color
        return communities

    @staticmethod
    def plot_network(network: Network, communities=None) -> None:
        if communities is None:
            communities = [1] * network.no_nodes

        graph = nx.from_numpy_matrix(np.matrix(network.matrix))
        pos = nx.spring_layout(graph)
        plt.figure(figsize=(5, 5))
        nx.draw_networkx_nodes(graph, pos, node_size=100, cmap='plasma', node_color=communities, edgecolors='black')
        nx.draw_networkx_labels(graph, pos, labels={n: str(n + 1) for n in graph.nodes()})
        nx.draw_networkx_edges(graph, pos, alpha=0.4)
        plt.show()
