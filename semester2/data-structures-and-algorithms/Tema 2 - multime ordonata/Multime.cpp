#include "Multime.h"
#include "NodMultime.h"
#include "IteratorMultime.h"
#include <iostream>

using namespace std;

//o posibila relatie
bool rel(TElem e1, TElem e2) {
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}

Multime::Multime() {
	/* de adaugat */
	this->prim = nullptr;
}


bool Multime::adauga(TElem elem) {
	/* de adaugat */
	if (prim == nullptr) {
		PNod q = new Nod(elem, nullptr);
		this->prim = q;
		return true;
	}
	PNod p = prim;
	if (!rel(p->elem, elem)) {
		PNod q = new Nod(elem, nullptr);
		this->prim = q;
		this->prim->next = p;
		return true;
	}

	while (p->next != nullptr && rel(p->next->elem, elem) == true) {
		p = p->next;
	}

	if (p->elem == elem) {
		return false;
	}

	PNod q = new Nod(elem, nullptr);
	q->next = p->next;
	p->next = q;
	return true;
}


bool Multime::sterge(TElem elem) {
	/* de adaugat */
	if (prim == nullptr) {
		return false;
	}

	PNod p = prim;
	if (p->elem == elem) {
		prim = p->next;
		return true;
	}
	while (p->next != nullptr) {
		if (p->next->elem == elem) {
			p->next = p->next->next;
			return true;
		}
		p = p->next;
	}
	return false;
}


bool Multime::cauta(TElem elem) const {
	/* de adaugat */
	PNod p = prim;
	while (p != nullptr) {
		if (p->elem == elem) {
			return true;
		}
		p = p->next;
	}
	return false;
}


int Multime::dim() const {
	/* de adaugat */
	PNod p = prim;
	int dimensiune = 0;
	while (p != nullptr) {
		dimensiune++;
		p = p->next;
	}
	return dimensiune;
}



bool Multime::vida() const {
	/* de adaugat */
	return prim == nullptr;
}

int Multime::diferenta(const Multime& b) {
	int nr_elim = 0;
	PNod i = b.prim;
	while (i != nullptr) {
		PNod j = this->prim;
		while (j != nullptr) {
			if (i->elem == j->elem) {
				this->sterge(i->elem);
				nr_elim++;
			}
			j = j->next;
		}
		i = i->next;
	}
	return nr_elim;
}

IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}


Multime::~Multime() {
	/* de adaugat */
	while (prim != nullptr) {
		PNod p = prim;
		prim = prim->next;
		delete p;
	}
}
