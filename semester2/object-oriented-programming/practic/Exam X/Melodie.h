#pragma once
using namespace std;
#include <string>

class Melodie {
	int id;
	string titlu;
	string artist;
	int rank;
public:
	// Constructorul default al clasei Melodie
	Melodie(int id, string titlu, string artist, int rank) :
		id{ id }, titlu{ titlu }, artist{ artist }, rank{ rank } {};

	// Returneaza o referinta la ID-ul melodiei
	// return: referinta la id
	auto& getID() {
		return id;
	}

	// Returneaza o referinta la titlul melodiei
	// return: referinta la titlu
	auto& getTitlu() {
		return titlu;
	}

	// Returneaza o referinta la artistul melodiei
	// return: referinta la artist
	auto& getArtist() {
		return artist;
	}

	// Returneaza o referinta la rank-ul melodiei
	// return: referinta la rank
	auto& getRank() {
		return rank;
	}
};