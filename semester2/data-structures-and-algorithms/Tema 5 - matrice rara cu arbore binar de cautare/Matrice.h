#pragma once

typedef int TElem;

struct Triplet {
	int lin;
	int col;
	TElem elem;

	bool operator==(const Triplet& t) {
		return t.lin == lin && t.col == col;
	}

	bool operator!=(const Triplet& t) {
		return !(*this == t);
	}
};

#define NULL_TELEMENT 0
static const Triplet NULL_TRIPLET = { -1, -1, NULL_TELEMENT };

class Matrice {

private:
	void afiseazaArb(int p, int niv);

	Triplet* el;
	int* st;
	int* dr;

	int nrLin, nrCol;
	int nrElem, cap;

	int root;

	int primLiber;

	bool rel(const Triplet& t1, const Triplet& t2) const;

	void actPrimLiber();

	int creeazaNod(Triplet e);

	int adaugaRec(int p, Triplet e);

	int minim(int p);

	int stergeRec(int p, Triplet e);

public:

	//constructor
	//se arunca exceptie daca nrLinii<=0 sau nrColoane<=0
	Matrice(int nrLinii, int nrColoane);


	//destructor
	~Matrice(){};

	//returnare element de pe o linie si o coloana
	//se arunca exceptie daca (i,j) nu e pozitie valida in Matrice
	//indicii se considera incepand de la 0
	TElem element(int i, int j) const;


	// returnare numar linii
	int nrLinii() const;

	// returnare numar coloane
	int nrColoane() const;


	// modificare element de pe o linie si o coloana si returnarea vechii valori
	// se arunca exceptie daca (i,j) nu e o pozitie valida in Matrice
	TElem modifica(int i, int j, TElem);

	TElem suma(int j);
};
