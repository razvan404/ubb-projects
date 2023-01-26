#include <iostream>
#include <fstream>
#include <cmath>
#include <queue>
#include <list>

using namespace std;

double distance(pair<int, int> coord1, pair<int, int> coord2) {
	return sqrt((coord1.first - coord2.first) * (coord1.first - coord2.first) + (coord1.second - coord2.second) * (coord1.second - coord2.second));
}

class Graph {
	string in, out;
	const double INF = 1e7;
	int V, E;
	list<pair<int, double>>* adj;

public:
	Graph(string in) {
		this->in = in;
		ifstream fin(this->in);
		if (!fin) {
			cout << "Fisierul de intrare nu a putut fi deschis!\n";
			exit(-1);
		}

		int V, E;
		fin >> V >> E;
		this->adj = new list<pair<int, double>>[V + 1];
		pair<int, int>* coords = new pair<int, int>[V + 1];
		this->V = V;
		this->E = E;
		
		if (!this->adj || !coords) {
			exit(-1);
		}

		for (int i = 1; i <= V; i++) {
			fin >> coords[i].first >> coords[i].second;
		}
		int u, v;
		for (int i = 1; i <= E; i++) {
			fin >> u >> v;
			adj[u].push_back({ v, distance(coords[v], coords[u]) });
		}
		delete[] coords;
		fin.close();
	}

	void Dijkstra(int src, int dest) {
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pcoada;
		vector<double> dist(V + 1, INF);
		vector<int> tata(V + 1, 0);

		pcoada.push({ 0, src });
		dist[src] = 0;
		tata[src] = -1;
		while (!pcoada.empty()) {
			int u = pcoada.top().second;
			pcoada.pop();

			for (const auto& i : adj[u]) {
				int v = i.first;
				double w = i.second;
				if (dist[v] > dist[u] + w) {
					tata[v] = u;
					dist[v] = dist[u] + w;
					pcoada.push({ dist[v], v });
				}
			}
		}

		if (dist[dest] == INF) {
			cout << "NO WAY BETWEEN THE 2 CITIES!";
		}
		else {
			cout << "OPTIMAL WAY: ";
			vector<int> drum;
			int curent = dest;
			while (curent != -1) {
				drum.insert(drum.begin(), curent);
				curent = tata[curent];
			}
			for (const auto& i : drum) {
				cout << i << " ";
			}
		}
		cout << "\n";
	}
	~Graph() {
		delete[] adj;
	};
};

int main() {
	Graph G("input.txt");
	int src = 0, dest = 0;
	cout << " START: ";
	cin >> src;
	cout << " DESTINATION: ";
	cin >> dest;
	G.Dijkstra(src, dest);

	return EXIT_SUCCESS;
}