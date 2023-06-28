from graph_operations import GraphOperations


def print_hi(name):
    print(f'Hi, {name}')


if __name__ == '__main__':
    GraphOperations.test_aco(test_name='att48.tsp', generations_count=150, ants_count=100, tau0=0.5,
                             alpha=0.1, beta=2.0, q0=0.5, q=3.0, rho=0.7, dynamic_rate=31, generations_plot_jump=50)
