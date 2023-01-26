#include <string>
#include "Medicine.h"

string Medicine::getName() const {
	return name;
}
double Medicine::getPrice() const noexcept {
	return price;
}
string Medicine::getProducer() const {
	return producer;
}
string Medicine::getSubstance() const {
	return substance;
}
