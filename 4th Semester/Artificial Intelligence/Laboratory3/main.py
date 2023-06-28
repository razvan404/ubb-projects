from network_operations import NetworkOperations
from network_tester import NetworkTester

if __name__ == '__main__':
    NetworkTester.test_genetic_algorithm('net7.in', NetworkOperations.read_network_from_in,
                                         communities_count=2,
                                         modularity_function=NetworkOperations.modularity_density,
                                         population_size=100,
                                         mutation_probability=0.3)
