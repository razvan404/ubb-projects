#pragma warning (disable:4996)
#include <stdlib.h>
#include <string.h>
#include "participant.h"
#include "functions.h"

participant_p initializeaza_participant(char* nume, char* prenume, int* probleme) {
	participant_p participant = malloc(sizeof(participant_t));
	if (participant) {
		participant->nume = malloc(200 * sizeof(char));
		participant->prenume = malloc(200 * sizeof(char));
		participant->probleme = malloc(10 * sizeof(int));
		participant->scor = 0;

		if (participant->nume && participant->prenume && participant->probleme) {
			strcpy(participant->nume, autocorect(nume));
			strcpy(participant->prenume, autocorect(prenume));

			for (int i = 0; i < 10; ++i) {
				participant->probleme[i] = probleme[i];
				participant->scor += probleme[i];
			}

			return participant;
		}
	}
}

int valideaza_participant(participant_p participant) {
	for (int i = 0; i < 10; ++i) {
		if (participant->probleme[i] < 0 || participant->probleme[i] > 10) {
			return -1;
		}
	}
	return 0;
}

char* get_nume(participant_p participant) {
	return participant->nume;
}

char* get_prenume(participant_p participant) {
	return participant->prenume;
}

int* get_probleme(participant_p participant) {
	return participant->probleme;
}

int get_scor(participant_p participant) {
	return participant->scor;
}

void seteaza_nume(participant_p p, char* nume) {
	strcpy(p->nume, nume);
}

void seteaza_prenume(participant_p p, char* prenume) {
	strcpy(p->prenume, prenume);
}

void seteaza_scor(participant_p p, int scor) {
	p->scor = scor;
}

void seteaza_probleme(participant_p p, int* probleme) {
	int scor = 0;
	for (int i = 0; i < 10; ++i) {
		p->probleme[i] = probleme[i];
		scor += probleme[i];
	}
	seteaza_scor(p, scor);
}

void seteaza_participant(participant_p p, char* nume, char* prenume, int* probleme) {
	seteaza_nume(p, nume);
	seteaza_prenume(p, prenume);
	seteaza_probleme(p, probleme);
}

void atribuie_participant(participant_p p1, participant_p p2) {
	seteaza_nume(p1, get_nume(p2));
	seteaza_prenume(p1, get_prenume(p2));
	seteaza_probleme(p1, get_probleme(p2));
}

int compara_participanti(participant_p p1, participant_p p2) {
	return (strcmp(get_nume(p1), get_nume(p2)) == 0) && (strcmp(get_prenume(p1), get_prenume(p2)) == 0);
}

void distruge_participant(participant_p p) {
	free(p->nume);
	free(p->prenume);
	free(p->probleme);
	free(p);
}
