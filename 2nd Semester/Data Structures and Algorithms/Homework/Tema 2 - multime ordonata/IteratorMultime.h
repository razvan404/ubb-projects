#pragma once
#include "Multime.h"
#include "NodMultime.h"

typedef int TElem;

class Nod;
typedef Nod* PNod;

class IteratorMultime
{
	friend class Multime;
	friend class Nod;

private:

	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	IteratorMultime(const Multime& m);

	//contine o referinta catre containerul pe care il itereaza
	const Multime& mult;

	/* aici e reprezentarea  specifica a iteratorului */
	PNod curent;

public:

		//reseteaza pozitia iteratorului la inceputul containerului
		// Complexitate timp: T(n) = 1 ∈ Θ(1)
		void prim();

		//muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
		// Complexitate timp: T(n) = 1 ∈ Θ(1)
		void urmator();

		//verifica daca iteratorul e valid (indica un element al containerului)
		// Complexitate timp: T(n) = 1 ∈ Θ(1)
		bool valid() const;

		//returneaza valoarea elementului din container referit de iterator
		//arunca exceptie daca iteratorul nu e valid
		// Complexitate timp: T(n) = 1 ∈ Θ(1)		
		TElem element() const;
};

