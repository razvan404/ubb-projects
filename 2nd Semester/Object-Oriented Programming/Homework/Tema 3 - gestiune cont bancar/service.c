#pragma once
#include "service.h"
#include "vector.h"
#include "assert.h"
#include <string.h>

int validateIndex(PVector contbancar, int index) {
    /*
     * verifica daca un index dat poate face parte dintr-un vector(contbancar) dat
     * contbancar este pointer la locatia unui vector(cont bancar)
     * index = int, indexul verificat apartinerii vectorului
     * returneaza 1 pt invalid, 0 pt valid
     */
    if(index < 0 || index >= getLen(contbancar))
        return 1;   //nu e bun
    return 0;
}

void sortContbancar(PVector contbancar, int (*key)(PTranzactie), int (*cmp)(int,int), int reverse) {
    /*
     * sorteaza un vector(contbancar) folosind o functie cheie si o functie de comparare
     * contbancar este pointer la locatia unui vector(cont bancar)
     * key = pointer la o functie care ia ca parametru un element(tranzactie) si returneaza o valoare int
     * cmp = pointer la o functie care ia ca parametri doi int, cmp trebuie sa returneze 0-nesortat, alt int-sortat
     * reverse = int 1 sau 0 pentru descrescator / crescator
     */
    PTranzactie aux;

    for (int i = 0; i < getLen(contbancar); i++) {
        for (int j = i + 1; j < getLen(contbancar); j++) {
            if(cmp(key(getElemAt(contbancar, i)), key(getElemAt(contbancar, j))) != reverse) {
                aux = getElemAt(contbancar, i);
                setElemAt(contbancar, i, getElemAt(contbancar, j));
                setElemAt(contbancar, j, aux);
            }
        }
    }
}

int key_zi(PTranzactie tranz) {
    /*
     * functie cheie pt functionalitatea sortarii dupa zile
     * tranz este un element(tranzactie)
     */
    return tranz->zi;
}

int compare_zi(int a_zi, int b_zi)
{
    /*
     * functie compare folosita ca si criteriu de sortare pt functionalitatea sortarii dupa zile
     * a_zi este ziua primului element(tranzactie)
     * a_zi este ziua celui de-al doilea element(tranzactie)
     */
    return a_zi >= b_zi;
}

int validareZi(int zi)
{
    /*
     * returneaza validitatea zilei
     * intre 1 si 31 returneaza 1, altfel 0
     */
    if(zi <= 0 || zi >= 32)
        return 0;
    return 1;
}

int validareSuma(double suma)
{
    /*
     * returneaza validitatea sumei
     * pentru negative returneaza 0, altfel 1
     */
    if(suma <= 0)
        return 0;
    return 1;
}

int validareTip(char* tip)
{
    /*
     * returneaza validitatea tipului
     * pentru tip = intrare/iesire returneaza 1, altfel 0
     */

    if((strcmp(tip, "intrare") != 0) && (strcmp(tip, "iesire") != 0))
        return 0;
    return 1;
}

int validareDescriere(char* descriere)
{
    /*
     * returneaza validitatea descrierii
     * trebuie sa contina maxim 12 caractere
     */
    if(strlen(descriere) > 12)
        return 0;
    return 1;
}

PVector filterMaxSum(PVector contbancar, double sum) {
    PVector contFiltrat = creareVector();
    for (int i = 0; i < getLen(contbancar); i++)
        if (sum >= getSuma(getElemAt(contbancar, i))) {
            adaugaElem(contFiltrat, getElemAt(contbancar, i));
        }
    return contFiltrat;
}

PVector filterType(PVector contbancar, char* tip) {
    PVector contFiltrat = creareVector();
    for (int i = 0; i < getLen(contbancar); i++)
        if (strcmp(getTip(getElemAt(contbancar, i)), tip) == 0) {
            adaugaElem(contFiltrat, getElemAt(contbancar, i));
        }
    return contFiltrat;
}

void distrugeCont(PVector cont) {
    for (int i = 0; i < getLen(cont); ++i) {
        destroyTranz(getElemAt(cont, i));
    }
    distrugeVector(cont);
}

void adaugaUndo(PVector undoList, PVector cont) {
    PVector contNou = creareVector();
    for (int i = 0; i < cont->lungime; ++i) {
        PTranzactie elem = copyTranz(getElemAt(cont, i));
        adaugaElem(contNou, elem);
    }
    adaugaElem(undoList, contNou);
}

int doUndo(PVector *cont, PVector undoList) {
    if (getLen(undoList) == 0) {
        return 0;
    }
    distrugeCont(*cont);
    *cont = stergeElem(undoList, getLen(undoList));
    return 1;
}

void distrugeUndo(PVector undoList) {
    for (int i = 0; i < getLen(undoList); ++i) {
        distrugeCont(getElemAt(undoList, i));
    }
    distrugeVector(undoList);
}
