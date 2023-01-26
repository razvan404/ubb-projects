#pragma once
#include "tranzactie.h"
#include "vector.h"
#include <stdlib.h>
#include <limits.h>

#define BASE_VECTOR_CAPACITY 5
#define VECTOR_RESIZE_FACTOR 2

void distrugeVector(PVector cont) {
    /*
     * elimina din memorie bitii alocati pentru un vector(cont bancar)
     * cont este pointer la locatia unui vector(cont bancar)
     */
    free(cont->elemente);
    free(cont);
}

PVector creareVector() {
    /*
     * creeaza un vector dinamic(cod bancar)
     * returneaza pointerul la locatia memoriei alocate dinamic
     */
    PVector cont = malloc(sizeof(TVector));
    if (cont) {
        cont->lungime = 0;
        cont->capacitate = BASE_VECTOR_CAPACITY;
        cont->elemente = malloc(cont->capacitate * sizeof(TElem));
    }
    return cont;
}

void redim(PVector cont) {
    /*
     * modifica marimea blocului alocat dinamic din memorie, astfel incat vor avea loc noi elemente_temp
     * contbancar este pointer la locatia unui vector(cont bancar)
     */

    //salvare temporara de elemente_temp
    cont->capacitate *= VECTOR_RESIZE_FACTOR;
    TElem* elemente_noi = malloc(sizeof(TElem) * cont->capacitate);

    if (elemente_noi) {
        for (int i = 0; i < cont->lungime; i++) {
            elemente_noi[i] = getElemAt(cont, i);
        }
        free(cont->elemente);

        cont->elemente = elemente_noi;
        return;
    }
}

int getLen(PVector v) {
    return v->lungime;
}

TElem getElemAt(PVector v, int poz) {
    return v->elemente[poz];
}

void setElemAt(PVector v, int poz, TElem elem) {
    v->elemente[poz] = elem;
}

void adaugaElem(PVector cont, TElem tranz) {
    /*
     * Adauga o tranzactie la totalul de tranzactii.
     * (tranzactia originala este distrusa in acest proces, copia este in vector)
     * contbancar = pointer la vectorul in care se adaugaTranz
     * tranzactie = tranzactia ce trebuie adaugata
     */
    if(cont->lungime >= cont->capacitate)
        redim(cont);

    cont->elemente[cont->lungime] = tranz;
    cont->lungime++;
}

TElem stergeElem(PVector cont, int poz) {
    /*
     * Sterge o tranzactie la totalul de tranzactii.
     * contbancar = pointer la vectorul in care se stergeTranz
     * poz = pozitia elementului de pe care se sterge, poz incepe de la 1, nu de la 0!
     */
    int index = poz - 1, len = cont->lungime;

    TElem old = cont->elemente[index];
    for (int i = index; i < len - 1; i++)
        cont->elemente[i] = cont->elemente[i + 1];
    cont->lungime--;
    return old;
}
