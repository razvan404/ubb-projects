#include <bits/stdc++.h>

using namespace std;

int V, E, **G;

bool bfs(int** rG, int s, int t, int* pi) {
	bool viz[V];
	for (int i = 0; i < V; ++i) {
		viz[i] = false;
	}

	queue<int> Q;
	Q.push(s);
	viz[s] = true;
	pi[s] = -1;

	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();

		for (int v = 0; v < V; ++v) {
			if (viz[v] == false && rG[u][v] > 0) {
				Q.push(v);
				pi[v] = u;
				viz[v] = true;
			}
		}
	}

	return viz[t] == true;
}

int fordFulkerson(int s, int t) {
	int** rezG = new int*[V];
	for (int i = 0; i < V; ++i) {
		rezG[i] = new int[V];
		for (int j = 0; j < V; ++j) {
			rezG[i][j] = G[i][j];
		}
	}

	int* pi = new int[V];
	int max_flow = 0;

	while (bfs(rezG, s, t, pi)) {
		int path_flow = INT_MAX;
		for (int v = t; v != s; v = pi[v]) {
			int u = pi[v];
			if (rezG[u][v] < path_flow) {
				path_flow = rezG[u][v];
			}
		}

		for (int v = t; v != s; v = pi[v]) {
			int u = pi[v];
			rezG[u][v] -= path_flow;
			rezG[v][u] += path_flow;
		}

		max_flow += path_flow;
	}
	
	for (int i = 0; i < V; ++i) {
		delete[] rezG[i];
	}
	delete[] rezG;
	delete[] pi;

	return max_flow;
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cout << "Invalid format!\n"
			<< " Usage: ./p1.exe INPUT_FILE OUTPUT_FILE\n";
		return EXIT_FAILURE;
	}
	
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);

	fin >> V >> E;
	G = new int*[V];
	for (int i = 0; i < V; ++i) {
		G[i] = new int[V];
		for (int j = 0; j < V; ++j) {
			G[i][j] = 0;
		}
	}
	for (int i = 0; i < E; ++i) {
		int x, y, w;
		fin >> x >> y >> w;
		G[x][y] = w;
	}

	fout << fordFulkerson(0, V - 1);

	for (int i = 0; i < V; ++i) {
		delete[] G[i];
	}
	delete[] G;

	fin.close();
	fout.close();
	return EXIT_SUCCESS;
}
