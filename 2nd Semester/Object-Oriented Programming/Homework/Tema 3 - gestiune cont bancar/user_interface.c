#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <string.h>
#include "vector.h"
#include "tranzactie.h"
#include "service.h"

PTranzactie readTranzactie() {
    int zi;
    double suma;
    char tip[20], descriere[20], buffer[20];

    printf(" Ziua: ");
    if (scanf("%s", buffer) == 0)
    {
        printf("\nComanda invalida!\n");
        rewind(stdin);
        return NULL;
    }

    int i = 0;
    while (buffer[i] != '\0' && i < 19) {
        ++i;
    }
    buffer[i] = '\0';

    for (size_t i = 0; i < strlen(buffer); ++i) {
        if (buffer[i] < '0' || buffer[i] > '9') {
            printf("Trebuie introdus un numar!\n\n");
            return NULL;
        }
    }
    zi = atoi(buffer);

    if (validareZi(zi) == 0)
    {
        printf("Ziua trebuie sa fie intre 1 si 31!\n");
        return NULL;
    }

    printf(" Suma: ");
    rewind(stdin);
    if (scanf("%s", buffer) == 0)
    {
        printf("Comanda invalida!\n");
        rewind(stdin);
        return NULL;
    }

    for (size_t i = 0; i < strlen(buffer); ++i) {
        if ((buffer[i] < '0' || buffer[i] > '9') && buffer[i] != '.') {
            printf("Trebuie introdus un numar!\n");
            return NULL;
        }
    }

    suma = atof(buffer);

    if (validareSuma(suma) == 0)
    {
        printf("\nSuma trebuie sa fie pozitiva!\n");
        return NULL;
    }

    printf(" Tipul: ");

    if (scanf("%s", tip) == 0)
    {
        printf("Comanda invalida!\n");
        rewind(stdin);
        return NULL;
    }

    if (validareTip(tip) == 0)
    {
        printf("Tipul trebuie sa fie intrare sau iesire!\n");
        return NULL;
    }

    printf(" Descriere: ");
    rewind(stdin);
    fgets(descriere, 20, stdin);
    if (validareDescriere(descriere) == 0)
    {
        printf("Descrierea trebuie sa aiba maxim 12 caractere!\n");
        return NULL;
    }
    if (descriere[strlen(descriere) - 1] == '\n') {
        descriere[strlen(descriere) - 1] = '\0';
    }
    rewind(stdin);

    return createTranz(zi, suma, tip, descriere);
}

void adaugareTranzactie(PVector contbancar, PVector listaUndo)
{
    PTranzactie tranz = readTranzactie();
    if (tranz == NULL)
        return;

    adaugaUndo(listaUndo, contbancar);
    adaugaElem(contbancar, tranz);
    printf("Tranzactie adaugata cu succes\n\n");
}

void afisareTranzactie(PTranzactie tranzactie)
{
    printf("Ziua: %d   |   ", ((PTranzactie)tranzactie)->zi);
    printf("Suma: %g   |   ", ((PTranzactie)tranzactie)->suma);
    printf("Tip: %s   |   ", ((PTranzactie)tranzactie)->tip);
    printf("Descriere: %s\n", ((PTranzactie)tranzactie)->descriere);
}

int readcommand()
{
    printf("Banca\n");
    printf(" 1) adauga tranzactie\n");
    printf(" 2) modificare tranzactie\n"); 
    printf(" 3) stergere tranzactie\n");
    printf(" 4) afisare tranzactii\n");
    printf(" 5) filtrare tranzactii cu suma maxima data\n");
    printf(" 6) filtrare tranzactii dupa un anumit tip\n");
    printf(" 7) sortare tranzactii dupa zi\n");
    printf(" 8) undo\n");
    printf(" 0) iesire\n");
    int com;
    printf("Alege comanda: ");
    if (scanf("%d", &com) == 0) {
        return 63;
    }
    return com;
}

void afisareAllTranz(PVector contbancar)
{
    printf("\n");
    for (int i = 0; i < getLen(contbancar); i++)
    {
        printf("  %d |\t", i + 1);
        afisareTranzactie(getElemAt(contbancar, i));
    }
    printf("\n");
}

void vizualizareMaxSum(PVector contbancar)
{
    double suma;
    printf("Suma maxima dorita: ");
    if (scanf("%lf", &suma) == 0) {
        printf("\nComanda invalida!\n");
        rewind(stdin);
        return;
    }
    PVector contFiltrat = filterMaxSum(contbancar, suma);
    if (getLen(contFiltrat) == 0) {
        printf("Nu exista tranzactii cu suma maxima data!\n\n");
    }
    else {
        afisareAllTranz(contFiltrat);
    }
    distrugeVector(contFiltrat);
}

void vizualizareTip(PVector contbancar) {
    char tip[20];
    printf("Tipul dorit: ");
    if (scanf("%s", tip) == 0) {
        printf("\nComanda invalida!\n");
        rewind(stdin);
        return;
    }
    if (validareTip(tip) == 0) {
        printf("Tip invalid, poate sa fie doar intrare sau iesire!\n\n");
        return;
    }

    PVector contFiltrat = filterType(contbancar, tip);
    if (getLen(contFiltrat) == 0) {
        printf("Nu exista tranzactii cu suma maxima data!\n\n");
    }
    else {
        afisareAllTranz(contFiltrat);
    }
    distrugeVector(contFiltrat);
}

int readTranzPoz()
{
    int poz;
    printf("Introduceti pozitia tranzactiei: ");
    if (scanf("%d", &poz) == 0)
    {
        printf("Comanda invalida!\n");
        rewind(stdin);
        return 0;
    }

    return poz;
}

void modificare(PVector contbancar, PVector listaUndo) {
    afisareAllTranz(contbancar);

    int poz = readTranzPoz();
    int index = poz - 1;
    if (validateIndex(contbancar, index) == 1)
    {
        printf("Pozitia este invalida!\n");
        return;
    }

    PTranzactie tranz = readTranzactie();
    if (tranz == NULL)
        return;

    adaugaUndo(listaUndo, contbancar);
    modifyTranz(getElemAt(contbancar, index), getZi(tranz), getSuma(tranz), getTip(tranz), getDescriere(tranz));
    destroyTranz(tranz);
}

void stergere(PVector contbancar, PVector listaUndo)
{
    afisareAllTranz(contbancar);

    int poz = readTranzPoz();
    int index = poz - 1;
    if (validateIndex(contbancar, index) == 1)
    {
        printf("Pozitia este invalida!\n");
        return;
    }

    //pozitia incepe de la 1, indicele de la 0
    adaugaUndo(listaUndo, contbancar);
    destroyTranz(stergeElem(contbancar, poz));
}

void sortare(PVector contbancar, PVector listaUndo) {
    int ordonare;
    printf("Alegeti modul de sortare:\n 1) descrescator\n 2) crescator\nAlegeti comanda: ");
    if (scanf("%d", &ordonare) == 0) {
        printf("Optiune invalida!\n\n");
        rewind(stdin);
        return;
    }

    if (ordonare <= 0 || ordonare >= 3)
    {
        printf("Comanda invalida!");
        return;
    }

    if (ordonare == 1)
    {
        adaugaUndo(listaUndo, contbancar);
        printf("Sortare descrescatoare!\n");
        sortContbancar(contbancar, key_zi, compare_zi, 1);
    }
    if (ordonare == 2)
    {
        adaugaUndo(listaUndo, contbancar);
        printf("Sortare crescatoare!\n");
        sortContbancar(contbancar, key_zi, compare_zi, 0);
    }

    afisareAllTranz(contbancar);
}

void undo(PVector* contBancar, PVector undoList) {
    if (!doUndo(contBancar, undoList)) {
        printf("Nu se poate face undo, deoarece nu a fost efectuate destule operatii valide!\n\n");
        return;
    }
    afisareAllTranz(*contBancar);
    printf("Operatiunea de undo a fost facuta cu succes!\n\n");
}

void preset(PVector cont) {
    adaugaElem(cont, createTranz(1, 95.5, "intrare", "descriere1"));
    adaugaElem(cont, createTranz(9, 74.4, "intrare", "descriere2"));
    adaugaElem(cont, createTranz(7, 19.8, "iesire", "descriere3"));
    adaugaElem(cont, createTranz(4, 33.6, "intrare", "descriere4"));
    adaugaElem(cont, createTranz(3, 51.0, "iesire", "descriere5"));
    adaugaElem(cont, createTranz(5, 80.1, "iesire", "descriere6"));
    adaugaElem(cont, createTranz(10, 75.3, "iesire", "descriere7"));
    adaugaElem(cont, createTranz(24, 46.9, "intrare", "descriere8"));
    adaugaElem(cont, createTranz(17, 38.2, "iesire", "descriere9"));
    adaugaElem(cont, createTranz(28, 82.5, "iesire", "descriere10"));
    adaugaElem(cont, createTranz(30, 17.6, "intrare", "descriere11"));
}

void run()
{
    PVector contBancar = creareVector();
    PVector listaUndo = creareVector();
    preset(contBancar);
    int optiune;
    while (1) {
        optiune = readcommand();
        system("cls");

        if (optiune == 1) {
            adaugareTranzactie(contBancar, listaUndo);
        }
        else if (optiune == 2) {
            modificare(contBancar, listaUndo);
        }
        else if (optiune == 3) {
            stergere(contBancar, listaUndo);
        }
        else if (optiune == 4) {
            afisareAllTranz(contBancar);
        }
        else if (optiune == 5) {
            vizualizareMaxSum(contBancar);
        }
        else if (optiune == 6) {
            vizualizareTip(contBancar);
        }
        else if (optiune == 7) {
            sortare(contBancar, listaUndo);
        }
        else if (optiune == 8) {
            undo(&contBancar, listaUndo);
        }

        else if (optiune == 0) {
            distrugeCont(contBancar);
            distrugeUndo(listaUndo);
            break;
        }
        else {
            printf("Comanda nu exista!\n");
        }
    }
}
