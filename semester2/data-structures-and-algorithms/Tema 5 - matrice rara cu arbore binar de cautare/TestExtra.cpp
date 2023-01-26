#include "TestExtra.h"
#include "Matrice.h"
#include <cassert>

void testAllExtra() {
	Matrice m(4, 4);
	//adaug niste elemente
	m.modifica(1, 1, 5);
	m.modifica(0, 3, 4);
	m.modifica(1, 2, 5);
	m.modifica(3, 0, 9);
	m.modifica(3, 2, 10);
	assert(m.suma(2) == 15);
	assert(m.suma(0) == 9);
	m.modifica(3, 2, 2);
	assert(m.suma(2) == 7);
	
	try {
		m.suma(4);
		assert(false);
	}
	catch (...) {
		assert(true);
	}
}