#pragma once
#include <exception>

template <typename Type>
class IteratorVectorDinamic;

template <typename Type>
class VectorDinamic {
private:
	int n;		// dimensiunea vectorului dinamic
	int cp;		// capacitatea vectorului dinmaic
	Type* e;	// elementele vectorului dinamic
	void redim();	// redimensionare

public:
		// constructor
		//arunca exceptie in cazul in care capacitate e <=0
		VectorDinamic(int capacitate);

		// returnare dimensiune
		int dim() const;

		// returnare element
		//arunca exceptie daca i nu e valid
		//indicii ii consideram de la 0
		Type element(int i) const;

		// modifica element de pe pozitia i si returneaza vechea valoare
		//arunca exceptie daca i nu e valid
		Type modifica(int i, Type e);

		// adaugare element la sfarsit
		void adaugaSfarsit(Type e);

		// adaugare element pe o pozitie i
		//arunca exceptie daca i nu e valid
		void adauga(int i, Type e);

		// sterge element de pe o pozitie i si returneaza elementul sters
		//arunca exceptie daca i nu e valid
		Type sterge(int i);

		// returnare iterator
		IteratorVectorDinamic<Type> iterator();

		//destructor
		~VectorDinamic();
};

template <typename Type>
void VectorDinamic<Type>::redim() {
	Type* eNou = new Type[cp * 2];
	for (int i = 0; i < n; ++i) {
		eNou[i] = e[i];
	}
	cp += cp;
	delete[] e;
	e = eNou;
}

template <typename Type>
VectorDinamic<Type>::VectorDinamic(int cp) {
	if (cp < 1) {
		throw std::exception("Capacitatea vectorului trebuie sa fie un numar pozitiv!");
	}
	this->cp = cp;		// setam capacitatea la cea data
	this->n = 0;		// setam dimensiunea la 0
	e = new Type[cp];	// alocam spatiu pentru elemente
}

template <typename Type>
VectorDinamic<Type>::~VectorDinamic() {
	delete[] e;		// eliberam zona
}

template <typename Type>
int VectorDinamic<Type>::dim() const{
	return n;
}

template <typename Type>
Type VectorDinamic<Type>::element(int i) const{
	return e[i];
}

template <typename Type>
void VectorDinamic<Type>::adaugaSfarsit(Type e) {
	if (n == cp) {
		redim();
	}
	this->e[n] = e;
	++n;
}

template <typename Type>
void VectorDinamic<Type>::adauga(int i, Type e) {
	if (i < 0 || i > n) {
		throw std::exception("Nu s-a putut adauga elementul, pozitia este invalida!");
	}
	if (n == cp) {
		redim();
	}
	for (int j = n; j > i; --j) {
		this->e[j] = this->e[j - 1];
	}
	this->e[i] = e;
	++n;
}

template <typename Type>
Type VectorDinamic<Type>::modifica(int i, Type e) {
	if (i < 0 || i >= n) {
		throw std::exception("Nu s-a putut realiza modificarea, pozitia este invalida!");
	}
	Type old = this->e[i];
	this->e[i] = e;
	return old;
}

template <typename Type>
Type VectorDinamic<Type>::sterge(int i) {
	if (i < 0 || i >= n) {
		throw std::exception("Nu s-a putut sterge elementul, pozitia este invalida!");
	}
	Type old = e[i];
	for (int j = i; j < n; ++j) {
		e[j] = e[j + 1];
	}
	n--;
	return old;
}


template <typename Type>
IteratorVectorDinamic<Type> VectorDinamic<Type>::iterator() {
	return IteratorVectorDinamic<Type>(*this);
}

template <typename Type>
class IteratorVectorDinamic {

private:
	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	IteratorVectorDinamic(const VectorDinamic<Type>&);

	//contine o referinta catre containerul pe care il itereaza
	const VectorDinamic<Type>& v;

	int curent;	// reprezentarea iteratorului
	
public:
	//reseteaza pozitia iteratorului la inceputul containerului
	void prim();

	//muta iteratorul in container
	// arunca exceptie daca iteratorul nu e valid
	void urmator();

	//verifica daca iteratorul e valid (indica un element al containerului)
	bool valid() const;

	//returneaza valoarea elementului din container referit de iterator
	//arunca exceptie daca iteratorul nu e valid
	Type element() const;
};

template <typename Type>
IteratorVectorDinamic<Type>::IteratorVectorDinamic(const VectorDinamic<Type>& _v) : v(_v) {
	curent = 0;
}

template <typename Type>
void IteratorVectorDinamic<Type>::prim() {
	curent = 0;
}

template <typename Type>
bool IteratorVectorDinamic<Type>::valid() const {
	return curent < v.dim();
}

template <typename Type>
Type IteratorVectorDinamic<Type>::element() const {
	return v.element(curent);
}

template <typename Type>
void IteratorVectorDinamic<Type>::urmator() {
	++curent;
}
