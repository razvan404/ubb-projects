#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using std::ifstream;
using std::ofstream;
using std::vector;
using std::queue;

int V, E; // numarul de varfuri si de arce
vector<vector<int>> G; // graful retinut ca matrice de adiacenta


bool BreadthFirstSearch(vector<vector<int>>& residual, int s, int t, vector<int>& parent) {
	// Initializam vectorul cu noduri vizitate, initial toate valorile vor fi false
	vector<bool> visited(V, false);

	queue<int> Q;
	Q.push(s);
	visited[s] = true; // Marcam nodul sursa ca fiind vizitat
	parent[s] = -1; // Nodul sursa nu va avea un parinte

	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();

		for (int v = 0; v < V; ++v) {
			// Cautam nodurile nevizitate si cu ponderi nenule, daca am gasit unul, il punem in coada si continuam parcurgerea
			if (visited[v] == false && residual[u][v] != 0) {
				Q.push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}

	return visited[t] == true;
}


int FordFulkerson(int s, int t) {
	// Initializam graful rezidual care initial va fi egal cu graful original
	vector<vector<int>> residual_graph = G;
	// Initializam vectorul de parinti
	vector<int> parent(V);
	// In max_flow vom retine fluxul maxim
	int max_flow = 0;
	
	// Cat timp vom putea ajunge de la nodul sursa la nodul destinatie, fluxul maxim va creste
	while (BreadthFirstSearch(residual_graph, s, t, parent)) {
		// In current_flow vom retine fluxul minim care trece prin nodurile vizitate de pana acum
		int current_flow = INT_MAX;

		int v = t;
		while (v != s) {
			int u = parent[v];
			if (residual_graph[u][v] < current_flow) {
				current_flow = residual_graph[u][v];
			}
			v = parent[v];
		}

		// Modificam ponderile in graful rezidual
		v = t;
		while (v != s) {
			int u = parent[v];
			residual_graph[u][v] -= current_flow;
			residual_graph[v][u] += current_flow;
			v = parent[v];
		}

		// Actualizam fluxul maxim
		max_flow += current_flow;
	}

	return max_flow;
}


int main(void) {
	ifstream fin("Data.txt");
	ofstream fout("Output.txt");

	fin >> V >> E;
	G.resize(V, vector<int>(V));

	for (int i = 0; i < E; ++i) {
		int x, y, w;
		fin >> x >> y >> w;
		G[x][y] = w;
	}

	fout << FordFulkerson(0, V - 1);

	fin.close();
	fout.close();
	return EXIT_SUCCESS;
}
