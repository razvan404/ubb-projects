#pragma once
#include <string>

using std::string;

class Medicine {
private:
	string name;
	double price = 0;
	string producer;
	string substance;

public:
	// Medicine Class Default Constructor
	Medicine() noexcept {}
	// Medicine Class Constructor
	Medicine(string name, double price, string producer, string substance) :
		name{ name },
		price{ price },
		producer{ producer },
		substance{ substance } {}
	// Medicine Class Copy Constructor
	Medicine(const Medicine& medicine) :
		name{ medicine.name },
		price{ medicine.price },
		producer{ medicine.producer },
		substance{ medicine.substance } {}
	// Medicine Class Move Constructor
	Medicine(Medicine&& other) = default;
	// Medicine Class Copy Assignment Operators
	Medicine& operator=(const Medicine&) = default;
	// Medicine Class Move Assignment Operators
	Medicine& operator=(Medicine&& other) = default;
	// Medicine Class Destructor
	~Medicine() = default;

	// Medicine Class Comparation Operators
	bool operator==(const Medicine& other) const noexcept {
		return this->name == other.name && this->producer == other.producer;
	}
	bool operator!=(const Medicine& other) const noexcept {
		return this->name != other.name || this->producer != other.producer;
	}

	// Returns the name of the medicine
	string getName() const;
	// Returns the price of the medicine
	double getPrice() const noexcept;
	// Returns the producer of the medicine
	string getProducer() const;
	// Returns the active substance of the medicine
	string getSubstance() const;
};
