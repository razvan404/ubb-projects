#pragma once
#include "Joc.hpp"
#include <vector>
#include <fstream>

class Repo {
private:
	vector<Joc> myList;
	string file;
public:
	// Constructorul
	//	file : fisierul din care se citesc datele
	Repo(string file)
		: file{ file } {};

	// Citeste datele din fisierul text dat ca parametru
	//	return: se va modifica lista
	void read();

	// Returneaza pozitia unui anumit joc
	//	j : referinta la un Joc
	//	return: pozitia lui j in vector
	unsigned getJoc(Joc& j);

	// Returneaza lista cu jocuri
	//	return: lista de jocuri
	vector<Joc>& getList() {
		read();
		return myList;
	}
};
