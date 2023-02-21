#include <crtdbg.h>
#include "user_interface.h"
#include "tests.h"

/*	1. Concurs de programare
  La concursul anual de programare, comitetul de evaluare inregistreaza intr-o lista scorul
obtinut de fiecare participant. Despre fiecare participant se inregistreaza urmatoarele
informatii: Nume, Prenume, Scor. Fiecare participant trebuie sa rezolve 10 probleme, maximul
de puncte pe fiecare problema este 10.

  Creati o aplicatie care permite comitetului de organizare sa:
a) Adauge participanti
b) Actualizare participant existent
c) Sterge participanti
d) Permite afisearea participantilor filtrat dupa o proprietate (cei care au un scor mai mic
   decat o valoare data, cei cu nume incepand cu o litera data, etc.)
e) Permite sortarea participantilor dupa nume sau dupa scor (crescator/descrescator)	*/

int main(int argc, char** argv) {
	test_all();
	run();
	_CrtDumpMemoryLeaks();
	return 0;
}
