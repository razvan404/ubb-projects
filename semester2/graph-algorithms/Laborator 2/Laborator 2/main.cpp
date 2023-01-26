#pragma warning(disable: 6001)
#include <iostream>
#include <crtdbg.h>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#define elif else if 
using namespace std;

ifstream fin("data/matrice.txt");
ifstream in("data/labirint.txt");
ofstream out("data/labirint_sol.txt");
const int INF = (int)(1e7 + 5);
const int LMAX = (int)(1e3 + 1);


void moore();
void tranzitiv();
void labirint();
void bfs_visit();
void dfs_visit();

int main(int argc, char** argv) {
	cout << " 1. Algoritmul lui Moore pentru un graf orientat neponderat\n";
	cout << " 2. Inchiderea tranzitiva a unui graf orientat\n";
	cout << " 3. Solutie pentru labirint\n";
	cout << " 4. Varfurile descoperite de algoritmul BFS si distanta fata de varful sursa\n";
	cout << " 5. Padurea descoperita de DFS\n";
	cout << "Alege cerinta: ";
	int option;
	cin >> option;
	cout << "\n";
	if (option == 1) {
		moore();
	}
	elif(option == 2) {
		tranzitiv();
	}
	elif(option == 3) {
		labirint();
	}
	elif(option == 4) {
		bfs_visit();
	}
	elif(option == 5) {
		dfs_visit();
	}
	else {
		cout << "Optiune invalida\n";
	}
	_CrtDumpMemoryLeaks();
	return 0;
}

void moore() {
	int n;
	fin >> n;
	vector<int> vecini[LMAX];
	for (int x, y; fin >> x >> y; vecini[x].push_back(y));
	queue<int> coada;
	int* dist = new int[n + 1];
	int* tata = new int[n + 1];
	bool* viz = new bool[n + 1];

	int nod_sursa;
	cout << " Introduceti nodul sursa: ";
	cin >> nod_sursa;

	for (int i = 1; i <= n; dist[i] = INF, viz[i] = false, i++);
	dist[nod_sursa] = 0;

	coada.push(nod_sursa);
	while (!coada.empty()) {
		int curent = coada.front();
		coada.pop();
		viz[curent] = true;
		for (auto i : vecini[curent]) {
			if (dist[i] > dist[curent] + 1) {
				tata[i] = curent;
				dist[i] = dist[curent] + 1;
				if (!viz[i]) {
					coada.push(i);
				}
			}
		}
	}

	int nod_destinatie;
	cout << " Introduceti nodul destinatie: ";
	cin >> nod_destinatie;

	if (dist[nod_destinatie] == INF) {
		cout << "Nodurile nu sunt unite de un drum!\n";
	}
	else {
		int* drum = new int[dist[nod_destinatie] + 1];
		int poz = dist[nod_destinatie];
		drum[poz] = nod_destinatie;
		while (poz) {
			drum[poz - 1] = tata[drum[poz]];
			--poz;
		}
		cout << "Drumul dintre nodurile " << nod_sursa << " si " << nod_destinatie << ": ";
		for (int i = 0; i <= dist[nod_destinatie]; cout << drum[i++] << " ");
		cout << "\n";
		delete[] drum;
	}

	delete[] dist;
	delete[] tata;
	delete[] viz;
}

void tranzitiv() {
	int n;
	fin >> n;
	bool** inchidere = new bool*[n + 1];
	for (int i = 1; i <= n; memset(inchidere[i++], false, n + 1)) {
		inchidere[i] = new bool[LMAX];
	}
	for (int x, y; fin >> x >> y; inchidere[x][y] = true);
	
	for (int k = 1; k <= n; ++k) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; j++, inchidere[i][j] |= inchidere[i][k] && inchidere[k][j]);
		}
	}
	cout << "Inchiderea tranzitiva:\n";
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; cout << inchidere[i][j++] << " ");
		delete[] inchidere[i];
		cout << "\n";
	}
	delete[] inchidere;
}

void labirint() {
	struct node {
		int x, y, dist;
	};

	int row[] = { -1, 0, 0, 1 };
	int col[] = { 0, -1, 1, 0 };
	char* s = new char[LMAX];
	vector<vector<int>> mat;
	vector<vector<int>> viz;
	vector<vector<pair<int, int>>> tata;
	pair<int, int> src, dest;
	src = dest = { -1, -1 };

	int n = 0, smax = 0;
	while (in.getline(s, LMAX)) {
		n++;
		if ((int)strlen(s) > smax) {
			smax = strlen(s);
		}
		mat.resize(n, vector<int>(smax));
		viz.resize(n, vector<int>(smax));
		tata.resize(n, vector<pair<int, int>>(smax));
		for (size_t i = 0; i < strlen(s); ++i) {
			if (s[i] == '1') {
				viz[n - 1][i] = true;
				mat[n - 1][i] = 1;
			}
			elif(s[i] == ' ') {
				viz[n - 1][i] = false;
				mat[n - 1][i] = 0;
			}
			elif(s[i] == 'S') {
				src = { n - 1, i };
			}
			elif(s[i] == 'F') {
				dest = { n - 1, i };
			}
		}
	}
	if (src.first == -1 || dest.first == -1) {
		printf("Datele au fost introduse gresit!\n");
		return;
	}
	queue<node> coada;
	viz[src.first][src.second] = true;
	tata[src.first][src.second] = { -1, -1 };
	coada.push({ src.first, src.second, 0 });

	int min_dist = INF;

	while (!coada.empty()) {
		node node = coada.front();
		coada.pop();
		int i = node.x, j = node.y, dist = node.dist;

		if (i == dest.first && j == dest.second) {
			min_dist = dist;
			break;
		}

		for (int k = 0; k < 4; ++k) {
			int r = i + row[k];
			int c = j + col[k];
			if ((r >= 0 && r < (int)mat.size()) && (c >= 0 && c < (int)mat[r].size()) && !viz[r][c]) {
				viz[r][c] = true;
				tata[r][c] = { i, j };
				coada.push({ r, c, dist + 1 });
			}
		}
	}

	if (min_dist == INF) {
		cout << "Nu exista un drum intre cele 2 puncte!\n";
	}
	else {
		pair<int, int> aux = dest;
		while (aux.first != -1 && aux.second != -1) {
			mat[aux.first][aux.second] = 2;
			aux = tata[aux.first][aux.second];
		}
		for (int i = 0; i < (int)mat.size(); ++i) {
			for (int j = 0; j < (int)mat[i].size(); ++j) {
				if (mat[i][j] == 1) {
					out << '1';
				}
				elif(mat[i][j] == 0) {
					out << ' ';
				}
				elif(i == src.first && j == src.second) {
					out << 'S';
				}
				elif(i == dest.first && j == dest.second) {
					out << 'F';
				}
				else {
					out << '8';
				}
			}
			out << '\n';
		}
		cout << "Done\n";
	}
	delete[] s;
}

void bfs_visit() {
	int n, nod_sursa;
	fin >> n;
	vector<int> vecini[LMAX];
	for (int x, y; fin >> x >> y; vecini[x].push_back(y));
	cout << " Introduceti nodul sursa: ";
	cin >> nod_sursa;

	vector<bool> viz(n + 1, false);
	vector<int> dist(n + 1, 0);
	queue<int> coada;
	viz[nod_sursa] = true;
	coada.push(nod_sursa);

	cout << "Nodurile acoperite de BFS: ";
	while (!coada.empty()) {
		int curent = coada.front();
		cout << curent << " - " << dist[curent] << "; ";
		coada.pop();
		for (auto i : vecini[curent]) {
			if (!viz[i]) {
				dist[i] = dist[curent] + 1;
				viz[i] = true;
				coada.push(i);
			}
		}
	}
}

void dfs_visit() {
	int n, nod_sursa;
	fin >> n;
	vector<int> vecini[LMAX];
	for (int x, y; fin >> x >> y; vecini[x].push_back(y));
	cout << " Introduceti nodul sursa: ";
	cin >> nod_sursa;

	vector<bool> viz(n + 1, false);
	stack<int> stiva;
	stiva.push(nod_sursa);
	bool passed = false;

	cout << "Nodurile acoperite de DFS: ";
	while (!stiva.empty()) {
		int curent = stiva.top();
		stiva.pop();
		if (!viz[curent]) {
			passed = true;
			cout << curent << " ";
			viz[curent] = true;
		}
		for (auto i : vecini[curent]) {
			if (!viz[i]) {
				stiva.push(i);
			}
		}
	}
	cout << "\n";
}
