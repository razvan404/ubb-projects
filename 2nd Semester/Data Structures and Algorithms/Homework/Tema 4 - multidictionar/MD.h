#pragma once
#include<vector>
#include<utility>

using namespace std;

#define MAXMD 100000 // maximul numarul elementelor
#define NIL INT_MIN

typedef int TCheie;
typedef int TValoare;

typedef pair<TCheie, TValoare> TElem;
typedef pair<TCheie, vector<TValoare>> TSectiune;

class IteratorMD;

class MD
{
	friend class IteratorMD;

private:
	/* aici e reprezentarea */
	int m; // numarul de locatii din tabela de dispersie
	TSectiune* e; // vectorul elementelor
	int* urm; // vectorul legaturilor
	int primLiber; // locatia primei pozitii libere din tabela

	int nrElem;

	// actualizare prim liber
	void actPrimLiber();


	// functia de dispersie
	int d(TCheie e) const;

public:
	// constructorul implicit al MultiDictionarului
	MD();

	// adauga o pereche (cheie, valoare) in MD	
	void adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
	vector<TValoare> cauta(TCheie c) const;

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	bool sterge(TCheie c, TValoare v);

	//returneaza numarul de perechi (cheie, valoare) din MD 
	int dim() const;

	//verifica daca MultiDictionarul e vid 
	bool vid() const;

	// se returneaza iterator pe MD
	IteratorMD iterator() const;

	// sterge toate elementele din MD
	void goleste();

	// destructorul MultiDictionarului	
	~MD();



};

