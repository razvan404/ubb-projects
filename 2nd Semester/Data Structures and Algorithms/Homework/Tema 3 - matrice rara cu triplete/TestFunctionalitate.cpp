#include "TestFunctionalitate.h"
#include "Matrice.h"
#include <assert.h>

void testFunctionalitate() {
	Matrice m(4, 4);
	assert(m.nrLinii() == 4);
	assert(m.nrColoane() == 4);
	assert(m.sumaDiagonalaPrincipala() == 0);
	//adaug niste elemente
	m.modifica(1, 1, 5);
	m.modifica(2, 2, 7);
	m.modifica(3, 4, 8);
	m.modifica(0, 1, 4);
	assert(m.sumaDiagonalaPrincipala() == 12);
	m.modifica(1, 1, 0);
	assert(m.element(1, 1) == NULL_TELEMENT);
	assert(m.sumaDiagonalaPrincipala() == 7);
}