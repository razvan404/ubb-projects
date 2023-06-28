from typing import List

import networkx as nx
import numpy as np
from matplotlib import pyplot as plt

from genetic_algorithm import GeneticAlgorithm
from my_chromosome import MyChromosome
from my_network import MyNetwork


class NetworkOperations:
    @staticmethod
    def read_network_from_in(file_name: str) -> MyNetwork:
        with open(file_name) as file_input:
            no_nodes = int(file_input.readline())
            matrix = [[int(elem) for elem in file_input.readline().split(" ")] for _ in range(no_nodes)]
            return MyNetwork(matrix)

    @staticmethod
    def read_network_from_gml(file_name: str) -> MyNetwork:
        gml_network = nx.read_gml(file_name, label='id')
        adj_matrix = nx.adjacency_matrix(gml_network)

        return MyNetwork(matrix=adj_matrix.toarray(), no_nodes=len(gml_network.nodes),
                         no_edges=len(gml_network.edges()), degrees=[degree[1] for degree in gml_network.degree])

    @staticmethod
    def greedy_communities_by_tool(network: MyNetwork) -> List[int]:
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
    def greedy_communities_custom(network: MyNetwork, no_of_communities: int = 2) -> List[int]:
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
    def plot_network(network: MyNetwork, communities: List[int] = None, text: str = None) -> None:
        if communities is None:
            communities = [1] * network.no_nodes

        graph = nx.from_numpy_matrix(np.matrix(network.matrix))
        pos = nx.spring_layout(graph)
        plt.figure(figsize=(5, 5))
        nx.draw_networkx_nodes(graph, pos, node_size=50, cmap='plasma', node_color=communities, edgecolors='black')
        nx.draw_networkx_edges(graph, pos, alpha=0.4)
        if text is not None:
            plt.title(text, horizontalalignment='center')
        plt.show()

    @staticmethod
    def simple_modularity(network: MyNetwork, communities: List[int], communities_count: int = None) -> float:
        """
        Calculates the degree to which a network's components could be divided into smaller modules
        The formula for this is:
            1/2m * SUM[of i and j nodes of graph A] (A[i][j] - degree[i]*degree[j] / 2m) * sigma(i, j)
        where A is the adjacency matrix, m is the number of edges, degree is the vector of degrees, and
        sigma is Kronecker function, which tell us if i and j are in the same community
        :param network: the network to calculate the modularity of
        :param communities: The found communities so far
        :return: the modularity of the network's communities
        """
        edges_squared = 2 * network.no_edges
        modularity = 0.0
        for i in range(0, network.no_nodes):
            for j in range(0, network.no_nodes):
                if communities[i] == communities[j]:
                    modularity += network.matrix[i][j] - network.degrees[i] * network.degrees[j] / edges_squared
        return modularity / edges_squared

    @staticmethod
    def modularity_density(network: MyNetwork, communities: List[int], communities_count: int, lambda_density: int = 0.5) -> float:
        graph = nx.from_numpy_matrix(np.matrix(network.matrix))
        my_communities = [[] for _ in range(communities_count)]
        for i in range(network.no_nodes):
            my_communities[communities[i] - 1].append(i)
        modularity = 0.0
        for community in my_communities:
            subgraph = nx.subgraph(graph, community)
            if subgraph.number_of_nodes() == 0:
                continue
            interior_degrees_sum = 0
            exterior_degrees_sum = 0
            for node in subgraph.nodes:
                interior_degrees_sum += subgraph.degree(node)
                exterior_degrees_sum += graph.degree(node) - subgraph.degree(node)
            modularity += (2 * lambda_density * interior_degrees_sum - 2 * (1 - lambda_density) *
                           exterior_degrees_sum) / subgraph.number_of_nodes()
        return modularity

    @staticmethod
    def z_modularity(network: MyNetwork, communities: List[int], communities_count: int) -> float:
        graph = nx.from_numpy_matrix(np.matrix(network.matrix))
        my_communities = [[] for _ in range(communities_count)]
        for i in range(network.no_nodes):
            my_communities[communities[i] - 1].append(i)
        internal_edges_fraction = 0
        degree_ratio_squared = 0
        for community in my_communities:
            subgraph = nx.subgraph(graph, community)
            grades_sum = sum([graph.degree(node) for node in subgraph.nodes])
            degree_ratio_squared += (grades_sum / (2 * network.no_edges)) ** 2
            internal_edges_fraction += subgraph.number_of_nodes() / network.no_nodes

        if degree_ratio_squared <= 0 or degree_ratio_squared >= 1:
            return 0.0
        else:
            return (internal_edges_fraction - degree_ratio_squared)\
                / np.sqrt(degree_ratio_squared * (1 - degree_ratio_squared))

    @staticmethod
    def apply_genetic_algorithm(network: MyNetwork,
                                communities_count: int,
                                modularity_function: callable,
                                population_size: int,
                                mutation_probability: float) -> (MyChromosome, int):
        best_chromosomes = []
        ga = GeneticAlgorithm(network, communities_count,
                              population_size=population_size,
                              modularity_function=modularity_function)
        GeneticAlgorithm.mutation_prob = mutation_probability

        generation = 0

        while True:
            ga.next_generation()
            best_chromosome = ga.best_chromosome()
            print('Best solution in generation: ' + str(generation) +
                  ':\nRepresentation: ' + str(best_chromosome.representation) +
                  '\nRepartition: ' + str(best_chromosome.repartition) +
                  '\nFitness: ' + str(best_chromosome.fitness), end='\n\n')
            best_chromosomes.append(best_chromosome)
            if generation % 3 == 0:
                NetworkOperations.plot_network(network, best_chromosome.representation,
                                               text="Generation " + str(generation))
            generation += 1
            if generation % 25 == 0:
                break_bool = None
                while break_bool is None:
                    inp = input("Do you want to continue? [Y/n]: ")
                    break_bool = True if inp == 'n' else False if inp == 'Y' else None
                if break_bool:
                    break

        the_best = max(best_chromosomes)
        return the_best, generation
