#include <assert.h>
#include <stdlib.h>
#include "tests.h"
#include "tranzactie.h"
#include "vector.h"
#include "service.h"
#include "user_interface.h"
#define BASE_VECTOR_CAPACITY 5
#define VECTOR_RESIZE_FACTOR 2

void testCreate() {
    PTranzactie tranz = createTranz(10, 20.5, "intrare", "salariu");
    assert(getZi(tranz) == 10);
    assert(getSuma(tranz) == 20.5);
    assert(strcmp(getTip(tranz), "intrare") == 0);
    assert(strcmp(getDescriere(tranz), "salariu") == 0);
    destroyTranz(tranz);
}

void testModify() {
    PTranzactie tranz = createTranz(10000, 200000.5, "iesire", "gaz");
    modifyTranz(tranz, 10, 20.5, "intrare", "salariu");
    assert(getZi(tranz) == 10);
    assert(getSuma(tranz) == 20.5);
    assert(strcmp(getTip(tranz), "intrare") == 0);
    assert(strcmp(getDescriere(tranz), "salariu") == 0);

    destroyTranz(tranz);
}

void testCopyTranz() {
    PTranzactie tranz = createTranz(10, 20.5, "intrare", "salariu");
    PTranzactie t2 = copyTranz(tranz);
    assert(getZi(tranz) == 10);
    assert(getSuma(tranz) == 20.5);
    assert(strcmp(getTip(tranz), "intrare") == 0);
    assert(strcmp(getDescriere(tranz), "salariu") == 0);

    destroyTranz(tranz);
    destroyTranz(t2);
}

void testCrearecont() {
    PVector cont = creareVector();
    assert(cont->lungime == 0);
    assert(cont->capacitate == BASE_VECTOR_CAPACITY);
    distrugeVector(cont);
}

void testAdauga() {
    //adaugaTranz elemente, dar fara redimensionare
    PVector cont = creareVector();
    PTranzactie* tranz = malloc(BASE_VECTOR_CAPACITY * sizeof(PTranzactie));
    PTranzactie* test = malloc(BASE_VECTOR_CAPACITY * sizeof(PTranzactie));
    int val_verificare;

    if (!tranz || !test) exit(-1);

    for (int i = 0; i < BASE_VECTOR_CAPACITY; i++) {
        val_verificare = (i + 1) * 10;
        tranz[i] = createTranz(val_verificare, 20.5, "intrare", "bmw");
        test[i] = createTranz(val_verificare, 20.5, "intrare", "bmw");
        adaugaElem(cont, tranz[i]);
    }

    for (int i = 0; i < BASE_VECTOR_CAPACITY; i++) {
        assert(((PTranzactie)cont->elemente[i])->zi == ((PTranzactie)test[i])->zi);
        destroyTranz((PTranzactie)test[i]);
    }

    assert(cont->lungime == BASE_VECTOR_CAPACITY);
    assert(cont->capacitate == BASE_VECTOR_CAPACITY);

    free(tranz);
    free(test);
    distrugeCont(cont);
}

void testRedimensionare()
{
    PVector cont = creareVector();

    const int redim_capacity = BASE_VECTOR_CAPACITY + 1;
    PTranzactie* tranz = malloc((BASE_VECTOR_CAPACITY + 1) * sizeof(PTranzactie));
    int val;

    if (!tranz) exit(-1);

    //ziua este din 10 in 10
    for (int i = 0; i < redim_capacity; i++) {
        val = (i + 1) * 10;
        tranz[i] = createTranz(val, 20.5, "intrare", "bmw");
        adaugaElem(cont, tranz[i]);
    }

    assert(cont->lungime == redim_capacity);
    assert(cont->capacitate == BASE_VECTOR_CAPACITY * VECTOR_RESIZE_FACTOR);
    assert(((PTranzactie)cont->elemente[redim_capacity - 1])->zi == redim_capacity * 10);

    free(tranz);
    distrugeCont(cont);
}

void testSterge() {
    PVector cont = creareVector();
    PTranzactie t;
    int val_verificare;

    for (int i = 0; i < BASE_VECTOR_CAPACITY; i++) {
        val_verificare = (i + 1) * 10;
        t = createTranz(val_verificare, 20.5, "intrare", "bmw");
        adaugaElem(cont, t);
    }

    destroyTranz(stergeElem(cont, 1));

    for (int i = 0; i < BASE_VECTOR_CAPACITY - 1; i++) {
        assert(((PTranzactie)cont->elemente[i])->zi == (i + 2) * 10);
    }

    distrugeCont(cont);
}


void testSortZile() {
    PVector cont = creareVector();
    PTranzactie t;
    int val_verificare;

    for (int i = 0; i < 5; i++) {
        val_verificare = (i + 1) * 10;
        t = createTranz(val_verificare, 20.5, "intrare", "bmw");
        adaugaElem(cont, t);
    }

    assert(((PTranzactie)cont->elemente[0])->zi == 10);

    sortContbancar(cont, key_zi, compare_zi, 1);

    assert(((PTranzactie)cont->elemente[0])->zi == 50);
    assert(((PTranzactie)cont->elemente[1])->zi == 40);
    assert(((PTranzactie)cont->elemente[2])->zi == 30);
    assert(((PTranzactie)cont->elemente[3])->zi == 20);
    assert(((PTranzactie)cont->elemente[4])->zi == 10);

    distrugeCont(cont);
}

void testValidari()
{
    PVector cont = creareVector();
    assert(validateIndex(cont, 0) == 1);

    PTranzactie tranz = createTranz(10, 20.5, "intrare", "bmw");
    adaugaElem(cont, tranz);

    assert(validateIndex(cont, 2) == 1);
    assert(validateIndex(cont, 1) == 1);

    //singurul element are indexul 0
    assert(validateIndex(cont, 0) == 0);

    assert(validareZi(10) == 1);
    assert(validareZi(32) == 0);
    assert(validareZi(0) == 0);

    assert(validareSuma(150.509) == 1);
    assert(validareSuma(-5) == 0);

    assert(validareTip("intrare") == 1);
    assert(validareTip("iesire") == 1);
    assert(validareTip("mancare") == 0);

    assert(validareDescriere("mancare") == 1);
    assert(validareDescriere("salvare") == 1);
    assert(validareDescriere("ornitoring domestic") == 0);

    distrugeCont(cont);
}

void testFiltrari() {
    PVector cont = creareVector();
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

    PVector filtrareSum = filterMaxSum(cont, 35);
    assert(getLen(filtrareSum) == 3);
    assert(getSuma(getElemAt(filtrareSum, 0)) == 19.8);
    assert(getSuma(getElemAt(filtrareSum, 1)) == 33.6);
    assert(getSuma(getElemAt(filtrareSum, 2)) == 17.6);

    PVector filtrareTip = filterType(cont, "intrare");
    assert(getLen(filtrareTip) == 5);
    assert(getZi(getElemAt(filtrareTip, 0)) == 1);
    assert(getZi(getElemAt(filtrareTip, 1)) == 9);
    assert(getZi(getElemAt(filtrareTip, 2)) == 4);
    assert(getZi(getElemAt(filtrareTip, 3)) == 24);
    assert(getZi(getElemAt(filtrareTip, 4)) == 30);

    distrugeVector(filtrareSum);
    distrugeVector(filtrareTip);
    distrugeCont(cont);
}

void testUndo() {
    PVector cont = creareVector();
    PVector undoList = creareVector();
    adaugaUndo(undoList, cont);
    adaugaElem(cont, createTranz(1, 95.5, "intrare", "descriere1"));
    adaugaUndo(undoList, cont);
    adaugaElem(cont, createTranz(9, 74.4, "intrare", "descriere2"));
    adaugaUndo(undoList, cont);
    adaugaElem(cont, createTranz(7, 19.8, "iesire", "descriere3"));
    adaugaUndo(undoList, cont);
    adaugaElem(cont, createTranz(4, 33.6, "intrare", "descriere4"));
    adaugaUndo(undoList, cont);
    adaugaElem(cont, createTranz(3, 51.0, "iesire", "descriere5"));
    assert(doUndo(&cont, undoList) == 1);
    assert(doUndo(&cont, undoList) == 1);
    assert(getLen(cont) == 3);
    assert(getLen(undoList) == 3);
    assert(doUndo(&cont, undoList) == 1);
    assert(doUndo(&cont, undoList) == 1);
    assert(doUndo(&cont, undoList) == 1);
    assert(doUndo(&cont, undoList) == 0);
    assert(doUndo(&cont, undoList) == 0);
    adaugaUndo(undoList, cont);
    adaugaElem(cont, createTranz(1, 95.5, "intrare", "descriere1"));
    adaugaUndo(undoList, cont);
    adaugaElem(cont, createTranz(9, 74.4, "intrare", "descriere2"));

    distrugeCont(cont);
    distrugeUndo(undoList);
}


void testAll()
{
    //Element
    testCreate();
    testModify();
    testCopyTranz();
    //vector
    testCrearecont();
    testAdauga();

    testRedimensionare();
    testSterge();

    testSortZile();
    //testValidari();
    testFiltrari();
    //testUndo();
}
