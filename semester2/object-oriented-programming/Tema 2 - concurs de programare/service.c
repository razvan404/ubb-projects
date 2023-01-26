#pragma warning (disable:4996)
#include <string.h>
#include <stdlib.h>
#include "service.h"
#include "vector.h"
#include "participant.h"
#include "functions.h"

int cauta_participant(vector_p c, TElem p) {
	for (int i = 0; i < get_lungime(c); ++i) {
		if (compara_participanti(get_element(c, i), p) == 1) return i;
	}
	return -1;
}

int id_participant(vector_p c, char* nume, char* prenume) {
	int note[] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	participant_p p_temp = initializeaza_participant(nume, prenume, note);
	int ID = cauta_participant(c, p_temp);
	distruge_participant(p_temp);
	return ID;
}

int adauga_participant(vector_p* c, char* nume, char* prenume, int* probl) {
	
	participant_p p_temp = initializeaza_participant(nume, prenume, probl);
	if (valideaza_participant(p_temp) == -1) {
		distruge_participant(p_temp);
		return -2;
	}

	if (cauta_participant(*c, p_temp) == -1) {
		adauga_element(c, p_temp);
		return 0;
	}
	distruge_participant(p_temp);
	return -1;
}

int modifica_participant(vector_p c, int ID, char* nume, char* prenume, int* probl, int modify_scor) {
	participant_p p_initial = get_element(c, ID);
	char* nume_nou = malloc(200 * sizeof(char));
	char* prenume_nou = malloc(200 * sizeof(char));
	int* probl_noi = malloc(10 * sizeof(int));

	if (nume_nou && prenume_nou && probl_noi) {
		if (strcmp(nume, "-") == 0) {
			strcpy(nume_nou, get_nume(p_initial));
		}
		else {
			strcpy(nume_nou, nume);
		}

		if (strcmp(prenume, "-") == 0) {
			strcpy(prenume_nou, get_prenume(p_initial));
		}
		else {
			strcpy(prenume_nou, prenume);
		}

		if (modify_scor == 0) {
			for (int i = 0; i < 10; ++i) {
				probl_noi[i] = get_probleme(p_initial)[i];
			}
		}
		elif (modify_scor == 1) {
			for (int i = 0; i < 10; ++i) {
				probl_noi[i] = probl[i];
			}
		}

		participant_p p_temp = initializeaza_participant(nume_nou, prenume_nou, probl_noi);

		free(nume_nou);
		free(prenume_nou);
		free(probl_noi);

		if (valideaza_participant(p_temp) == -1) {
			distruge_participant(p_temp);
			return -1;
		}

		if (cauta_participant(c, p_temp) != -1 && cauta_participant(c, p_temp) != ID) {
			distruge_participant(p_temp);
			return -1;
		}
		modifica_element(c, ID, p_temp);
		distruge_participant(p_initial);
		return 0;
	}
}

int sterge_participant(vector_p c, int ID) {
	if (valideaza_pozitie(c, ID) == 0) {
		return -1;
	}
	participant_p p_temp = scoate_element(c, ID);
	distruge_participant(p_temp);
	return 0;
}

vector_p filtreaza_scor_mai_mic(vector_p c, int scor) {
	vector_p c_filter = initializeaza_vector(get_lungime(c));
	for (int i = 0; i < get_lungime(c); ++i) {
		if (get_scor(get_element(c, i)) < scor) {
			int note[] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
			participant_p p_temp = initializeaza_participant("", "", note);
			atribuie_participant(p_temp, get_element(c, i));
			adauga_element(&c_filter, p_temp);
		}
	}
	return c_filter;
}

vector_p filtreaza_prima_litera(vector_p c, char litera) {
	vector_p c_filter = initializeaza_vector(get_lungime(c));
	for (int i = 0; i < get_lungime(c); ++i) {
		if (get_nume(get_element(c, i))[0] == litera) {
			int note[] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
			participant_p p_temp = initializeaza_participant("", "", note);
			atribuie_participant(p_temp, get_element(c, i));
			adauga_element(&c_filter, p_temp);
		}
	}
	return c_filter;
}

void sorteaza_participanti(vector_p c, int(*compare)(participant_p, participant_p)) {
	int sorted = 0;
	while (!sorted) {
		sorted = 1;
		for (int i = 1; i < get_lungime(c); ++i) {
			if (compare(get_element(c, i - 1), get_element(c, i)) == 1) {
				sorted = 0;
				interschimba_elemente(c, i - 1, i);
			}
		}
	}
}

void distruge_concurs(vector_p v) {
	for (int i = 0; i < get_lungime(v); ++i) {
		distruge_participant(get_element(v, i));
	}
	distruge_vector(v);
}
