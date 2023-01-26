#include "IteratorMultime.h"
#include "NodMultime.h"
#include "Multime.h"
#include <exception>

IteratorMultime::IteratorMultime(const Multime& m)
				: mult(m) {
	/* de adaugat */
	curent = m.prim;
}

TElem IteratorMultime::element() const {
	if (this->valid() == false) {
		throw std::exception("");
	}
	return curent->element();
}

bool IteratorMultime::valid() const {
	return curent != nullptr;
}

void IteratorMultime::urmator() {
	curent = curent->urmator();
}

void IteratorMultime::prim() {
	/* de adaugat */
	curent = mult.prim;
}
