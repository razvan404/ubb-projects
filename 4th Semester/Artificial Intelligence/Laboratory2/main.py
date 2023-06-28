from network_generator import NetworkGenerator
from network import Network
from network_operations import NetworkOperations
from network_tester import NetworkTester

if __name__ == '__main__':
    # NetworkTester.run()
    # NetworkGenerator.generate_random_adjacency_matrix_in_file("data/in/net8.in", 128, 2)
    network = NetworkOperations.read_network_from_in("data/in/net8.in")
    communities_count = 2
    communities_list = NetworkOperations.greedy_communities_custom(network, communities_count)
    NetworkOperations.plot_network(network, communities_list)
