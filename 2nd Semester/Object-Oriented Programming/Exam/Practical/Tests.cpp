#include "Tests.h"
#include "Melodie.h"
#include "Repo.h"
#include "Serv.h"
#include <cassert>

void copyTestFolder(string newFolder) {
	ofstream fout(newFolder);
	ifstream fin("Tests.txt");

	char line[500];
	while (fin.getline(line, 500)) {
		fout << line << '\n';
	}
	fin.close();
	fout.close();
}

void testMelodie() {
	Melodie m{ 1, "Krkr", "Brbr", 7 };
	assert(m.getID() == 1);
	assert(m.getTitlu() == "Krkr");
	assert(m.getArtist() == "Brbr");
	assert(m.getRank() == 7);
	m.getRank() = 9;
	assert(m.getRank() == 9);
}

void testRepo() {
	copyTestFolder("Aux.txt");
	Repo r{ "Aux.txt" };
	assert(r.getList().size() == 10);
	r.deleteMusic(9);
	assert(r.getList().size() == 9);
	try {
		r.deleteMusic(9);
		assert(false);
	}
	catch (...) {
		assert(true);
	}
	assert(r.getList().at(8).getRank() == 9);
	r.changeRank(8, 5);
	assert(r.getList().at(8).getRank() == 5);
	try {
		r.changeRank(9, 6);
		assert(false);
	}
	catch (...) {
		assert(true);
	}
	remove("Aux.txt");
}

void testServ() {
	copyTestFolder("Aux.txt");
	Repo r{ "Aux.txt" };
	Serv s{ r };

	assert(s.ranks[7] == 2);
	assert(s.ranks[5] == 1);

	try {
		s.changeRank(6, 7);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	s.changeRank(6, 5);
	assert(s.ranks[7] == 1);
	assert(s.ranks[5] == 2);

	assert(s.getList().size() == 10);
	s.deleteMusic(7);
	assert(s.getList().size() == 9);
	try {
		s.deleteMusic(7);
		assert(false);
	}
	catch (...) {
		assert(true);
	}
	assert(s.getList().size() == 9);
	
	s.updateTitleRank(0, "Miaunita", 10);
	assert(s.getList().at(7).getTitlu() == "Miaunita");

	remove("Aux.txt");
}

void testAll() {
	testMelodie();
	testRepo();
	testServ();
}