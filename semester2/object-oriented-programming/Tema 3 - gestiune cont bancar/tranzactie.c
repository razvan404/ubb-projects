#pragma once
#pragma warning(disable: 4996)
#include "tranzactie.h"
#include "string.h"
#include "stdlib.h"
#include "assert.h"

PTranzactie createTranz(int new_zi, double new_suma, char* new_tip, char* new_descriere) {
    /*
     * creeaza un element Tranzactie cu valorile specificate.
     * new_zi este ziua
     * new_suma este suma
     * new_tip este pointer la un sir de caractere
     * new_descriere este pointer la un sir de caractere
     * returneaza un element Tranzactie
     */
    PTranzactie tr = malloc(sizeof(TTranzactie));
    if (tr) {
        tr->zi = new_zi;
        tr->suma = new_suma;

        int len = strlen(new_tip) + 1;
        tr->tip = (char*)malloc(len * sizeof(char));
        len = strlen(new_descriere) + 1;
        tr->descriere = (char*)malloc(len * sizeof(char));
        
        if (tr->tip && tr->descriere) {
            strcpy(tr->tip, new_tip);

            len = strlen(new_descriere) + 1;
            strcpy(tr->descriere, new_descriere);

            return tr;
        }
    }
}

int getZi(PTranzactie tranz) {
    return tranz->zi;
}

double getSuma(PTranzactie tranz) {
    return tranz->suma;
}

char* getTip(PTranzactie tranz) {
    return tranz->tip;
}

char* getDescriere(PTranzactie tranz) {
    return tranz->descriere;
}

void destroyTranz(PTranzactie t) {
    /*
     * elimina din memorie bitii alocati dinamic pt un element tranzactie
     * t este pointer la un element tranzactie
     */
    free(t->tip);
    free(t->descriere);
    free(t);
}

void modifyTranz(PTranzactie t, int new_zi, double new_suma, char* new_tip, char* new_descriere) {
    /*
     * modifica un element Tranzactie cu valorile specificate.
     * new_zi este noua ziua
     * new_suma este noua suma
     * new_tip este pointer la un nou sir de caractere
     * new_descriere este pointer la un nou sir de caractere
     */
    t->zi = new_zi;
    t->suma = new_suma;
    free(t->tip);
    free(t->descriere);

    int len = strlen(new_tip) + 1;
    t->tip = malloc(len * sizeof(char));
    len = strlen(new_descriere) + 1;
    t->descriere = malloc(len * sizeof(char));

    if (t->tip && t->descriere) {
        strcpy(t->tip, new_tip);
        strcpy(t->descriere, new_descriere);
        return;
    }
}

PTranzactie copyTranz(PTranzactie source) {
    /*
     * Copiaza continutul unei tranzactii la o alta tranzactie
     * dest = tranzactia in care se copiaza continutul
     * source = tranzacia de unde se copiaza
     */
    int len = strlen(source->tip) + 1;
    char* tip = malloc(len * sizeof(char));
    len = strlen(source->descriere) + 1;
    char* descriere = malloc(len * sizeof(char));

    if (tip && descriere) {
        strcpy(tip, source->tip);
        strcpy(descriere, source->descriere);
        PTranzactie dest = createTranz(source->zi, source->suma, tip, descriere);
        free(tip);
        free(descriere);
        return dest;
    }
}
