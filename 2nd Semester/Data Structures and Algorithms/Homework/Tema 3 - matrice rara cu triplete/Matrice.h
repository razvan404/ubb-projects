#pragma once

typedef int TElem;

typedef struct {
	int row;
	int col;
	TElem val;
} TMatriceElem;

#define NULL_TELEMENT 0

class Matrice {

private:
	// capacitatea de memorare a vectorilor
	unsigned cp;

	// numarul de linii, de coloane si de valori
	int rows, cols, vals;

	// vectorul static de elemente de tip TMatriceElem
	TMatriceElem *elem;
	// vectorii statici pentru legaturi
	int *urm, *prec;
	// referinta catre primul si ultimul element al listei
	int prim, ultim;
	// referinta catre primul element din lista spatiului liber
	int primLiber;

	//functii pentru alocarea/dealocarea unui spatiu liber
	//se returneaza pozitia unui spatiu liber in lista
	int aloca();
	//dealoca spatiul de indice i
	void dealoca(int i);
	//functie privata care creeaza un nod in lista inlantuita
	int creeazaNod(TMatriceElem e);
	// functie care redimensioneaza cele 3 tablouri dinamice
	void redim();

public:
	//constructor
	//se arunca exceptie daca nrLinii<=0 sau nrColoane<=0
	Matrice(int nrLinii, int nrColoane);


	//destructor
	~Matrice();

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

	// face suma elementelor de pe diagonala princiapala a matricii
	TElem sumaDiagonalaPrincipala();

};
