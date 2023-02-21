#include "Repository.h"

void Repo::read() {
	ifstream fin(file);
	myList.clear();
	while (!fin.eof()) {
		unsigned pret, age;
		string titlu, platforma;
		fin >> titlu >> pret
			>> platforma >> age;
		if (titlu == "") {
			break;
		}
		myList.push_back(Joc{ titlu, pret, platforma, age });
	}
}

unsigned Repo::getJoc(Joc& j) {
	read();
	for (unsigned i = 0; i < myList.size(); ++i) {
		if (myList.at(i) == j) {
			return i;
		}
	}
	return -1;
}