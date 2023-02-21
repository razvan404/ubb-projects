#pragma once
#include "Melodie.h"
#include <vector>
#include <fstream>
#include <exception>

class Repo {
	vector<Melodie> myList;
	string file = "Data.txt";
public:
	// Constructorul default al clasei Repo
	Repo() = default;

	// Constructorul care isi ia datele din fisier al clasei Repo
	// file: numele fisierului
	// return: se vor pune in myList elementele din fisier
	Repo(string file) : file{ file } {
		ifstream fin(file);
		char line[500];
		while (fin.getline(line, 500)) {
			char* p = strtok(line, ";");
			int id = atoi(p);
			p = strtok(NULL, ";");
			string titlu = p;
			p = strtok(NULL, ";");
			string artist = p;
			p = strtok(NULL, ";");
			int rank = atoi(p);

			myList.push_back({id, titlu, artist, rank});
		}
		fin.close();
	};

	// Salveaza in fisier datele din constructor
	// return: se salveaza in fisier datele din repo
	void saveToFile() {
		ofstream fout(file);
		for (auto& m : myList) {
			fout << m.getID() << ";"
				<< m.getTitlu() << ";"
				<< m.getArtist() << ";"
				<< m.getRank() << "\n";
		}
		fout.close();
	}

	// Se returneaza lista
	// return: lista corespunzatoare repo-ului
	auto& getList() {
		return myList;
	}

	// Se sterge o melodie din repo
	// poz : pozitia melodiie care trebuie stearsa
	// return: se va sterge melodia de pe pozitia data din Repo
	// @Arunca exceptie in cazul in care pozitia este invalida
	void deleteMusic(int poz) {
		if (poz < 0 || poz >= myList.size()) {
			throw exception("Nu exista un element pe acea pozitie!");
		}
		myList.erase(myList.begin() + poz);
		saveToFile();
	}

	// Se modifica rank-ul unei melodii din repo
	// poz: pozitia elementului care trebuie modificat
	// newRank: noul rank al elementului care trebuie modificat
	// @Arunca exceptie in cazul in care pozitia este invalida
	void changeRank(int poz, int newRank) {
		if (poz < 0 || poz >= myList.size()) {
			throw exception("Nu exista un element pe acea pozitie!");
		}
		myList.at(poz).getRank() = newRank;
		saveToFile();
	}
};