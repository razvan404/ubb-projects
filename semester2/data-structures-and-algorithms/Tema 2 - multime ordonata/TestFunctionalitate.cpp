#include "TestFunctionalitate.h"
#include "Multime.h"
#include <assert.h>
#include <cstdio>

void testFunct() {
	Multime a;
	assert(a.adauga(5) == true);
	assert(a.adauga(1) == true);
	assert(a.adauga(10) == true);
	assert(a.adauga(7) == true);
	assert(a.adauga(1) == false);
	assert(a.adauga(10) == false);
	assert(a.adauga(-3) == true);
	// a = {5, 1, 10, 7, -3}
	Multime b;
	assert(b.adauga(1) == true);
	assert(b.adauga(10) == true);
	assert(b.adauga(7) == true);
	assert(b.adauga(12) == true);
	// b = {1, 10, 7, 12}
	assert(a.diferenta(b) == 3);
	assert(a.dim() == 2);
	assert(a.cauta(5) == true);
	assert(a.cauta(1) == false);
	assert(a.cauta(10) == false);
	assert(a.cauta(7) == false);
	assert(a.cauta(-3) == true);
}