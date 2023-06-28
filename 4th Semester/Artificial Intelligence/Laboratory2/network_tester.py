import os

from network_operations import NetworkOperations


class NetworkTester:
    @staticmethod
    def __test_in(test_name: str, communities_count: int = 2) -> None:
        print('\ttesting ' + test_name + ' | status: ', flush=True, end='')
        path = os.path.join(os.getcwd(), 'data/in', test_name)
        network = NetworkOperations.read_network_from_in(path)
        assert NetworkOperations.greedy_communities_custom(network, communities_count) \
               == NetworkOperations.greedy_communities_by_tool(network)
        print('success!')

    @staticmethod
    def __test_gml(test_name: str, communities_count: int = 2) -> None:
        print('\ttesting ' + test_name + ' | status: ', flush=True, end='')
        path = os.path.join(os.getcwd(), 'data/gml', test_name)
        network = NetworkOperations.read_network_from_gml(path)
        assert NetworkOperations.greedy_communities_custom(network, communities_count) \
               == NetworkOperations.greedy_communities_by_tool(network)
        print('success!')

    @staticmethod
    def run() -> None:
        print('testing .gml files:')
        NetworkTester.__test_gml('dolphins.gml')
        NetworkTester.__test_gml('football.gml')
        NetworkTester.__test_gml('karate.gml')
        NetworkTester.__test_gml('krebs.gml')

        print('testing .in files:')
        NetworkTester.__test_in('net.in')
        NetworkTester.__test_in('net2.in')
        NetworkTester.__test_in('net3.in', communities_count=3)
        NetworkTester.__test_in('net4.in', communities_count=4)
        NetworkTester.__test_in('net5.in', communities_count=5)
        NetworkTester.__test_in('net6.in')
        NetworkTester.__test_in('net7.in')
        NetworkTester.__test_in('net8.in')
