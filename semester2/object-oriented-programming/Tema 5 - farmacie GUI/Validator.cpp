#include "Exceptions.hpp"
#include "Validator.h"

void Validator::validateMedicineName(string name) {
	if (name.length() < 3 || name.length() > 18) {
		throw ValidationException{ "Length of the medicine's name is invalid! It should have between 3 and 18 characters!" };
	}
}
void Validator::validateMedicinePrice(double price) {
	if (price <= 0 || price > 10000) {
		throw ValidationException{ "Price of the medicine should be bigger than $0 and smaller or equal than $10.000!" };
	}
}
void Validator::validateMedicineProducer(string producer) {
	if (producer.length() < 4 || producer.length() > 23) {
		throw ValidationException{ "Length of the medicine's producer is invalid! It should have between 4 and 23 characters!" };
	}
}
void Validator::validateMedicineSubstance(string substance) {
	if (substance.length() < 5 || substance.length() > 38) {
		throw ValidationException{ "Length of the medicine's substance is invalid! It should have between 5 and 38 characters" };
	}
}
