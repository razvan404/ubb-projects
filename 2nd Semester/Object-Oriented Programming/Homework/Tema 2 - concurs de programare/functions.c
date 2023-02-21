#pragma warning (disable:4996)
#include <string.h>
#include <stdlib.h>
#include "functions.h"
#include "participant.h"

long aprox(double t) {
	long t_real = t;
	if (t - t_real < 0.5) return t_real;
	else return t_real + 1;
}

char* autocorect(char* text) {
	char* text_cpy = malloc((strlen(text) + 1) * sizeof(char));
	strcpy(text_cpy, text);
	if (text_cpy[strlen(text_cpy) - 1] == '\n') {
		text_cpy[strlen(text_cpy) - 1] = '\0';
	}

	char text_corectat[200] = "";
	char* p;
	p = strtok(text_cpy, " -");
	while (p) {
		if (p[0] >= 'a' && p[0] <= 'z') p[0] += 'R' - 'r';
		for (unsigned i = 1; i < strlen(p); ++i) {
			if (p[i] >= 'A' && p[i] <= 'Z') p[i] += 'r' - 'R';
		}
		strcat(text_corectat, p);
		p = strtok(NULL, " ");
		if (p != NULL) strcat(text_corectat, " ");
	}
	free(text_cpy);
	return text_corectat;
}

int string_to_number(char* string) {
	for (unsigned i = 0; i < strlen(string); ++i) {
		if (string[i] < '0' || string[i] > '9') {
			return -1;
		}
	}
	return atoi(string);
}

int compara_participanti_scor_mai_mare(participant_p p1, participant_p p2) {
	return get_scor(p1) > get_scor(p2);
}

int compara_participanti_scor_mai_mic(participant_p p1, participant_p p2) {
	return get_scor(p1) < get_scor(p2);
}

int compara_participanti_alfabetic_crescator(participant_p p1, participant_p p2) {
	return strcmp(get_nume(p1), get_nume(p2)) > 0;
}

int compara_participanti_alfabetic_descrescator(participant_p p1, participant_p p2) {
	return strcmp(get_nume(p1), get_nume(p2)) < 0;
}