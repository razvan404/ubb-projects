#pragma once
#pragma warning (disable: 26455) // Default constructor should not throw. Exception constructor will throw.

#include <string>

using std::string;

class PharmacyException {
private:
	string errorMessage;
public:
	PharmacyException(string what) : errorMessage{ what } {}
	string what() const {
		return errorMessage;
	}
};

class IndexException {
public:
	IndexException() {
		throw PharmacyException{ "Invalid position!" };
	}
};

class InexistentMedicineException {
	InexistentMedicineException() {
		throw PharmacyException{ "There is no medicine with the given name and the given producer!" };
	}
};

class ExistentMedicineException {
public:
	ExistentMedicineException() {
		throw PharmacyException{ "There is already a medicine with the same name and the same producer!" };
	}
};

class UndoException {
public:
	UndoException() {
		throw PharmacyException{ "Can't do undo because the medicine list is empty!" };
	}
};

class ValidationException {
public:
	ValidationException(string what) {
		throw PharmacyException{ what };
	}
};

class InvalidInput {
public:
	InvalidInput(string what) {
		throw PharmacyException{ what };
	}
};

class OtherException {
public:
	OtherException(string what) {
		throw PharmacyException{ what };
	}
};
