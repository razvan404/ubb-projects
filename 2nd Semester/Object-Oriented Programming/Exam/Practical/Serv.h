#pragma once
#include "Repo.h"
#include "Observer.h"
#include <algorithm>

class Serv : public Observable {
	Repo& r;

	// Prin aceasta functie privata sortam elementele repo-ului dupa rank-ul acestora
	void sortRank() {
		sort(r.getList().begin(), r.getList().end(), [&](Melodie& m1, Melodie& m2) {
			return m1.getRank() < m2.getRank();
			});
	}
public:
	// in ranks retinem o lista cu cate melodii sunt per fiecare rank
	int ranks[11] {};

	// Constructorul clasei Serv
	Serv(Repo& r) : r{ r } {
		sortRank();
		for (auto& m : r.getList()) {
			ranks[m.getRank()]++;
		}
		r.saveToFile();
	}

	// Se returneaza lista de elemente din serv
	// return: lista de elemente
	auto& getList() {
		return r.getList();
	}

	// Se schimba rank-ul unei melodii din serv
	// poz: pozitia melodiei care trebuie schimbate
	// newRank: noul rank al melodiei
	// return: se va modifica rank-ul melodiei de pe pozitia data
	// @Arunca exceptie in cazul in care melodia avea deja acel rank
	void changeRank(int poz, int newRank) {
		if (r.getList().at(poz).getRank() == newRank) {
			throw exception("Melodia are deja acest rank!");
		}
		ranks[r.getList().at(poz).getRank()]--;
		r.changeRank(poz, newRank);
		ranks[newRank]++;
		sortRank();
		notify();
	}

	// Se va sterge o melodie din serv de pe o pozitie
	// poz: pozitia melodiei care trebuie stearsa
	// return: se va scoate acea melodie din serv
	// @Arunca exceptie daca este ultima melodie a artistului
	void deleteMusic(int poz) {
		auto& that = r.getList().at(poz);
		int nrMelodii = 0;
		for (auto& m : r.getList()) {
			if (that.getArtist() == m.getArtist()) {
				nrMelodii++;
			}
		}
		if (nrMelodii == 1) {
			throw exception("Nu se poate sterge, este ultima melodie a artistului!");
		}

		r.deleteMusic(poz);
		notify();
	}
	
	// Se va actualiza titlul si rank-ul unei melodii
	// poz: pozitia melodiei care trebuie modificata
	// title: noul titlu al melodiei
	// rank: noul rank al melodiei
	// return: se va actualiza melodia in serv
	// @Arunca exceptie daca procedura de changeRank esueaza
	void updateTitleRank(int poz, string title, int rank) {
		string oldTitle = r.getList().at(poz).getTitlu();
		r.getList().at(poz).getTitlu() = title;
		try {
			changeRank(poz, rank);
		}
		catch (exception& e) {
			r.getList().at(poz).getTitlu() = oldTitle;
			throw e;
		}
		r.saveToFile();
	}

};