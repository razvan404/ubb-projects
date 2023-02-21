#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <queue>
#include <list>
#include <string>

using namespace std;
const int VMAX = 1e5;
const int INF = 1e7;

class Graph {
	string infile;
	string outfile;
	int V;
	int E;
	list<pair<int, int>>* adj;

public:
	Graph(string in, string out);
	void dijkstra(int src);
	bool bellmanFord();
	void johnson();
	~Graph();
};

Graph::Graph(string in, string out) {
	this->infile = in;
	this->outfile = out;

	ifstream fin(this->infile);
	if (!fin) {
		cout << "Fisierul de intrare nu a putut fi deschis!\n";
		exit(-1);
	}
	int V, E;
	fin >> V >> E;
	this->adj = new list<pair<int, int>>[V];
	this->V = V;
	this->E = E;
	for(int u, v, w; fin >> u >> v >> w; adj[u].push_back({ v, w }));
	fin.close();
}

void Graph::dijkstra(int src) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pcoada;
	vector<int> dist(V, INF);

	pcoada.push({ 0, src });		
	dist[src] = 0;
	while(!pcoada.empty()) {
		int u = pcoada.top().second;
		pcoada.pop();
		for (auto i : adj[u]) {
			int v = i.first;
			int w = i.second;
			if (dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				pcoada.push({ dist[v], v });
			}
		}
	}

	ofstream fout;
	fout.open(this->outfile, ios_base::app);
	for (int i = 0; i < V; ++i) {
		if (dist[i] == INF) {
			fout << "INF ";
		}
		else {
			fout << dist[i] << " ";
		}
	}
	fout << "\n";
}

bool Graph::bellmanFord() {
	struct edge {
		int src, dest, weight;
	};
	vector<edge> edges;
	vector<int> dist(V + 1, INF);
	dist[V] = 0;
	
	for (int i = 0; i < V; ++i) {
		edges.push_back({ V, i, 0 });
		for (auto j : adj[i]) {
			edges.push_back({ i, j.first, j.second });
		}
	}

	for (int i = 0; i < V - 1; ++i) {
		for (auto j : edges) {
			if (dist[j.src] != INF && dist[j.dest] > dist[j.src] + j.weight) {
				dist[j.dest] = dist[j.src] + j.weight;
			}
		}
	}
	
	for (int i = 0; i < V; ++i) {
		edges.pop_back();
	}

	ofstream fout(this->outfile);

	for (auto j : edges) {
		if (dist[j.src] + j.weight < dist[j.dest]) {
			return false;
		}
	}

	for (int i = 0; i < V; ++i) {
		for (auto j : adj[i]) {
			j.second += dist[i] - dist[j.first];
			fout << i << " " << j.first << " " << j.second << "\n";
		}
	}
	
	fout.close();
	return true;
}

void Graph::johnson() {
	if (this->bellmanFord() == false) {
		ofstream fout(outfile);
		fout << "-1\n";
		fout.close();
		return;
	}
	for (int i = 0; i < V; ++i) {
		this->dijkstra(i);
	}
}

Graph::~Graph() {
	delete[] adj;
}


int main(int argc, char** argv) {
	if (argc != 3) {
		cout << "Numar invalid de argumente!\n";
		cout << " Utilizare: ./p2.exe fisier1 fisier2\n";
		exit(-1);
	}

	Graph G(argv[1], argv[2]);
	G.johnson();

	return 0;
}

