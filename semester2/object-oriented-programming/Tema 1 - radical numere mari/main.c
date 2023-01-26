#pragma GCC optimize ("O3")
#pragma warning (disable: 4996)
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <crtdbg.h>
#define lmax 10000

typedef int* huge;

/*
* Se aloca dinamic pe heap un numar de tip 'huge'
* return - un numar 'huge' cu valoarea 0
*/
huge init_huge();

/*
* Se dezaloca de pe heap numarul de tip 'huge'
* h - huge number
* numarul o sa fie dezalocat din memorie
*/
void destroy_huge(huge h);
/*
* Ii atribuie unui numar mare valoarea unui string
* h - huge number, s - string
* h[0] lungimea numarului din s, h[1..n] valoarea inversa a numarului din s
*/
void atribValue(huge h, char* s);

/*
* Ii atribuie unui numar mare valoarea altui numar mare
* h, x - huge numbers
* h va avea valoarea lui x
*/
void atribHuge(huge h, huge x);

/*
* Afiseaza un numar mare
* h - huge number
* print on screen the number
*/
void afisHuge(huge h);

/*
* Compara 2 numere mari.
* h, x - huge numbers
* return -1 daca h < x, +1 daca h > x, 0 daca h == x
*/
short sgn(huge h, huge x);

/*
* Aduna 2 numere mari.
* a, b - huge numbers
* a va avea valoarea lui a + b
*/
void add(huge a, huge b);

/*
* Scade 2 numere mari
* a, b - huge numbers
* a va avea valoarea lui a - b
*/
void sub(huge a, huge b);

/*
* Face inmultirea dintre un vector si un scalar
* h - huge number, x - unsigned integer
* h va avea valoarea lui h * x
*/
void mul(huge h, unsigned int x);

/*
* Shifteaza vectorul cu un numar de pozitii la stanga
* h - huge number, Count - unsigned integer
* h va avea valoarea vectorului shiftat
*/
void shl(huge h, unsigned int Count);

/*
* Shifteaza vectorul cu un numar de pozitii la dreapta
* h - huge number, Count - unsigned integer
* h va avea valoarea vectorului shiftat
*/
void shr(huge h, unsigned int Count);

/*
* Face radicalul unui numar gigantic h
* h, ans - huge number
* ans <- sqrt(h)
*/
void sqrt_huge(huge h, huge ans);

/*
* Afiseaza un meniu cu optiunile aplicatiei
* return - optiunea data de utilizator daca este valida sau -1
*/
int globalMenu();

int main(int argc, char** argv) {
	char s[lmax], *real_s, *imag_s, new_s[lmax], *buffer;
	int prec;
	printf("Radacina patrata a unui numar real (cu o precizie data)\n");
	while (1) {
		int cmd = globalMenu();
		if (cmd == -1) {
			printf(" Optiune invalida, incearca din nou!\n\n");
		}
		else if (cmd == 0) {
			break;
		}
		else {
			printf(" Numarul: ");
			scanf("%s", s);

			printf(" Precizie: ");
			scanf("%d", &prec);
			size_t initial_value = strlen(s);
			real_s = strtok(s, ".");

			if (strlen(s) == initial_value) {
				for (int i = 0; i < prec; ++i) {
					strcat(s, "00");
				}
				huge real = init_huge();
				huge ans = init_huge();
				atribValue(real, s);
				sqrt_huge(real, ans);
				printf("Radicalul cu %d decimale: ", prec);
				for (int i = ans[0]; i > prec; --i) {
					printf("%d", ans[i]);
				}
				if (ans[0] <= prec) {
					printf("0");
				}
				printf(".");
				for (int i = prec; i > 0; --i) {
					printf("%d", ans[i]);
				}
				printf("\n\n");
				destroy_huge(real);
				destroy_huge(ans);
			}
			else {
				imag_s = strtok(NULL, ".");
				strcpy(new_s, real_s);
				if (strlen(imag_s) >= 2 * prec) {
					strncat(new_s, imag_s, 2 * prec);
				}
				else {
					strcat(new_s, imag_s);
					for (int i = strlen(imag_s); i < 2 * prec; ++i) {
						strcat(new_s, "0");
					}
				}
				huge real = init_huge();
				huge ans = init_huge();
				atribValue(real, new_s);
				sqrt_huge(real, ans);
				printf("Radicalul cu %d decimale: ", prec);
				for (int i = ans[0]; i > prec; --i) {
					printf("%d", ans[i]);
				}
				if (ans[0] <= prec) {
					printf("0");
				}
				printf(".");
				for (int i = prec; i > 0; --i) {
					printf("%d", ans[i]);
				}
				printf("\n\n");
				destroy_huge(real);
				destroy_huge(ans);
			}
		}
	}
	printf(" La revedere!\n");
	_CrtDumpMemoryLeaks();
	return 0;
}


huge init_huge() {
	huge init = malloc((2 * lmax + 3) * sizeof(int));
	if (init) {
		for (int i = 0; i < 2 * lmax + 3; ++i) {
			init[i] = 0;
		}
		return init;
	}
	exit(-1);
}

void destroy_huge(huge h) {
	free(h);
}

void atribValue(huge h, char* s) {
	h[0] = 0;
	for (int i = strlen(s) - 1; i > -1; --i) {
		++h[0];
		h[h[0]] = s[i] - '0';
	}
	while (h[0] && !h[h[0]]) h[0]--;
}

void atribHuge(huge h, huge x) {
	for (int i = 0; i <= x[0]; ++i) {
		h[i] = x[i];
	}
}

void afisHuge(huge h) {
	if (h[0] == 0) printf("0");
	for (int i = h[0]; i >= 1; --i) {
		printf("%d", h[i]);
	}
	printf("\n");
}

short sgn(huge h, huge x) {
	while (h[0] && !h[h[0]]) h[0]--;
	while (x[0] && !x[x[0]]) x[0]--;

	if (h[0] < x[0]) {
		return -1;
	}
	if (h[0] > x[0]) {
		return +1;
	}

	for (int i = h[0]; i > 0; --i) {
		if (h[i] < x[i]) {
			return -1;
		}
		if (h[i] > x[i]) {
			return +1;
		}
	}

	return 0;
}

void add(huge a, huge b) {
	if (b[0] > a[0]) {
		for (int i = a[0] + 1; i <= b[0]; ++i) {
			a[i] = 0;
			++a[0];
		}
	}
	else {
		for (int i = b[0] + 1; i <= a[0]; ++i) {
			b[i] = 0;
		}
	}
	bool transp = 0;
	for (int i = 1; i <= a[0]; ++i) {
		a[i] += b[i] + transp;
		transp = a[i] / 10;
		a[i] %= 10;
	}
	if (transp) {
		a[++a[0]] = transp;
	}
}

void sub(huge a, huge b) {
	bool transp = 0;
	for (int i = b[0] + 1; i <= a[0]; ++i) {
		b[i] = 0;
	}
	for (int i = 1; i <= a[0]; ++i) {
		a[i] -= b[i] + transp;
		if (a[i] < 0) transp = 1;
		else transp = 0;
		if (transp) a[i] += 10;
	}
	while (a[0] && !a[a[0]]) {
		--a[0];
	}
}

void mul(huge h, unsigned int x) {
	unsigned long transp = 0;
	for (int i = 1; i <= h[0]; ++i) {
		h[i] = h[i] * x + transp;
		transp = h[i] / 10;
		h[i] = h[i] % 10;
	}
	while (transp) {
		h[++h[0]] = transp % 10;
		transp /= 10;
	}
}

void shl(huge h, unsigned int Count) {
	for (int i = h[0]; i > 0; --i) {
		h[i + Count] = h[i];
	}
	for (int i = 1; i <= Count; ++i) {
		h[i] = 0;
	}
	h[0] += Count;
}

void shr(huge h, unsigned int Count) {
	for (int i = Count + 1; i <= h[0]; ++i) {
		h[i - Count] = h[i];
	}
	h[0] -= Count;
}

void sqrt_huge(huge h, huge ans) {
	if (h[0] & 1) {
		++h[0];
		h[h[0]] = 0;
	}
	huge transp = init_huge();
	huge curent = init_huge();
	huge pair = init_huge();
	huge zero = init_huge();
	atribValue(zero, "0");
	atribValue(transp, "0");
	atribValue(ans, "0");
	for (int i = h[0]; i > 0; i -= 2) {
		atribHuge(curent, ans);
		mul(curent, 2);
		mul(transp, 100);
		char s[3];
		s[0] = h[i] + '0';
		s[1] = h[i - 1] + '0';
		s[2] = '\0';
		huge pair = init_huge();
		huge aux = init_huge();
		atribValue(pair, s);
		add(transp, pair);
		shl(curent, 1);
		int next_value = 0;
		for (int i = 0; i <= 9; ++i) {
			atribHuge(aux, curent);
			aux[1] = i;
			mul(aux, i);
			if (sgn(aux, transp) == 1)
				break;
			next_value = i;
		}
		curent[1] = next_value;
		mul(curent, next_value);
		mul(ans, 10);
		if (ans[0] == 0 && next_value != 0) {
			ans[0] = 1;
		}
		ans[1] = next_value;
		sub(transp, curent);
		destroy_huge(pair);
		destroy_huge(aux);
	}
	destroy_huge(transp);
	destroy_huge(curent);
	destroy_huge(pair);
	destroy_huge(zero);
}

int globalMenu() {
	printf(" 1) Efectueaza radicalul\n");
	printf(" 0) Iesi din aplicatie\n");
	printf("Alege o optiune: ");
	char buffer[50];
	scanf("%s", buffer);
	if (strlen(buffer) > 1) return -1;
	if (buffer[0] < '0' || buffer[0] > '1') return -1;
	return buffer[0] - '0';
}
