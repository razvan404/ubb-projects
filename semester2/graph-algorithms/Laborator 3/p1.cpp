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
	int V, E, S;
	list<pair<int, int>> *adj;

public:
	Graph(string in, string out);
	void dijkstra();
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
	int V, E, S;
	fin >> V >> E >> S;
	this->V = V;
	this->E = E;
	this->S = S;
	this->adj = new list<pair<int, int>>[V];

	for(int u, v, w; fin >> u >> v >> w; adj[u].push_back({ v, w }));
	fin.close();
}

void Graph::dijkstra() {
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pcoada;
	vector<int> dist(V, INF);

	pcoada.push({ 0, this->S });
	dist[this->S] = 0;
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

	ofstream fout(this->outfile);
	for (int i = 0; i < V; ++i) {
		if (dist[i] == INF) {
			fout << "INF ";
		}
		else {
			fout << dist[i] << " ";
		}
	}
	fout << "\n";
	fout.close();
}

Graph::~Graph() {
	delete[] adj;
}


int main(int argc, char** argv) {
	if (argc != 3) {
		cout << "Numar invalid de argumente!\n";
		cout << " Utilizare: ./p1.exe fisier1 fisier2\n";
		exit(-1);
	}

	Graph G(argv[1], argv[2]);
	G.dijkstra();

	return 0;
}

