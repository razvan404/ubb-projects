#pragma once
#include "Repository.h"
#include <algorithm>
#include <exception>

class Serv {
	Repo& repo;
public:
	// constructorul
	//	repo: Repository
	Serv(Repo& repo)
		: repo{ repo } {};

	// returneaza lista cu jocuri asociata service-ului
	//	return: lista de jocuri
	auto& getList() {
		return repo.getList();
	}

	// returneaza pozitia unui anumit joc
	//	titlu: string, titlul jocului
	//	pret: unsigned, pretul jocului
	//	return: unsigned, pozitia jocului corespunzator
	unsigned getPos(string titlu, unsigned pret) {
		Joc aux{ titlu, pret, "", 0 };
		return repo.getJoc(aux);
	}

	// returneaza elementul de pe o anumita pozitie
	//	pos: unsigned, pozitia jocului cautat
	//	return: jocul respectiv sau exceptie daca nu exista
	Joc& at(unsigned pos);

	// returneaza o lista sortata crescator dupa pret
	//	return: lista de jocuri filtrata
	vector<Joc> sorteazaCresc();

	// returneaza o lista cu jocurile cu PEGI age rating mai mic decat 12 ani
	//	return: lista de jocuri filtrata
	vector<Joc> ptCopii();
};