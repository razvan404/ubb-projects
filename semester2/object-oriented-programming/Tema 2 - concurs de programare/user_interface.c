#pragma warning (disable: 4996)
#pragma warning (disable: 4113)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user_interface.h"
#include "service.h"
#include "vector.h"
#include "participant.h"
#include "functions.h"

int global_menuUI() {
	printf("Concurs de programare\n");
	printf(" 1) Adauga participant\n");
	printf(" 2) Actualizare participant\n");
	printf(" 3) Sterge participant\n");
	printf(" 4) Filtrare participanti\n");
	printf(" 5) Sortare participanti\n");
	printf(" 6) Afisare participanti\n");
	printf(" 0) Opreste aplicatia\n");
	printf("Introdu o optiune: ");
	int cmd;
	scanf("%d", &cmd);
	return cmd;
}
void afisare_concurentiUI(vector_p c) {
	printf("Afisare participanti\n");

	if (get_lungime(c) == 0) {
		printf(" Nu exista concurenti!\n\n");
		return;
	}
	for (int i = 0; i < get_lungime(c); ++i) {
		participant_p p_current = get_element(c, i);
		printf(" %d | Nume: %s |", i, get_nume(p_current));
		printf(" Prenume: %s | Scor: %d (", get_prenume(p_current), get_scor(p_current));
		for (int j = 0; j < 9; ++j) {
			printf("%d/", get_probleme(get_element(c, i))[j]);
		}
		printf("%d)\n", get_probleme(get_element(c, i))[9]);
	}
	printf("\n");
}
void adauga_concurentUI(vector_p* c) {
	printf("Adauga participant\n");

	char* nume = (char*)malloc(200 * sizeof(char));
	char* prenume = (char*)malloc(200 * sizeof(char));
	int* probl = (int*)malloc(10 * sizeof(int));

	printf(" Numele participantului: ");
	scanf("%s", nume);
	printf(" Prenumele participantului: ");
	rewind(stdin);
	fgets(prenume, 200, stdin);

	for (int i = 0; i < 10; ++i) {
		char* buffer = (char*)malloc(200 * sizeof(char));
		do {
			printf("  Scorul la problema %d: ", i + 1);
			scanf("%s", buffer);
			probl[i] = string_to_number(buffer);
			if (probl[i] == -1) {
				printf(" Scorul trebuie sa fie un numar, incearca din nou!\n");
			}
		} while (probl[i] == -1);
		free(buffer);
	}

	int error_message = adauga_participant(c, nume, prenume, probl);
	if (error_message == 0) printf("Participantul a fost adaugat cu succes!\n\n");
	elif (error_message == -1) printf("Participantul nu a putut fi adaugat deoarece se afla deja in cadrul concursului!\n\n");
	elif (error_message == -2) printf("Participantul nu a putut fi adaugat deoarece scorul este invalid (trebuie note de la 0 la 10)!\n\n"); 
	elif (error_message == -3) printf("Participiantul nu a putut fi adaugat deoarece s-a atins capacitatea maxima a concursului!\n\n");
	free(nume);
	free(prenume);
	free(probl);
}

void modifica_concurentUI(vector_p c) {
	printf("Modifica participant\n");
	printf(" 1) Modifica participant dupa pozitie\n");
	printf(" 2) Modifica participant dupa nume si prenume\n");
	printf("Introdu o optiune: ");
	int cmd;
	scanf("%d", &cmd);
	if (cmd == 1) {
		int ID, if_probl = 0;
		char* nume = malloc(200 * sizeof(char));
		char* prenume = malloc(200 * sizeof(char));
		int* probl = malloc(10 * sizeof(int));
		printf(" Introdu pozitia participantului care doresti sa fie modificat: ");
		scanf("%d", &ID);
		if (valideaza_pozitie(c, ID) == 0) {
			printf("Pozitia este invalida!\n\n");
			free(nume);
			free(prenume);
			free(probl);
			return;
		}
		printf(" Introdu un nou nume (sau caracterul '-' daca nu doresti o modificare): ");
		scanf("%s", nume);

		printf(" Introdu un nou prenume (sau caracterul '-' daca nu doresti o modificare): ");
		rewind(stdin);
		fgets(prenume, 200, stdin);
		
		printf(" Introdu 1 daca doresti o modificare a scorului sau 0 in caz contrar: ");
		scanf("%d", &if_probl);
		if (if_probl == 1) {
			for (int i = 0; i < 10; ++i) {
				printf("  Scorul la problema %d: ", i + 1);
				scanf("%d", &probl[i]);
			}
		}
		elif (if_probl != 0) {
			printf("Optiune invalida!\n\n");
			free(nume);
			free(prenume);
			free(probl);
			return;
		}

		if (modifica_participant(c, ID, nume, prenume, probl, if_probl) == -1) {
			printf("Modificarea nu a putut fi efectuata!\n\n");
		}
		else printf("Modificarea a fost efectuata cu succes!\n\n");
		free(nume);
		free(prenume);
		free(probl);
	}
	elif (cmd == 2) {
		char* nume = malloc(200 * sizeof(char));
		char* prenume = malloc(200 * sizeof(char));
		int* probl = malloc(10 * sizeof(int));
		int if_probl = 0;
		printf(" Numele participantului care trebuie modificat: ");
		scanf("%s", nume);
		printf(" Prenumele participantului care trebuie modificat: ");
		rewind(stdin);
		fgets(prenume, 200, stdin);

		int ID = id_participant(c, nume, prenume);
		if (ID == -1) {
			printf("Datele introduse sunt invalide!\n\n");
			free(nume);
			free(prenume);
			free(probl);
			return;
		}

		printf(" Introdu un nou nume (sau caracterul '-' daca nu doresti o modificare): ");
		scanf("%s", nume);

		printf(" Introdu un nou prenume (sau caracterul '-' daca nu doresti o modificare): ");
		rewind(stdin);
		fgets(prenume, 200, stdin);

		printf(" Introdu 1 daca doresti o modificare a scorului sau 0 in caz contrar: ");
		scanf("%d", &if_probl);
		if (if_probl == 1) {
			for (int i = 0; i < 10; ++i) {
				printf("  Scorul la problema %d: ", i + 1);
				scanf("%d", &probl[i]);
			}
		}
		elif(if_probl != 0) {
			printf("Optiune invalida!\n\n");
			free(nume);
			free(prenume);
			free(probl);
			return;
		}

		if (modifica_participant(c, ID, nume, prenume, probl, if_probl) == -1) {
			printf("Modificarea nu a putut fi efectuata!\n\n");
		}
		else printf("Modificarea a fost efectuata cu succes!\n\n");
		free(nume);
		free(prenume);
		free(probl);
	}
	else printf("Optiune invalida!\n\n");
}
void sterge_concurentUI(vector_p c) {
	printf("Stergere participant\n");
	printf(" 1) Sterge participant dupa pozitie\n");
	printf(" 2) Sterge participant dupa nume si prenume\n");
	printf("Introdu o optiune: ");
	int cmd;
	scanf("%d", &cmd);
	if (cmd == 1) {
		int ID;
		printf(" Introdu pozitia participantului care doresti sa fie sters: ");
		scanf("%d", &ID);
		if (sterge_participant(c, ID) == -1) {
			printf("Stergerea nu a putut avea loc!\n\n");
		}
		else {
			printf("Stergerea a fost efectuata cu succes!\n\n");
		}
	}
	elif (cmd == 2) {
		char nume[200], prenume[200];
		printf(" Numele participantului care trebuie sa fie sters: ");
		scanf("%s", nume);
		printf(" Prenumele participantului care trebuie sa fie sters: ");
		rewind(stdin);
		fgets(prenume, 200, stdin);

		int ID = id_participant(c, nume, prenume);
		if (ID == -1) {
			printf("Datele au fost introduse gresit!\n\n");
			return;
		}
		if (sterge_participant(c, ID) == -1) {
			printf("Stergerea nu a putut avea loc!\n\n");
		}
		else {
			printf("Stergerea a fost efectuata cu succes!\n\n");
		}
	}
	else printf("Optiune invalida!\n\n");
}
void filtrare_concurentiUI(vector_p c) {
	printf("Filtrare participanti\n");
	printf(" 1) Afisarea celor cu scorul mai mic decat o valoare data\n");
	printf(" 2) Afisarea celor al caror nume incep cu o litera data\n");
	printf("Introdu o optiune: ");
	int cmd;
	scanf("%d", &cmd);
	if (cmd == 1) {
		printf(" Introdu o valoare: ");
		int val, passed = 0;
		scanf("%d", &val);
		vector_p c_filter = filtreaza_scor_mai_mic(c, val);
		if (!get_lungime(c_filter)) {
			printf("Nu exista participanti cu scorul mai mic decat %d!\n\n", val);
			distruge_concurs(c_filter);
			return;
		}
		printf("Participantii cu scorul mai mic decat %d:\n", val);
		for (int i = 0; i < get_lungime(c_filter); ++i) {
			printf(" %d | Nume: %s |", i, get_nume(get_element(c_filter, i)));
			printf(" Prenume: %s", get_prenume(get_element(c_filter, i)));
			printf(" | Scor: %d (",	get_scor(get_element(c_filter, i)));
			for (int j = 0; j < 9; ++j) {
				printf("%d/", get_probleme(get_element(c_filter, i))[j]);
			}
			printf("%d)\n", get_probleme(get_element(c_filter, i))[9]);
		}
		distruge_concurs(c_filter);
		printf("\n");
	}
	elif (cmd == 2) {
		printf(" Introdu o litera: ");
		char input[20];
		scanf("%s", input);
		if (strlen(input) > 1) {
			printf("Nu ai introdus o litera!\n\n");
			return;
		}
		char litera = autocorect(input)[0];
		vector_p c_filter = filtreaza_prima_litera(c, litera);
		if (!get_lungime(c_filter)) {
			printf("Nu exista participanti care au prima litera a numelui '%c'!\n\n", litera);
			distruge_concurs(c_filter);
			return;
		}
		printf("Participantii care au prima litera a numelui '%c':\n", litera);
		for (int i = 0; i < get_lungime(c_filter); ++i) {
			printf(" %d | Nume: %s |", i, get_nume(get_element(c_filter, i)));
			printf(" Prenume: %s", get_prenume(get_element(c_filter, i)));
			printf(" | Scor: %d (", get_scor(get_element(c_filter, i)));
			for (int j = 0; j < 9; ++j) {
				printf("%d/", get_probleme(get_element(c_filter, i))[j]);
			}
			printf("%d)\n", get_probleme(get_element(c_filter, i))[9]);
		}
		distruge_concurs(c_filter);
		printf("\n");
	}
	else printf("Optiune invalida!\n\n");
}
void sortare_concurentiUI(vector_p c) {
	printf("Sortare participanti\n");
	printf(" 1) Dupa scor\n");
	printf(" 2) Dupa nume\n");
	printf("Introdu o optiune: ");
	int cmd;
	scanf("%d", &cmd);

	int (*compare)(participant_p, participant_p, char*);

	if (cmd == 1) {
		printf("\nSortare participanti dupa scor\n");
		printf(" 1) Crescator\n");
		printf(" 2) Descrescator\n");
		printf("Introdu o optiune: ");
		scanf("%d", &cmd);
		if (cmd == 1) {
			compare = compara_participanti_scor_mai_mare;
			sorteaza_participanti(c, compare);

			printf(" Sortarea a avut loc cu succes!\n\n");
		}
		elif(cmd == 2) {
			compare = compara_participanti_scor_mai_mic;
			sorteaza_participanti(c, compare);
			printf(" Sortarea a avut loc cu succes!\n\n");
		}
		else printf(" Optiune invalida\n\n");
	}
	elif(cmd == 2) {
		printf("\nSortare participanti dupa nume\n");
		printf(" 1) Crescator\n");
		printf(" 2) Descrescator\n");
		printf("Introdu o optiune: ");
		scanf("%d", &cmd);
		if (cmd == 1) {
			compare = compara_participanti_alfabetic_crescator;
			sorteaza_participanti(c, compare);
			printf(" Sortarea a avut loc cu succes!\n\n");
		}
		elif(cmd == 2) {
			compare = compara_participanti_alfabetic_descrescator;
			sorteaza_participanti(c, compare);
			printf(" Sortarea a avut loc cu succes!\n\n");
		}
		else printf(" Optiune invalida\n\n");
	}
	else printf(" Optiune invalida\n\n");
}

void populeaza_concurs(vector_p* c) {
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

	adauga_participant(c, "Hamed", "Ali", note0);
	adauga_participant(c, "Ephesius", "Alvin Klas", note1);
	adauga_participant(c, "Saqui", "Karmen Leto", note2);
	adauga_participant(c, "Meaghan", "Noelia Kalea", note3);
	adauga_participant(c, "Elli", "Mirza", note4);
	adauga_participant(c, "Agneza", "Sophronius Suha", note5);
	adauga_participant(c, "Eckehard", "Sirius Gunda", note6);
	adauga_participant(c, "Zorro", "Amalija Anastas", note7);
	adauga_participant(c, "Shqipe", "Nicolas Xaver", note8);
	adauga_participant(c, "Drakon", "Brendan", note9);
}

void goodbyeUI() {
	printf("88        db        88%c%cYb 888888 Yb    dP 888888 8888b.  888888 88%c%cYb 888888   d8b\n", 0x22, 0x22, 0x22, 0x22);
	printf("88       dPYb       88__dP 88__    Yb  dP  88__    8I  Yb 88__   88__dP 88__     Y8P\n");
	printf("88.o    dP__Yb      88%cYb  88%c%c     YbdP   88%c%c    8I  dY 88%c%c   88%cYb  88%c%c     `%c'\n", 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22);
	printf("88ood8 dP%c%c%c%cYb     88  Yb 888888    YP    888888 8888Y%c  888888 88  Yb 888888   (8)\n", 0x22, 0x22, 0x22, 0x22, 0x22);
}

void run() {
	
	int cmd;
	vector_p c = initializeaza_vector(1);
	populeaza_concurs(&c);
	
	while (cmd = global_menuUI()) {
		system("cls");
		if (cmd == 1) {
			adauga_concurentUI(&c);
		}
		elif (cmd == 2) {
			modifica_concurentUI(c);
		}
		elif (cmd == 3) {
			sterge_concurentUI(c);
		}
		elif (cmd == 4) {
			filtrare_concurentiUI(c);
		}
		elif (cmd == 5) {
			sortare_concurentiUI(c);
		}
		elif (cmd == 6) {
			afisare_concurentiUI(c);
		}
		else {
			printf("Optiune invalida!\n\n");
		}
	}
	distruge_concurs(c);
	system("cls");
	goodbyeUI();
}
