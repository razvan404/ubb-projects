#pragma once
#include "NodMultime.h"
#include "IteratorMultime.h"

typedef int TElem;

typedef bool(*Relatie)(TElem, TElem);

//in implementarea operatiilor se va folosi functia (relatia) rel (de ex, pentru <=)
// va fi declarata in .h si implementata in .cpp ca functie externa colectiei
bool rel(TElem, TElem);

class IteratorMultime;
class Nod;

typedef Nod* PNod;

class Multime {
	friend class IteratorMultime;
private:
	/* aici e reprezentarea */
	PNod prim;

public:
		//constructorul implicit
		Multime();

		//adauga un element in multime
		//returneaza adevarat daca elementul a fost adaugat (nu exista deja in multime)
		// Complexitate timp: 
		//		Caz favorabil: se adauga pe prima pozitie, T(n) = 1 ∈ Θ(1)
		//		Caz devaforabil: se adauga pe ultima pozitie: T(n) = n ∈ Θ(n)
		//		Caz mediu: T(n) = (1 + 2 + ... + n) / n = (n + 1) / 2 ∈ Θ(n)
		//		Complexitate generala: T(n) ∈ O(n)
		bool adauga(TElem e);

		//sterge un element din multime
		//returneaza adevarat daca elementul a existat si a fost sters
		// Complexitate timp: 
		//		Caz favorabil: se sterge de pe prima pozitie, T(n) = 1 ∈ Θ(1)
		//		Caz devaforabil: se sterge de pe ultima pozitie: T(n) = n ∈ Θ(n)
		//		Caz mediu: T(n) = (1 + 2 + ... + n) / n = (n + 1) / 2 ∈ Θ(n)
		//		Complexitate generala: T(n) ∈ O(n)
		bool sterge(TElem e);

		//verifica daca un element se afla in multime
		// Complexitate timp: 
		//		Caz favorabil: se afla pe prima pozitie, T(n) = 1 ∈ Θ(1)
		//		Caz devaforabil: se afla pe ultima pozitie: T(n) = n ∈ Θ(n)
		//		Caz mediu: T(n) = (1 + 2 + ... + n) / n = (n + 1) / 2 ∈ Θ(n)
		//		Complexitate generala: T(n) ∈ O(n)
		bool cauta(TElem elem) const;


		//intoarce numarul de elemente din multime;
		// Complexitate timp: T(n) ∈ O(n)
		int dim() const;

		//verifica daca multimea e vida;
		// Complexitate timp: T(n) = 1 ∈ Θ(1)
		bool vida() const;

		// face diferenta dintre multime si o alta multime
		// returneaza cate elemente au fost eliminate
		int diferenta(const Multime& b);

		//returneaza un iterator pe multime
		IteratorMultime iterator() const;

		// destructorul multimii
		~Multime();

};
