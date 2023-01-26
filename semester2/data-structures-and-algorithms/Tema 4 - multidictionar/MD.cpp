#include "MD.h"
#include "IteratorMD.h"
#include <exception>
#include <iostream>
#include <math.h>

using namespace std;

int hashFunction(TCheie e) {
	return abs(e);
}

int MD::d(TCheie e) const {
	/// Complexitate timp: Θ(1)
	return hashFunction(e) % m;
}

void MD::actPrimLiber() {
	/// Caz favorabil: Θ(1)
	/// Caz defavorabil: Θ(m)
	/// Complexitate generala: O(m)
	primLiber++;
	while (primLiber < m && e[primLiber].first != NIL) {
		primLiber++;
	}
}

MD::MD() {
	/// Complexitate generala: O(m)
	m = MAXMD;
	urm = new int[MAXMD];
	e = new TSectiune[MAXMD];

	for (int i = 0; i < m; ++i) {
		e[i].first = NIL;
		urm[i] = NIL;
	}

	primLiber = 0;
	nrElem = 0;
}


void MD::adauga(TCheie c, TValoare v) {
	/// Caz favorabil: Θ(1)
	/// Caz defavorabil: Θ(m)
	/// Complexitate generala: O(m)
	nrElem++;
	int i = d(c); // locatia de dispersie a cheii

	if (e[i].first == NIL) { // cazul in care pozitia este libera
		e[i].first = c;
		e[i].second.push_back(v); // adaugam elementul
		if (i == primLiber) {
			actPrimLiber(); // actualizam primLiber daca este nevoie
		}
		return;
	}

	int j = NIL; // j reprezinta ultimul element pe care se afla ceva pentru a face reiterarea
	while (e[i].first != c && i != NIL) {
		j = i;
		i = urm[i];
	}

	if (e[i].first == c) {
		e[i].second.push_back(v);
		if (i == primLiber) {
			actPrimLiber(); // actualizam primLiber daca este nevoie
		}
		return;
	}

	if (primLiber >= m) {
		nrElem--;
		throw exception{ "Nu mai exista spatiu pentru adaugarea elementului!" };
	}

	// adaugam noua cheie
	e[primLiber].first = c;
	e[primLiber].second.push_back(v);
	urm[j] = primLiber;
	actPrimLiber();
}


bool MD::sterge(TCheie c, TValoare v) {
	/// Caz favorabil: Θ(1)
	/// Caz defavorabil: Θ(m)
	/// Complexitate generala: O(m)

	int i = d(c);
	int j = NIL;
	int k = 0;
	
	// verificam daca i are un element anterior
	while (k < m && j == NIL) {
		if (urm[k] == i) {
			j = k;
		}
		else {
			k++;
		}
	}

	// localizam cheia c in lista intrepatrunsa
	while (e[i].first != c && i != NIL) {
		j = i;
		i = urm[i];
	}

	// daca nu gasim cheia in lista intrepatrunsa, vom returna fals
	if (i == NIL) {
		return false;
	}

	bool sters = false;

	// localizam valoarea v in vectorul asociat cheii, daca il gasim il stergem
	for (auto val = e[i].second.begin(); val != e[i].second.end(); ++val) {
		if (*val == v) {
			e[i].second.erase(val);
			sters = true;
			break;
		}
	}
	
	// in cazul in care nu s-a gasit perechea cheie-valoare, se va returna fals
	if (!sters) {
		return false;
	}

	nrElem--;

	// daca vectorul asociat cheii a ramas fara elemente, vom sterge vectorul din lista
	if (e[i].second.size() == 0) {
		bool gata = false;
		while (!gata) {
			int p = urm[i];
			int pp = i;
			while (p != NIL && d(e[p].first) != i) {
				pp = p;
				p = urm[p];
			}
			if (p == NIL) {
				gata = true;
			}
			else {
				e[i] = e[p];
				j = pp;
				i = p;
			}
		}

		if (j != NIL) {
			urm[j] = urm[i];
		}
		e[i].first = NIL;
		e[i].second.clear();
		urm[i] = NIL;

		if (primLiber > i) {
			primLiber = i;
		}
	}
	return true;
}


vector<TValoare> MD::cauta(TCheie c) const {
	/// Caz favorabil: Θ(1), cheia se gaseste la valoarea ei de dispersare
	/// Caz defavorabil: Θ(m), pentru o dispersie foarte ineficienta
	/// Complexitate generala: O(m)
	int i = d(c);
	while (e[i].first != c && i != NIL) {
		i = urm[i];
	}

	if (i == NIL) {
		return vector<TValoare>();
	}
	return e[i].second;
}


int MD::dim() const {
	/// Complexitate timp: Θ(1)
	return nrElem;
}


bool MD::vid() const {
	/// Complexitate timp: Θ(1)
	return nrElem == 0;
}

IteratorMD MD::iterator() const {
	/// Complexitate timp: Θ(1)
	return IteratorMD(*this);
}

void MD::goleste() {
	/// Complexitate timp: Θ(m + n) unde n este numarul de TElemente
	for (int i = 0; i < m; ++i) {
		if (e[i].first != NIL) {
			e[i].first = NIL;
			e[i].second.clear();
		}
	}
	nrElem = 0;
	primLiber = 0;
}


MD::~MD() {
	/// Complexitate timp: Θ(1)
	delete[] urm;
	delete[] e;
}

