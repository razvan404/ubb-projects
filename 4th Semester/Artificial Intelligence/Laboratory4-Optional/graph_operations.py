from aco import ACO
from my_graph import Coordinate, MyGraph


class GraphOperations:
    @staticmethod
    def read_graph_from_tsp(filename: str, tau0: float = None) -> MyGraph:
        with open(filename) as f:
            line = f.readline()
            while "DIMENSION" not in line:
                line = f.readline()
            no_nodes = int(line.split(': ')[1])
            while "NODE" not in line:
                line = f.readline()
            coord = []
            adjacency_matrix = [[0] * no_nodes for _ in range(no_nodes)]
            for i in range(no_nodes):
                elems = f.readline().split(' ')
                coord.append(Coordinate(float(elems[1]), float(elems[2])))
                for j in range(i):
                    cost = coord[i].distance(coord[j])
                    adjacency_matrix[i][j] = cost
                    adjacency_matrix[j][i] = cost
            if tau0 is None:
                tau0 = 1 / no_nodes ** 2
            return MyGraph(no_nodes, coord, tau0)

    @staticmethod
    def test_aco(test_name: str, generations_count: int = 50, ants_count: int = 50, tau0: float = 0.5,
                 alpha: float = 0.5, beta: float = 0.5, q0: float = 0.5, q: float = 2.0, rho: float = 0.95,
                 dynamic_rate: int = 0, generations_plot_jump: int = 10):
        print('Testing', test_name)
        graph = GraphOperations.read_graph_from_tsp('data/' + test_name, tau0)
        aco_test = ACO(graph, ants_count, alpha, beta, q0, q, rho, dynamic_rate)
        [generation, path, cost] = aco_test.find_best_path(generations_count, generations_plot_jump)
        print(f'Best generation after last dynamic change (generation {generation})'
              f'\n Path: {path + [path[0]]}'
              f'\n Cost: {cost}')
