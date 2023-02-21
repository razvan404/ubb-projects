#include "TestFunctionalitate.h"

void testFunctionalitate() {
	MD m;
	m.adauga(1, 100);
	m.adauga(2, 200);
	m.adauga(3, 300);
	m.adauga(1, 500);
	m.adauga(2, 600);
	m.adauga(4, 800);
	assert(m.dim() == 6);

	m.goleste();
	assert(m.vid());
	const auto& it = m.iterator();
	assert(it.valid() == false);
}