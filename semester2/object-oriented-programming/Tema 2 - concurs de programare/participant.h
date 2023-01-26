#pragma once

typedef struct {
	char* nume;
	char* prenume;
	int* probleme;
	int scor;
} participant_t;
typedef participant_t* participant_p;

/*
* Se initializeaza un participant
* input - 2 siruri de caractere (nume prenume) si o lista de 10 numere (scorurile la probleme)
* return - participantul cu numele, prenumele si scorul dat 
*/
participant_p initializeaza_participant(char*, char*, int*);

/*
* Se valideaza un participant
* input - participant
* return - 0 daca este valid sau -1 in caz contrar
*/
int valideaza_participant(participant_p);

/*
* Returneaza numele participantului
* input - participant
* return - numele acestuia sub forma de sir de caractere
*/
char* get_nume(participant_p);

/*
* Returneaza prenumele participantului
* input - participant
* return - prenumele acestuia sub forma de sir de caractere
*/
char* get_prenume(participant_p);

/*
* Returneaza scorul la problemele participantului
* input - participant
* return - vectorul cu punctajele celor 10 probleme
*/
int* get_probleme(participant_p);

/*
* Returneaza scorul participantului
* input - participant
* return - scorul acestuia
*/
int get_scor(participant_p);

/*
* Seteaza numele unui participant
* input - participant, sir de caractere
* return - numele participantului va deveni sirul de caractere introdus
*/
void seteaza_nume(participant_p, char*);

/*
* Seteaza prenumele unui participant
* input - participant, sir de caractere
* return - prenumele participantului va deveni sirul de caractere introdus
*/
void seteaza_prenume(participant_p, char*);

/*
* Seteaza scorul unui participant
* input - participant, numar intreg (scor)
* return - scorul se va actualiza
*/
void seteaza_scor(participant_p, int);

/*
* Seteaza punctajul la probleme si scorul unui participant
* input - participant, lista de 10 intregi
* return - probleme si scorul se vor actualiza conform input-ului 
*/
void seteaza_probleme(participant_p, int*);

/*
* Seteaza participantului noi informatii
* input - participant, 2 siruri de caractere, intreg
* return - informatiile participantului se vor modifica in cele introduse
*/
void seteaza_participant(participant_p, char*, char*, int*);

/*
* Seteaza unui participant informatiile unui altul
* input - 2 participanti
* return - informatiile primului participant vor deveni la fel ca
		celui de-al doilea
*/
void atribuie_participant(participant_p, participant_p);

/*
* Compara 2 participanti
* input - 2 participanti
* return - 1 daca numele si prenumele participantilor coincid sau 0
*		in caz contrar
*/
int compara_participanti(participant_p, participant_p);

/*
* Se elibereaza din memorie un participant
* input - participant
* return - se elibereaza din memorie participantul introdus
*/
void distruge_participant(participant_p);