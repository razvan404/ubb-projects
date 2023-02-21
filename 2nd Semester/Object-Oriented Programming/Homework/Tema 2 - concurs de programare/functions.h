#pragma once

#define elif else if 

/*
* Aproximeaza un numar real la cel mai apropiat intreg
* input - numar real pozitiv
* return - aproximarea la cel mai apropiat intreg
*/
long aprox(double);

/*
* Corecteaza un nume (prima litera mare si restul mici)
* input - sir de caractere
* return - un sir de caractere corect
*/
char* autocorect(char*);

/*
* Transforma un sir de caractere intr-un numar
* input - sir de caractere
* return - numarul corespunzator
*/
int string_to_number(char*);

/*
* Ne spune care participant are scorul mai mare
* input - 2 participanti
* return - 1 daca primul are scor mai mare sau 0 in caz contrar
*/
int compara_participanti_scor_mai_mare(participant_p, participant_p);

/*
* Ne spune care participant are scorul mai mic
* input - 2 participanti
* return - 1 daca primul are scor mai mic sau 0 in caz contrar
*/
int compara_participanti_scor_mai_mic(participant_p, participant_p);

/*
* Ne spune care participant este primul in ordine alfabetica
* input - 2 participanti
* return - 1 daca primul este mai mare alfabetic sau 0 in caz contrar
*/
int compara_participanti_alfabetic_crescator(participant_p, participant_p);

/*
* Ne spune care participant este al doilea in ordine alfabetica
* input - 2 participanti
* return - 1 daca primul este mai mic alfabetic sau 0 in caz contrar
*/
int compara_participanti_alfabetic_descrescator(participant_p, participant_p);