#pragma warning(disable: 4996)
#pragma warning(disable: 4113)
#pragma warning(disable: 4172)
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tests.h"
#include "functions.h"
#include "participant.h"
#include "vector.h"
#include "service.h"

void test_functions();
void test_participant();
void test_vector();
void test_service_adauga();
void test_service_modifica();
void test_service_sterge();
void test_service_filtrare_scor();
void test_service_filtrare_litera();
void test_service_sortare();

void test_all() {
	test_functions();
	test_participant();
	test_vector();
	test_service_adauga();
	test_service_modifica();
	test_service_sterge();
	test_service_filtrare_scor();
	test_service_filtrare_litera();
	test_service_sortare();
	printf("Testele au trecut cu succes!\n");
}

void test_functions() {
	assert(aprox(5.3) == 5);
	assert(aprox(7.9) == 8);
	assert(aprox(2.5) == 3);

	if (5 == 6) assert(false);
	elif(5 == 5) assert(true);
	else assert(false);

	assert(string_to_number("534") == 534);
	assert(string_to_number("221") == 221);
	assert(string_to_number("2a34") == -1);

	assert(strcmp(autocorect("carNAt"), "Carnat") == 0);
	assert(strcmp(autocorect("pIsIcA iNtErGaLaCtIcA sPaTiAlA aNtItErEsTrA"), "Pisica Intergalactica Spatiala Antiterestra") == 0);
	assert(strcmp(autocorect("a"), "A") == 0);
	char* str_temp = malloc(50 * sizeof(char));
	if (str_temp) {
		strcpy(str_temp, "caINe");
		strcat(str_temp, "\n");
		assert(strcmp(autocorect(str_temp), "Caine") == 0);
		free(str_temp);
	}	
}
void test_participant() {
	int probl1[] = { 8, 6, 6, 6, 6, 6, 6, 6, 6, 8 };
	participant_p p1 = initializeaza_participant("Popescu", "Alex", probl1);
	assert(strcmp(get_nume(p1), "Popescu") == 0);
	assert(strcmp(get_prenume(p1), "Alex") == 0);
	assert(get_scor(p1) == 64);

	int probl2[] = { 7, 4, 4, 4, 4, 4, 4, 4, 7, 7 };
	participant_p p2 = initializeaza_participant("Ionescu", "Vlad", probl2);
	assert(strcmp(get_nume(p2), "Ionescu") == 0);
	assert(strcmp(get_prenume(p2), "Vlad") == 0);
	assert(get_scor(p2) == 49);

	int probl3[] = { 9, 8, 8, 8, 8, 8, 8, 8, 8, 8 };
	participant_p p3 = initializeaza_participant("Georgescu", "Luiza", probl3);
	assert(strcmp(get_nume(p3), "Georgescu") == 0);
	assert(strcmp(get_prenume(p3), "Luiza") == 0);
	assert(get_scor(p3) == 81);

	int probl4[] = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
	seteaza_participant(p1, "Georgescu", "Luiza", probl4);
	assert(strcmp(get_nume(p1), "Georgescu") == 0);
	assert(strcmp(get_prenume(p1), "Luiza") == 0);
	assert(get_scor(p1) == 100);

	assert(compara_participanti(p1, p3) == 1);
	assert(compara_participanti(p1, p2) == 0);

	atribuie_participant(p1, p2);
	assert(compara_participanti(p1, p3) == 0);
	assert(compara_participanti(p1, p2) == 1);

	distruge_participant(p1);
	distruge_participant(p2);
	distruge_participant(p3);
}
void test_vector() {
	vector_p c = initializeaza_vector(100);

	assert(get_lungime(c) == 0);
	seteaza_lungime(c, 10);
	assert(get_lungime(c) == 10);
	assert(get_capacitate(c) == 100);
	seteaza_lungime(c, 0);
	

	int probl1[] = { 8, 6, 6, 6, 6, 6, 6, 6, 6, 8 };
	participant_p p1 = initializeaza_participant("Popescu", "Alex", probl1);
	int probl2[] = { 7, 4, 4, 4, 4, 4, 4, 4, 7, 7 };
	participant_p p2 = initializeaza_participant("Ionescu", "Vlad", probl2);
	int probl3[] = { 9, 8, 8, 8, 8, 8, 8, 8, 8, 8 };
	participant_p p3 = initializeaza_participant("Georgescu", "Luiza", probl3);

	adauga_element(&c, p1);
	adauga_element(&c, p2);
	adauga_element(&c, p3);

	assert(cauta_participant(c, p2) == 1);
	assert(cauta_participant(c, p3) == 2);

	assert(compara_participanti(get_element(c, 2), p3) == 1);
	assert(compara_participanti(get_element(c, 1), p2) == 1);
	assert(compara_participanti(get_element(c, 0), p1) == 1);
	assert(get_lungime(c) == 3);

	redimensioneaza_vector(&c);
	assert(get_capacitate(c) == 200);
	assert(compara_participanti(get_element(c, 2), p3) == 1);
	assert(compara_participanti(get_element(c, 1), p2) == 1);
	assert(compara_participanti(get_element(c, 0), p1) == 1);
	assert(get_lungime(c) == 3);

	seteaza_element(c, 1, p1);
	assert(compara_participanti(get_element(c, 1), p1) == 1);

	modifica_element(c, 2, p2);
	assert(cauta_participant(c, p3) == -1);
	assert(compara_participanti(get_element(c, 2), p2) == 1);

	scoate_element(c, 2);
	assert(get_lungime(c) == 2);

	distruge_participant(p1);
	distruge_participant(p2);
	distruge_participant(p3);
	distruge_vector(c);
}
void test_service_adauga() {
	vector_p c = initializeaza_vector(11);
	int note0[] = { 9, 9, 9, 9, 8, 8, 8, 8, 8, 10 };
	assert(adauga_participant(&c, "Hamed", "Ali", note0) == 0);
	assert(strcmp(get_nume(get_element(c, 0)), "Hamed") == 0);
	assert(get_scor(get_element(c, 0)) == 86);

	int note1[] = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 3 };
	assert(adauga_participant(&c, "Ephesius", "Alvin", note1) == 0);
	assert(strcmp(get_nume(get_element(c, 1)), "Ephesius") == 0);
	assert(get_scor(get_element(c, 1)) == 39);

	int note2[] = { 5, 5, 5, 5, 4, 4, 4, 4, 4, 5 };
	assert(adauga_participant(&c, "Saqui", "Karmen", note2) == 0);
	assert(strcmp(get_nume(get_element(c, 2)), "Saqui") == 0);
	assert(get_scor(get_element(c, 2)) == 45);

	int note3[] = { 10, 10, 10, 9, 8, 8, 8, 8, 8, 10 };
	assert(adauga_participant(&c, "Meaghan", "Noelia", note3) == 0);
	assert(strcmp(get_nume(get_element(c, 3)), "Meaghan") == 0);
	assert(get_scor(get_element(c, 3)) == 89);

	int note4[] = { 7, 7, 7, 7, 7, 7, 7, 7, 6, 6 };
	assert(adauga_participant(&c, "Elli", "Mattanyahu", note4) == 0);
	assert(strcmp(get_nume(get_element(c, 4)), "Elli") == 0);
	assert(get_scor(get_element(c, 4)) == 68);

	int note5[] = { 6, 6, 6, 6, 6, 6, 6, 5, 5, 5 };
	assert(adauga_participant(&c, "Ezechias", "Sophronius", note5) == 0);
	assert(strcmp(get_nume(get_element(c, 5)), "Ezechias") == 0);
	assert(get_scor(get_element(c, 5)) == 57);

	int note6[] = { 5, 5, 5, 5, 5, 5, 5, 4, 4, 4 };
	assert(adauga_participant(&c, "Idir", "Sirius", note6) == 0);
	assert(strcmp(get_nume(get_element(c, 6)), "Idir") == 0);
	assert(get_scor(get_element(c, 6)) == 47);

	int note7[] = { 10, 10, 10, 10, 10, 9, 9, 9, 9, 9 };
	assert(adauga_participant(&c, "Amalija", "Zorro", note7) == 0);
	assert(strcmp(get_nume(get_element(c, 7)), "Amalija") == 0);
	assert(get_scor(get_element(c, 7)) == 95);

	int note8[] = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
	assert(adauga_participant(&c, "Jessika", "Nicolas", note8) == 0);
	assert(strcmp(get_nume(get_element(c, 8)), "Jessika") == 0);
	assert(get_scor(get_element(c, 8)) == 100);

	int note9[] = { 8, 8, 8, 8, 8, 8, 8, 7, 7, 7 };
	assert(adauga_participant(&c, "Drakon", "Onesimos", note9) == 0);
	assert(strcmp(get_nume(get_element(c, 9)), "Drakon") == 0);
	assert(get_scor(get_element(c, 9)) == 77);

	int note10[] = { 7, 7, 7, 7, 7, 7, 7, 6, 6, 6 };
	assert(adauga_participant(&c, "Saqui", "Karmen", note10) == -1);
	int note11[] = { 7, 7, 7, 7, 7, 7, 7, 6, 6, 11 };
	assert(adauga_participant(&c, "Sa", "Ka", note11) == -2);

	assert(get_lungime(c) == 10);
	assert(id_participant(c, "Meaghan", "Noelia") == 3);

	assert(adauga_participant(&c, "Drako", "Onesimo", note9) == 0);
	assert(adauga_participant(&c, "Drakzz", "Onesimzz", note9) == 0);

	assert(get_capacitate(c) == 22);
	assert(strcmp(get_nume(get_element(c, 0)), "Hamed") == 0);
	assert(get_scor(get_element(c, 0)) == 86);
	assert(strcmp(get_nume(get_element(c, 1)), "Ephesius") == 0);
	assert(get_scor(get_element(c, 1)) == 39);
	assert(strcmp(get_nume(get_element(c, 2)), "Saqui") == 0);
	assert(get_scor(get_element(c, 2)) == 45);
	assert(strcmp(get_nume(get_element(c, 3)), "Meaghan") == 0);
	assert(get_scor(get_element(c, 3)) == 89);
	assert(strcmp(get_nume(get_element(c, 4)), "Elli") == 0);
	assert(get_scor(get_element(c, 4)) == 68);
	assert(strcmp(get_nume(get_element(c, 5)), "Ezechias") == 0);
	assert(get_scor(get_element(c, 5)) == 57);
	assert(strcmp(get_nume(get_element(c, 6)), "Idir") == 0);
	assert(get_scor(get_element(c, 6)) == 47);
	assert(strcmp(get_nume(get_element(c, 7)), "Amalija") == 0);
	assert(get_scor(get_element(c, 7)) == 95);
	assert(strcmp(get_nume(get_element(c, 8)), "Jessika") == 0);
	assert(get_scor(get_element(c, 8)) == 100);
	assert(strcmp(get_nume(get_element(c, 9)), "Drakon") == 0);
	assert(get_scor(get_element(c, 9)) == 77);

	distruge_concurs(c);
}
void test_service_modifica() {
	vector_p c = initializeaza_vector(100);

	int note0[] = { 9, 9, 9, 9, 8, 8, 8, 8, 8, 10 };
	int note1[] = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 3 };
	int note2[] = { 5, 5, 5, 5, 4, 4, 4, 4, 4, 5 };
	int note3[] = { 10, 10, 10, 9, 8, 8, 8, 8, 8, 10 };
	int note4[] = { 7, 7, 7, 7, 7, 7, 7, 7, 6, 6 };
	int note5[] = { 6, 6, 6, 6, 6, 6, 6, 5, 5, 5 };
	int note6[] = { 5, 5, 5, 5, 5, 5, 5, 4, 4, 4 };
	int note7[] = { 10, 10, 10, 10, 10, 9, 9, 9, 9, 9 };
	int note8[] = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
	int note9[] = { 8, 8, 8, 8, 8, 8, 8, 7, 7, 7 };
	int note10[] = { 7, 7, 7, 7, 11, 7, 7, 6, 6, 6 };

	adauga_participant(&c, "Hamed", "Ali", note0);
	adauga_participant(&c, "Ephesius", "Alvin", note1);
	adauga_participant(&c, "Saqui", "Karmen", note2);
	adauga_participant(&c, "Meaghan", "Noelia", note3);
	adauga_participant(&c, "Elli", "Mattanyahu", note4);
	adauga_participant(&c, "Ezechias", "Sophronius", note5);
	adauga_participant(&c, "Idir", "Sirius", note6);
	adauga_participant(&c, "Amalija", "Zorro", note7);
	adauga_participant(&c, "Jessika", "Nicolas", note8);
	adauga_participant(&c, "Drakon", "Onesimos", note9);

	assert(modifica_participant(c, 8, "Valentin", "-", note10, 0) == 0);
	assert(modifica_participant(c, 8, "Valentin", "Andrei", note10, 1) == -1);
	assert(strcmp(get_nume(get_element(c, 8)), "Valentin") == 0);
	assert(strcmp(get_prenume(get_element(c, 8)), "Nicolas") == 0);
	assert(get_scor(get_element(c, 8)) == 100);

	assert(modifica_participant(c, 7, "-", "-", note10, 0) == 0);
	assert(strcmp(get_nume(get_element(c, 7)), "Amalija") == 0);
	assert(strcmp(get_prenume(get_element(c, 7)), "Zorro") == 0);
	assert(get_scor(get_element(c, 7)) == 95);
	assert(modifica_participant(c, 7, "Valentin", "Nicolas", note10, 0) == -1);

	distruge_concurs(c);
}
void test_service_sterge() {
	vector_p c = initializeaza_vector(100);

	int note0[] = { 9, 9, 9, 9, 8, 8, 8, 8, 8, 10 };
	int note1[] = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 3 };
	int note2[] = { 5, 5, 5, 5, 4, 4, 4, 4, 4, 5 };
	int note3[] = { 10, 10, 10, 9, 8, 8, 8, 8, 8, 10 };
	int note4[] = { 7, 7, 7, 7, 7, 7, 7, 7, 6, 6 };
	int note5[] = { 6, 6, 6, 6, 6, 6, 6, 5, 5, 5 };
	int note6[] = { 5, 5, 5, 5, 5, 5, 5, 4, 4, 4 };
	int note7[] = { 10, 10, 10, 10, 10, 9, 9, 9, 9, 9 };
	int note8[] = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
	int note9[] = { 8, 8, 8, 8, 8, 8, 8, 7, 7, 7 };

	adauga_participant(&c, "Hamed", "Ali", note0);
	adauga_participant(&c, "Ephesius", "Alvin", note1);
	adauga_participant(&c, "Saqui", "Karmen", note2);
	adauga_participant(&c, "Meaghan", "Noelia", note3);
	adauga_participant(&c, "Elli", "Mattanyahu", note4);
	adauga_participant(&c, "Ezechias", "Sophronius", note5);
	adauga_participant(&c, "Idir", "Sirius", note6);
	adauga_participant(&c, "Amalija", "Zorro", note7);
	adauga_participant(&c, "Jessika", "Nicolas", note8);
	adauga_participant(&c, "Drakon", "Onesimos", note9);

	assert(sterge_participant(c, 9) == 0);
	assert(sterge_participant(c, 9) == -1);
	assert(get_lungime(c) == 9);

	assert(sterge_participant(c, 1) == 0);
	assert(sterge_participant(c, 2) == 0);
	assert(sterge_participant(c, 3) == 0);
	assert(sterge_participant(c, 4) == 0);

	assert(get_lungime(c) == 5);
	assert(strcmp(get_nume(get_element(c, 4)), "Jessika") == 0);
	assert(strcmp(get_nume(get_element(c, 3)), "Idir") == 0);
	assert(strcmp(get_nume(get_element(c, 2)), "Elli") == 0);
	assert(strcmp(get_nume(get_element(c, 1)), "Saqui") == 0);
	assert(strcmp(get_nume(get_element(c, 0)), "Hamed") == 0);

	distruge_concurs(c);
}
void test_service_filtrare_scor() {
	vector_p c = initializeaza_vector(100);

	int note0[] = { 9, 9, 9, 9, 8, 8, 8, 8, 8, 10 };
	int note1[] = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 3 };
	int note2[] = { 5, 5, 5, 5, 4, 4, 4, 4, 4, 5 };
	int note3[] = { 10, 10, 10, 9, 8, 8, 8, 8, 8, 10 };
	int note4[] = { 7, 7, 7, 7, 7, 7, 7, 7, 6, 6 };
	int note5[] = { 6, 6, 6, 6, 6, 6, 6, 5, 5, 5 };
	int note6[] = { 5, 5, 5, 5, 5, 5, 5, 4, 4, 4 };
	int note7[] = { 10, 10, 10, 10, 10, 9, 9, 9, 9, 9 };
	int note8[] = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
	int note9[] = { 8, 8, 8, 8, 8, 8, 8, 7, 7, 7 };

	adauga_participant(&c, "Hamed", "Ali", note0);
	adauga_participant(&c, "Ephesius", "Alvin", note1);
	adauga_participant(&c, "Saqui", "Karmen", note2);
	adauga_participant(&c, "Meaghan", "Noelia", note3);
	adauga_participant(&c, "Elli", "Mattanyahu", note4);
	adauga_participant(&c, "Ezechias", "Sophronius", note5);
	adauga_participant(&c, "Idir", "Sirius", note6);
	adauga_participant(&c, "Amalija", "Zorro", note7);
	adauga_participant(&c, "Jessika", "Nicolas", note8);
	adauga_participant(&c, "Drakon", "Onesimos", note9);

	vector_p c1 = filtreaza_scor_mai_mic(c, 77);
	assert(get_lungime(c1) == 5);

	assert(strcmp(get_nume(get_element(c1, 0)), "Ephesius") == 0);
	assert(strcmp(get_nume(get_element(c1, 1)), "Saqui") == 0);
	assert(strcmp(get_nume(get_element(c1, 2)), "Elli") == 0);
	assert(strcmp(get_nume(get_element(c1, 3)), "Ezechias") == 0);
	assert(strcmp(get_nume(get_element(c1, 4)), "Idir") == 0);

	vector_p c2 = filtreaza_scor_mai_mic(c, 39);
	assert(get_lungime(c2) == 0);

	distruge_concurs(c1);
	distruge_concurs(c2);
	distruge_concurs(c);
}
void test_service_filtrare_litera() {
	vector_p c = initializeaza_vector(100);

	int note0[] = { 9, 9, 9, 9, 8, 8, 8, 8, 8, 10 };
	int note1[] = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 3 };
	int note2[] = { 5, 5, 5, 5, 4, 4, 4, 4, 4, 5 };
	int note3[] = { 10, 10, 10, 9, 8, 8, 8, 8, 8, 10 };
	int note4[] = { 7, 7, 7, 7, 7, 7, 7, 7, 6, 6 };
	int note5[] = { 6, 6, 6, 6, 6, 6, 6, 5, 5, 5 };
	int note6[] = { 5, 5, 5, 5, 5, 5, 5, 4, 4, 4 };
	int note7[] = { 10, 10, 10, 10, 10, 9, 9, 9, 9, 9 };
	int note8[] = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
	int note9[] = { 8, 8, 8, 8, 8, 8, 8, 7, 7, 7 };

	adauga_participant(&c, "Hamed", "Ali", note0);
	adauga_participant(&c, "Ephesius", "Alvin", note1);
	adauga_participant(&c, "Saqui", "Karmen", note2);
	adauga_participant(&c, "Meaghan", "Noelia", note3);
	adauga_participant(&c, "Elli", "Mattanyahu", note4);
	adauga_participant(&c, "Ezechias", "Sophronius", note5);
	adauga_participant(&c, "Idir", "Sirius", note6);
	adauga_participant(&c, "Amalija", "Zorro", note7);
	adauga_participant(&c, "Jessika", "Nicolas", note8);
	adauga_participant(&c, "Drakon", "Onesimos", note9);

	vector_p c1 = filtreaza_prima_litera(c, 'E');
	assert(get_lungime(c1) == 3);

	assert(strcmp(get_nume(get_element(c1, 0)), "Ephesius") == 0);
	assert(strcmp(get_nume(get_element(c1, 1)), "Elli") == 0);
	assert(strcmp(get_nume(get_element(c1, 2)), "Ezechias") == 0);

	vector_p c2 = filtreaza_prima_litera(c, 'C');
	assert(get_lungime(c2) == 0);

	distruge_concurs(c1);
	distruge_concurs(c2);
	distruge_concurs(c);
}
void test_service_sortare() {
	vector_p c = initializeaza_vector(100);

	int note0[] = { 9, 9, 9, 9, 8, 8, 8, 8, 8, 10 };
	int note1[] = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 3 };
	int note2[] = { 5, 5, 5, 5, 4, 4, 4, 4, 4, 5 };
	int note3[] = { 10, 10, 10, 9, 8, 8, 8, 8, 8, 10 };
	int note4[] = { 7, 7, 7, 7, 7, 7, 7, 7, 6, 6 };
	int note5[] = { 6, 6, 6, 6, 6, 6, 6, 5, 5, 5 };
	int note6[] = { 5, 5, 5, 5, 5, 5, 5, 4, 4, 4 };
	int note7[] = { 10, 10, 10, 10, 10, 9, 9, 9, 9, 9 };
	int note8[] = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
	int note9[] = { 8, 8, 8, 8, 8, 8, 8, 7, 7, 7 };

	adauga_participant(&c, "Hamed", "Ali", note0);
	adauga_participant(&c, "Ephesius", "Alvin", note1);
	adauga_participant(&c, "Saqui", "Karmen", note2);
	adauga_participant(&c, "Meaghan", "Noelia", note3);
	adauga_participant(&c, "Elli", "Mattanyahu", note4);
	adauga_participant(&c, "Ezechias", "Sophronius", note5);
	adauga_participant(&c, "Idir", "Sirius", note6);
	adauga_participant(&c, "Amalija", "Zorro", note7);
	adauga_participant(&c, "Jessika", "Nicolas", note8);
	adauga_participant(&c, "Drakon", "Onesimos", note9);

	int (*compare)(participant_p, participant_p);

	compare = compara_participanti_scor_mai_mare;
	sorteaza_participanti(c, compare);
	assert(strcmp(get_nume(get_element(c, 0)), "Ephesius") == 0);
	assert(strcmp(get_nume(get_element(c, 1)), "Saqui") == 0);
	assert(strcmp(get_nume(get_element(c, 2)), "Idir") == 0);

	compare = compara_participanti_scor_mai_mic;
	sorteaza_participanti(c, compare);
	assert(strcmp(get_nume(get_element(c, 0)), "Jessika") == 0);
	assert(strcmp(get_nume(get_element(c, 1)), "Amalija") == 0);
	assert(strcmp(get_nume(get_element(c, 2)), "Meaghan") == 0);

	compare = compara_participanti_alfabetic_crescator;
	sorteaza_participanti(c, compare);
	assert(strcmp(get_nume(get_element(c, 0)), "Amalija") == 0);
	assert(strcmp(get_nume(get_element(c, 1)), "Drakon") == 0);
	assert(strcmp(get_nume(get_element(c, 2)), "Elli") == 0);

	compare = compara_participanti_alfabetic_descrescator;
	sorteaza_participanti(c, compare);
	assert(strcmp(get_nume(get_element(c, 0)), "Saqui") == 0);
	assert(strcmp(get_nume(get_element(c, 1)), "Meaghan") == 0);
	assert(strcmp(get_nume(get_element(c, 2)), "Jessika") == 0);

	distruge_concurs(c);
}
