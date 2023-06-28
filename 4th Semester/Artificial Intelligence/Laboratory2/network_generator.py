from typing import List

import networkx as nx


class NetworkGenerator:
    @staticmethod
    def generate_random_adjacency_matrix(nodes_count: int, community_count: int,
                                         within_communities_probability: int = 0.3,
                                         between_communities_probability: int = 0.01) -> List[List[int]]:
        sizes = [nodes_count // community_count] * community_count
        sizes[-1] += nodes_count % community_count
        graph = nx.generators.random_partition_graph(sizes, p_in=within_communities_probability,
                                                     p_out=between_communities_probability)
        return nx.to_numpy_array(graph)

    @staticmethod
    def generate_random_adjacency_matrix_in_file(file_name: str, nodes_count: int, community_count: int,
                                                 within_communities_probability: int = 0.2,
                                                 between_communities_probability: int = 0.01) -> None:
        with open(file_name, "w") as file_output:
            graph = NetworkGenerator.generate_random_adjacency_matrix(nodes_count, community_count,
                                                                      within_communities_probability,
                                                                      between_communities_probability)
            file_output.write(str(len(graph)) + '\n')
            for line in graph:
                for index in range(len(line) - 1):
                    file_output.write(str(int(line[index])) + ' ')
                file_output.write(str(int(line[-1])) + '\n')
