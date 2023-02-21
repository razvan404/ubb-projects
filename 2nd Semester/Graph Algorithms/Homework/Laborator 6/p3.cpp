#include <bits/stdc++.h>

using namespace std;

#define LEN_MAX 10001

int V, E, PI[LEN_MAX];
unordered_set<int> ADJ[LEN_MAX];

void Hierholzer(int s, vector<int>& circuit) {
	stack<int> S;
	S.push(s);

	while (!S.empty()) {
		int u = S.top();
		if (ADJ[u].size() != 0) {
			int v = *ADJ[u].begin();
			ADJ[u].erase(v);
			ADJ[v].erase(u);
			S.push(v);
			continue;
		}
		S.pop();
		circuit.push_back(u);
	}
	circuit.pop_back();
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cout << "Invalid input!\n"
			<< " Usage: ./p3.exe INPUT_FILE OUTPUT_FILE";
		return EXIT_FAILURE;
	}

	ifstream fin(argv[1]);
	ofstream fout(argv[2]);
	
	fin >> V >> E;
	for (int i = 0; i < E; ++i) {
		int x, y;
		fin >> x >> y;
		ADJ[x].insert(y);
		ADJ[y].insert(x);
	}
	
	vector<int> euler;
	Hierholzer(0, euler);
	
	for (auto i : euler) {
		fout << i << " ";
	}

	fin.close();
	fout.close();
	return EXIT_SUCCESS;
}
