#pragma once
#include "service.h"
#include "vector.h"
#include "participant.h"


/*
* Cauta un participant in cadrul unui concurs
* input - concurs, participant
* return - pozitia acestuia daca se afla in concurs sau -1 in caz contrar
*/
int cauta_participant(vector_p, participant_p);

/*
* Returneaza pozitia participantului cu numele si prenumele dat
	din cadrul unui concurs
* input - concurs, 2 siruri de caractere (nume, prenume)
* return - pozitia participantului corespunzator sau -1 daca nu se afla in concurs
*/
int id_participant(vector_p, char*, char*);

/*
* Adauga un participant in concurs
* input - concurs, 2 siruri de caractere (nume, prenume), sir de 10 numere intregi (scor)
* return - se adauga participantul in concurs si se returneaza 0 daca s-a adaugat
		succes sau -1 in caz contrar
*/
int adauga_participant(vector_p*, char*, char*, int*);

/*
* Se modifica informatiile unui participant din concurs
* input - concurs, 2 siruri de caractere (nume, prenume), sir de numere intregi (scor probleme)
		numar intreg (1 daca se modifica probleme sau 0 in caz contrar)
* return - se actualizeaza informatiile participantului din concurs si se returneaza
		0 daca modificarea a avut loc cu succes sau -1 in caz contrar
*/
int modifica_participant(vector_p, int, char*, char*, int*, int);

/*
* Se sterge un participant de pe o pozitie din concurs
* input - concurs, numar intreg (pozitia)
* return - se sterge participantul din concurs si se returneaza 0 daca s-a sters
		cu succes sau -1 in caz contrar
*/
int sterge_participant(vector_p, int);

/*
* Filtreaza concursul, dand participantii cu un scor mai mic decat unul dat
* input - concurs, numar intreg (scor)
* return - se returneaza un concurs cu participantii cu scorul mai mic decat
		decat cel dat sau un concurs gol in caz ca nu exista
*/
vector_p filtreaza_scor_mai_mic(vector_p, int);

/*
* Filtreaza concursul, dand participantii cu o prima litera din nume data
* input - concurs, caracter (litera)
* return - se returneaza un concurs cu participantii cu prima litera a numelui
		care coincide cu litera data sau un concurs gol in caz ca nu exista
*/
vector_p filtreaza_prima_litera(vector_p, char);

/*
* Se sorteaza concursul dupa un anumit criteriu
* input - concurs, functie de comparare
* return - se sorteaza concursul dupa criteriul introdus
*/
void sorteaza_participanti(vector_p, int(*compare)(participant_p, participant_p));

/*
* Distruge un concurs
* input - vector cu participanti
* return - se distruge acel vector si participantii continuti
*/
void distruge_concurs(vector_p);
