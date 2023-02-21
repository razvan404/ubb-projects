#pragma once
#include "Multime.h"

class Nod;

typedef int TElem;
typedef Nod* PNod;

class Nod {
private:
	TElem elem;
	PNod next;

public:
	friend class Multime;
	// constructor
	Nod(TElem e, PNod next);

	// Complexitate timp: T(n) ∈ Θ(1)
	TElem element();

	// Complexitate timp: T(n) ∈ Θ(1)
	PNod urmator();
};
