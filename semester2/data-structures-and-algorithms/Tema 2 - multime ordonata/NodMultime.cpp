#include "NodMultime.h"
#include "Multime.h"

Nod::Nod(TElem e, PNod next) {
	this->elem = e;
	this->next = next;
}

TElem Nod::element() {
	return this->elem;
}

PNod Nod::urmator() {
	return this->next;
}
