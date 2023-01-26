#pragma once
#include "vector.h"
#include "tranzactie.h"

int validateIndex(PVector contbancar, int index);
void sortContbancar(PVector contbancar, int (*key)(PTranzactie), int (*cmp)(int,int), int reverse);

int key_zi(PTranzactie tranz);
int compare_zi(int a_zi, int b_zi);

int validareZi(int zi);
int validareSuma(double suma);
int validareTip(char *tip);
int validareDescriere(char *descriere);

PVector filterMaxSum(PVector contbancar, double sum);
PVector filterType(PVector contbancar, char* tip);
void distrugeCont(PVector);

void adaugaUndo(PVector undoList, PVector cont);
int doUndo(PVector* cont, PVector undoList);
void distrugeUndo(PVector undoList);