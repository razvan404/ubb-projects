from graph_generator import GraphGenerator
from graph_operations import GraphOperations

if __name__ == '__main__':
    # GraphGenerator.print_random_directed_weighted_graph_in_file("data/hard1.txt", 400)
    graph = GraphOperations.read_graph("data/hard2.txt", route=None)
    GraphOperations.apply_genetic_algorithm(graph, population_size=100, algorithm='TSP',
                                            population_type='set',
                                            generations_plot_step=100, generations_stop_step=500,
                                            node_size=10, plot_graph=False)
