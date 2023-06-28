import os

from network_operations import NetworkOperations
import matplotlib


class NetworkTester:
    @staticmethod
    def __test_communities_compared_to_tool(test_name: str, read_function: callable, communities_count: int = 2) -> None:
        print('\ttesting ' + test_name + ' | status: ', flush=True, end='')
        extension = test_name.split('.')[-1]
        path = os.path.join(os.getcwd(), 'data/' + extension, test_name)
        network = read_function(path)
        assert NetworkOperations.greedy_communities_custom(network, communities_count) \
               == NetworkOperations.greedy_communities_by_tool(network)
        print('success!')

    @staticmethod
    def run_communities_compared_to_tool() -> None:
        print('testing .gml files:')
        read_from_gml_function = NetworkOperations.read_network_from_gml

        NetworkTester.__test_communities_compared_to_tool('dolphins.gml', read_function=read_from_gml_function)
        NetworkTester.__test_communities_compared_to_tool('football.gml', read_function=read_from_gml_function)
        NetworkTester.__test_communities_compared_to_tool('karate.gml', read_function=read_from_gml_function)
        NetworkTester.__test_communities_compared_to_tool('krebs.gml', read_function=read_from_gml_function)

        print('testing .in files:')
        read_from_in_file_function = NetworkOperations.read_network_from_in

        NetworkTester.__test_communities_compared_to_tool('net.in', read_function=read_from_in_file_function)
        NetworkTester.__test_communities_compared_to_tool('net2.in', read_function=read_from_in_file_function)
        NetworkTester.__test_communities_compared_to_tool('net3.in', read_function=read_from_in_file_function,
                                                          communities_count=3)
        NetworkTester.__test_communities_compared_to_tool('net4.in', read_function=read_from_in_file_function,
                                                          communities_count=4)
        NetworkTester.__test_communities_compared_to_tool('net5.in', read_function=read_from_in_file_function,
                                                          communities_count=5)
        NetworkTester.__test_communities_compared_to_tool('net6.in', read_function=read_from_in_file_function)
        NetworkTester.__test_communities_compared_to_tool('net7.in', read_function=read_from_in_file_function)
        NetworkTester.__test_communities_compared_to_tool('net8.in', read_function=read_from_in_file_function)

    @staticmethod
    def test_genetic_algorithm_vs_tool(test_name: str, read_function: callable,
                                       communities_count: int = 2,
                                       modularity_function: callable = NetworkOperations.z_modularity,
                                       generations_count: int = 100):
        extension = test_name.split('.')[-1]
        path = os.path.join(os.getcwd(), 'data/' + extension, test_name)
        network = read_function(path)

        communities_tool = NetworkOperations.greedy_communities_by_tool(network)
        the_best_chromosome = NetworkOperations.apply_genetic_algorithm(network, communities_count,
                                                                        generations_count=generations_count,
                                                                        modularity_function=modularity_function)
        count = 0
        for x, y in zip(communities_tool, the_best_chromosome.representation):
            if x != y:
                count += 1
        print('For network: ', test_name, ' there are ', count, ' differences')
        print('Best chromosome: \nRepresentation:', the_best_chromosome.representation,
              '\nRepartition:', the_best_chromosome.repartition,
              '\nFitness:', the_best_chromosome.fitness)

    @staticmethod
    def test_genetic_algorithm(test_name: str,
                               read_function: callable,
                               communities_count: int = 2,
                               modularity_function: callable = NetworkOperations.simple_modularity,
                               population_size: int = 100,
                               mutation_probability: float = 0.2):
        extension = test_name.split('.')[-1]
        path = os.path.join(os.getcwd(), 'data/' + extension, test_name)
        network = read_function(path)
        the_best_chromosome, generations = NetworkOperations\
            .apply_genetic_algorithm(network, communities_count,
                                     population_size=population_size,
                                     modularity_function=modularity_function,
                                     mutation_probability=mutation_probability)
        matplotlib.use('TkAgg')
        NetworkOperations.plot_network(network, communities=the_best_chromosome.representation,
                                       text="Best chromosome for test '" + test_name + "'\nafter "
                                            + str(generations) + " generations")

        print('=' * 50, '\nBest chromosome: \nRepresentation:', the_best_chromosome.representation,
              '\nRepartition:', the_best_chromosome.repartition,
              '\nFitness:', the_best_chromosome.fitness, '\n', '=' * 50)
        print('Communities:')
        communities = [[] for _ in range(communities_count)]
        for index, community in enumerate(the_best_chromosome.representation):
            communities[community - 1].append(index + 1)
        for community in communities:
            print(community)
        print('=' * 50)
