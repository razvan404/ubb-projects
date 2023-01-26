#include "vector.h"
#include "participant.h"
#include <stdlib.h>

vector_p initializeaza_vector(int capacity) {
	vector_p v = malloc(sizeof(vector_t));
	if (v) {
		v->elems = malloc((capacity + 1) * sizeof(TElem));
		v->len = 0;
		v->capacity = capacity;
		return v;
	}
}

void redimensioneaza_vector(vector_p* v) {
	int new_capacity = 2 * (*v)->capacity;
	vector_p v_new = initializeaza_vector(new_capacity);
	v_new->len = (*v)->len;
	for (int i = 0; i < (*v)->len; ++i) {
		v_new->elems[i] = (*v)->elems[i];
	}
	free((*v)->elems);
	free(*v);
	*v = v_new;
}

int get_lungime(vector_p c) {
	return c->len;
}

TElem get_element(vector_p c, int i) {
	return c->elems[i];
}

int get_capacitate(vector_p c) {
	return c->capacity;
}

void seteaza_lungime(vector_p c, int value) {
	c->len = value;
}

void seteaza_element(vector_p c, int i, TElem p) {
	c->elems[i] = p;
}

int valideaza_pozitie(vector_p c, int i) {
	if (i < 0 || i >= get_lungime(c)) return 0;
	return 1;
}

void adauga_element(vector_p* c, TElem p) {
	if (get_lungime(*c) + 1 > get_capacitate(*c)) {
		redimensioneaza_vector(c);
	}
	(*c)->elems[(*c)->len] = p;
	(*c)->len++;
}

void modifica_element(vector_p c, int i, TElem p_new) {
	c->elems[i] = p_new;
}

TElem scoate_element(vector_p c, int i) {
	TElem old = c->elems[i];
	for (int j = i; j < c->len - 1; ++j) {
		c->elems[j] = c->elems[j + 1];
	}
	c->len--;
	return old;
}

void interschimba_elemente(vector_p c, int a, int b) {
	TElem auxiliar;
	auxiliar = c->elems[a];
	c->elems[a] = c->elems[b];
	c->elems[b] = auxiliar;
}

void distruge_vector(vector_p c) {
	free(c->elems);
	free(c);
}