#pragma once

typedef struct {
    int zi;
    double suma;
    char* tip;
    char* descriere;
} TTranzactie;

typedef TTranzactie* PTranzactie;

int getZi(PTranzactie);
double getSuma(PTranzactie);
char* getTip(PTranzactie);
char* getDescriere(PTranzactie);

PTranzactie createTranz(int new_zi, double new_suma, char* new_tip, char* new_descriere);
void destroyTranz(PTranzactie);
void modifyTranz(PTranzactie t, int new_zi, double new_suma, char* new_tip, char* new_descriere);
PTranzactie copyTranz(PTranzactie);
