#include "IteratorMD.h"
#include "MD.h"

using namespace std;

void IteratorMD::deplasare() {
	/// Complexitate timp: Θ(1)
	while ((curentTD < md.m) && md.e[curentTD].first == NIL)
		curentTD++;
}

IteratorMD::IteratorMD(const MD& _md): md(_md) {
	/// Complexitate timp: Θ(1)
	curentTD = 0;
	deplasare();
	curentVECT = 0;
}

TElem IteratorMD::element() const{
	/// Complexitate timp: Θ(1)
	return { md.e[curentTD].first, md.e[curentTD].second.at(curentVECT) };
}

bool IteratorMD::valid() const {
	/// Complexitate timp: Θ(1)
	return curentTD < md.m;
}

void IteratorMD::urmator() {
	/// Complexitate timp: Θ(1)
	if (curentVECT + 1 < md.e[curentTD].second.size()) {
		curentVECT++;
		return;
	}
	curentTD++;
	deplasare();
	curentVECT = 0;
}

void IteratorMD::prim() {
	/// Complexitate timp: Θ(1)
	curentTD = 0;
	deplasare();
	curentVECT = 0;
}

