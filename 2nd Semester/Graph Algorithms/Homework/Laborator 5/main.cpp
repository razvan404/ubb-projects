#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

class Graph {
private:
	ifstream fin;
	ofstream fout;

public:
	void PruferEncoding();
	void PruferDecoding();
	void HuffmanEncoding();
	void HuffmanDecoding();
    void MinimumCoverTree();

	Graph(string in, string out) :
		fin{ in },
		fout{ out } {}

	~Graph() {
		fin.close();
		fout.close();
	}
};



int main(int argc, char* argv[]) {
	if (argc != 4) {
		cout << "Invalid syntax!\n";
		cout << "  Usage: .exe PROBLEM_NUMBER INPUT_FILE OUTPUT_FILE\n";
		return EXIT_FAILURE;
	}

	Graph G{ argv[2], argv[3] };
	switch(atoi(argv[1])) {
	case 1:
		G.PruferEncoding();
		break;
	case 2:
		G.PruferDecoding();
		break;
	case 3:
		G.HuffmanEncoding();
		break;
	case 4:
		G.HuffmanDecoding();
		break;
    case 5:
        G.MinimumCoverTree();
        break;
	default:
		cout << "Invalid problem number!";
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}



void Graph::PruferEncoding() {
	int n;
	fin >> n;

	int* deg = new int[n]{ }; // degrees vector
	for (int i = 0; i < n; ++i) {
		deg[i] = 0; // we initialize the degree with 0
	}
	int* pi = new int[n]{ }; // parents vector
	set<int> leafs; // leafs set

	for (int i = 0; i < n; ++i) {
		fin >> pi[i];
		deg[i]++;
		pi[i] != -1 ? deg[pi[i]]++ : 0;
	}
	
	for (int i = 0; i < n; ++i) {
		if (deg[i] == 1 && pi[i] != -1) { // only leafs that are not the root
			leafs.insert(i);
		}
	}
	
	int* code = new int[n - 1]{ }; // prufer code vector

	for (int i = 0; i < n - 1; ++i) {
		int minLeaf = *(leafs.begin()); // we extract the minimum leaf
		leafs.erase(leafs.begin()); // and delete it from the set
	
		int minLeafP = pi[minLeaf]; // the parent of the minimum leaf

		code[i] = minLeafP;
		deg[minLeaf]--;
		deg[minLeafP]--;

		if (pi[minLeafP] != -1 && deg[minLeafP] == 1) { // if the parent is now a leaf, we add it to the leafs vector
			leafs.insert(minLeafP);
		}
	}

	fout << n - 1 << "\n";
	for (int i = 0; i < n - 1; ++i) {
		fout << code[i] << " ";
	}
	delete[] deg;
	delete[] pi;
	delete[] code;
}

void Graph::PruferDecoding() {
	int n;
	fin >> n;
	int* deg = new int[n + 1]{ };
	int* pi = new int[n + 1]{ };

	set<int> leafs;
	for (int i = 0; i < n + 1; ++i) {
		leafs.insert(i);
	}

	list<int> code;
	for (int i = 0; i < n; ++i) {
		int x;
		fin >> x;
		code.push_back(x);
		++deg[x];
		leafs.erase(x);
	}

	for (int i = 0; i < n; ++i) {
		int minLeaf = *leafs.begin();
		leafs.erase(leafs.begin());
		int minLeafP = code.front();
		
		pi[minLeaf] = minLeafP;
		deg[minLeafP]--;
		if (deg[minLeafP] == 0) {
			leafs.insert(minLeafP);
		}
		code.pop_front();
	}

	pi[*leafs.begin()] = -1; // the root

	fout << n + 1 << "\n";
	for (int i = 0; i < n + 1; ++i) {
		fout << pi[i] << " ";
	}

	delete[] deg;
	delete[] pi;
}

void Graph::HuffmanEncoding() {
	struct FreqPair {
		int freq = 0;
		char chr = 0;
		bool operator<(const FreqPair& oth) const {
			return freq < oth.freq || (freq == oth.freq && chr < oth.chr);
		}
	};

	string text;
	getline(fin, text);

	if (text == "") {
		return;
	}

	int freq[256] {};
	int letters = 0;

	for (char chr : text) {
		freq[int(chr)]++;
		freq[int(chr)] == 1 ? letters++ : 0;
	}

	multimap<FreqPair, string> Q;
	
	fout << letters << "\n";
	for (int i = 0; i < 256; ++i)  {
		if (freq[i]) {
			fout << char(i) << " " << freq[i] << "\n";
			Q.insert({ { freq[i], char(i) }, string(1, i) });
		}
	}
	
	string code[256];
	while (--letters) {
		auto x = *Q.begin();
		for (char chr : x.second) {
			code[int(chr)] = "0" + code[int(chr)];
		}
		Q.erase(Q.begin());

		auto y = *Q.begin();
		for (char chr : y.second) {
			code[int(chr)] = "1" + code[int(chr)];
		}
		Q.erase(Q.begin());

		Q.insert({ { x.first.freq + y.first.freq, min(x.first.chr, y.first.chr) }, x.second + y.second });
	}

	for (char chr : text) {
		fout << code[int(chr)];
	}
}

void Graph::HuffmanDecoding() {
	struct FreqPair {
		int freq = 0;
		char chr = 0;
		bool operator<(const FreqPair& oth) const {
			return freq < oth.freq || (freq == oth.freq && chr < oth.chr);
		}
	};
	
	multimap <FreqPair, string> Q;

	int letters, freq[256] {};
	string line;
	
	getline(fin, line);
	letters = stoi(line);

	for (int i = 0; i < letters; ++i) {
		getline(fin, line);
		char chr = line[0];
		freq[int(chr)] = stoi(line.substr(2));
		Q.insert({ {freq[int(chr)], chr }, string(1, chr) });
	}
	
	string encoded;
	getline(fin, encoded);

	string text;
	map<string, char> codes;

	string code[256] {};
	while (--letters) {
		auto x = *Q.begin();
		for (auto chr : x.second) {
			code[int(chr)] = "0" + code[int(chr)];
		}
		Q.erase(Q.begin());

		auto y = *Q.begin();
		for (auto chr : y.second) {
			code[int(chr)] = "1" + code[int(chr)];
		}
		Q.erase(Q.begin());

		Q.insert({ { x.first.freq + y.first.freq, min(x.first.chr, y.first.chr) }, x.second + y.second });
	}

	for (int i = 0; i < 256; ++i) {
		if (code[i] != "\0") {
			codes.insert({ code[i], i });
		}
	}

	int last = 0, len = 0;
	string prev, chr;
	
	while (codes.size() > 1) {
		string until = encoded.substr(last, len);
		len++;
		auto srch = codes.find(until);
		if (srch != codes.end()) {
			prev = until;
			chr = srch->second;
		}
		else if (srch == codes.end() && prev != "\0") {
			text.append(chr);
			freq[int(chr[0])]--;

			if (freq[int(chr[0])] == 0) {
				codes.erase(prev);
			}

			last += prev.size();
			len = 0;
			prev = "\0";
			chr = "\0";
		}
	}

	if (codes.size() == 1) {
		text.append(string(1, codes.begin()->second));
	}

	fout << text;
}

void Graph::MinimumCoverTree() {
    const int INF = 1e7 + 5;
    int V, E, root = 0;
    fin >> V >> E; // vertices and edges
    vector<pair<int, int>>* adj = new vector<pair<int, int>>[V];
    for (int i = 0; i < E; ++i) {
        int x, y, w;
        fin >> x >> y >> w;
        adj[x].push_back({ y, w });
        adj[y].push_back({ x, w });
        // cout << x << " " << y << " " << w << "\n";
    }

    int edges = -1;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;

    vector<int> key(V);
    vector<int> pi(V);
    vector<bool> viz(V);

    for (int i = 0; i < V; ++i) {
        key[i] = INF;
        pi[i] = -1;
        viz[i] = false;
    }

    Q.push({ 0, root });
    key[root] = 0;

    while (!Q.empty()) {
        int current = Q.top().second;
        Q.pop();
        if (viz[current]) {
            continue;
        }
        viz[current] = true;
        edges++;

        for (auto x : adj[current]) {
            int y = x.first;
            int w = x.second;
            if (key[y] > w && !viz[y]) {
                key[y] = w;
                Q.push({ w, y });
                pi[y] = current;
            }
        }
    }

    int minWeight = 0;
    for (int i = 0; i < V; ++i) {
        minWeight += key[i];
    }

    fout << minWeight << "\n" << edges << "\n";

    map<int, vector<int>> ans;

    for (int i = 0; i < V; ++i) {
        if (viz[i] && i != root) {
            if (i < pi[i]) {
                ans[i].push_back(pi[i]);
            }
            else {
                ans[pi[i]].push_back(i);
            }
        }
    }
    for (int i = 0; i < V; ++i) {
        sort(ans[i].begin(), ans[i].end());
        for (auto j : ans[i]) {
            fout << i << " " << j << "\n";
        }
    }
}
