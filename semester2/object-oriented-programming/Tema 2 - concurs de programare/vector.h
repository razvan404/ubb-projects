#pragma once
#include "participant.h"

typedef participant_p TElem;
typedef struct {
	TElem* elems;
	int len;
	int capacity;
} vector_t;
typedef vector_t* vector_p;

/*
* Initializeaza un vector
* input - numar intreg (capacitatea maxima)
* return - un vector cu capacitatea maxima data
*/
vector_p initializeaza_vector(int);

/*
* Se dubleaza capacitatea unui vector
* input - vector
* return - capacitatea vectorului se va dubla
*/
void redimensioneaza_vector(vector_p*);

/*
* Returneaza dimensiunea unui vector
* input - vector
* return - numarul de elemente
*/
int get_lungime(vector_p);

/*
* Returneaza elementul de pe o anumita pozitie
* input - vector, numar intreg (pozitia elementului cautat)
* return - participantul corespunzator
*/
TElem get_element(vector_p, int);

/*
* Returneaza capacitatea unui vector
* input - vector
* return - capacitatea sa
*/
int get_capacitate(vector_p);

/*
* Seteaza numarul de elemente ale unui vector
* input - vector, numar intreg (noul numar de elemente)
* return - numarul de elemente este setat la numarul intreg introdus
*/
void seteaza_lungime(vector_p, int);

/*
* Seteaza un participant pe o anumita pozitie
* input - concurs, numar intreg (pozitie), participant
* return - pe pozitia noua se va afla participantul introdus
*/
void seteaza_element(vector_p, int, TElem);

/*
* Verifica daca o pozitie este corecta
* input - concurs, numar intreg (pozitie)
* return - 1 daca pozitia este valida sau 0 in caz contrar
*/
int valideaza_pozitie(vector_p, int);

/*
* Adauga un participant in concurs
* input - concurs, participant
* return - in cadrul concursului se va adauga noul participant
*/
void adauga_element(vector_p*, TElem);

/*
* Modifica un participant de pe o anumita pozitie
* input - concurs, numar intreg (pozitia), participant
* return - se modifica participantul de pe pozitia data cu noul participant
*/
void modifica_element(vector_p, int, TElem);

/*
* Scoate un participant din concurs
* input - concurs, numar intreg (pozitia)
* return - se va scoate participantul de pe pozitia data din cadrul concursului si se va returna
*/
TElem scoate_element(vector_p, int);

/*
* Interschimba doi participanti
* input - concurs, 2 numere intregi (pozitiile)
* return - se vor interschimba participantii de pe acele pozitii
*/
void interschimba_elemente(vector_p, int, int);

/*
* Se elibereaza din memorie un concurs
* input - concurs
* return - se elibereaza din memorie concursul introdus
*/
void distruge_vector(vector_p);