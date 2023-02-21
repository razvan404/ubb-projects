#pragma once
#include "tranzactie.h"

//gen vector dinamic
typedef void* TElem;

typedef struct{
    int lungime;
    int capacitate;
    TElem* elemente;
} TVector;

typedef TVector* PVector;

int getLen(PVector v);
TElem getElemAt(PVector v, int poz);
void setElemAt(PVector v, int poz, TElem elem);

PVector creareVector();
void adaugaElem(PVector, TElem);
TElem stergeElem(PVector, int);
void redim(PVector);
void distrugeVector(PVector);