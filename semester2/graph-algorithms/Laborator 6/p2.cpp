#include <bits/stdc++.h>

using namespace std;

int V, E, **G, **FLUX;

void pompare(int* excess, int u, int v) {
	int delta;
	if (excess[u] < G[u][v] - FLUX[u][v]) {
		delta = excess[u];
	}
	else {
		delta = G[u][v] - FLUX[u][v];
	}

	FLUX[u][v] += delta;
	FLUX[v][u] -= delta;
	excess[u] -= delta;
	excess[v] += delta;
}

void inalta(int* height, int u) {
	int minHeight = INT_MAX;
	for (int v = 0; v < V; ++v) {
		if (G[u][v] - FLUX[u][v] > 0) {
			minHeight = minHeight < height[v] ? minHeight : height[v];
		}
	}
	height[u] = minHeight + 1;
}

void descarca(int* height, int* excess, int* current, int u) {
	while (excess[u] > 0) {
		if (current[u] == V) {
			inalta(height, u);
			current[u] = 0;

			continue;
		}

		int v = current[u];
		if (G[u][v] - FLUX[u][v] > 0 && height[u] == height[v] + 1) {
			pompare(excess, u, v);
		}
		else {
			current[u]++;
		}
	}
}

int pompare_topologica(int s, int d) {
	list<int> L;
	L.clear();

	int* height = new int[V];
	int* excess = new int[V];
	int* current = new int[V];

	height[s] = V;
	excess[s] = INT_MAX;

	for (int v = 0; v < V; ++v) {
		if (v != s) {
			pompare(excess, s, v);
		}
		if (v != s && v != d) {
			L.push_back(v);
		}
	}
	
	auto it = L.begin();
	while (it != L.end()) {
		int u = *it;
		int old_height = height[u];

		descarca(height, excess, current, u);

		if (height[u] > old_height) {
			L.splice(L.begin(), L, it);
		}
		it++;
	}

	int fluxMin = excess[d];

	delete[] current;
	delete[] excess;
	delete[] height;

	return fluxMin;
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cout << "Invalid input!\n"
			<< " Usage: p2.exe INPUT_FILE OUTPUT_FILE";
		return EXIT_FAILURE;
	}
	
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);
	
	fin >> V >> E;
	G = new int*[V];
	FLUX = new int*[V];

	for (int i = 0; i < V; ++i) {
		G[i] = new int[V];
		FLUX[i] = new int[V];
		for (int j = 0; j < V; ++j) {
			G[i][j] = 0;
			FLUX[i][j] = 0;
		}
	}
	
	for (int j = 0; j < E; ++j) {
		int x, y, w;
		fin >> x >> y >> w;
		G[x][y] = w;
	}
	
	fout << pompare_topologica(0, V - 1);

	for (int i = 0; i < V; ++i) {
		delete[] FLUX[i];
		delete[] G[i];
	}
	delete[] FLUX;
	delete[] G;

	fin.close();
	fout.close();
	return EXIT_SUCCESS;
}

