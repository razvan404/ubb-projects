#pragma once
#include <vector>
#include <fstream>
#include <random>
#include "Medicine.h"
#include "UserInterfaceTools.hpp"

using std::vector;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
using std::ofstream;

class MedicineListRepository {
private:
	vector<Medicine> list;

public:
	/// Default Medicine List Repository Class Constructor
	MedicineListRepository() = default;
	/// Medicine List Repository Class Constructor
	MedicineListRepository(vector<Medicine>& list) : list{ list } {}

	/// Returns the size of the repository
	unsigned getLength() const noexcept;
	/// Returns the medicine to a given position, if the position is invalid an exception is thrown
	const Medicine& getMedicineAt(unsigned i) const;
	/// Returns the list of medicines
	const vector<Medicine>& getMedicineList() const noexcept;

	/// Adds a new medicine to the repository
	void addMedicine(const Medicine& medicine);
	/// Adds a new medicine to the repository to a certain position
	void addMedicine(const Medicine& medicine, unsigned i);
	/// Removes a medicine from a given position, if the position is invalid an exception is thrown
	void deleteMedicine(unsigned i);
	/// Modifies a medicine from a given position, if the position is invalid an exception is thrown
	void updateMedicine(const Medicine& medicine, unsigned i);
	/// Returns the position of the medicine or the length if it doesn't exists in the repository
	unsigned findMedicine(const Medicine& medicine);
};



class MedicineRecipeRepository {
private:
	vector<Medicine> recipe;
	double totalSum = 0;

public:
	/// Default Medicine Recipe Repository Class Constructor
	MedicineRecipeRepository() = default;
	/// Medicine Recipe Repository Class Constructor
	MedicineRecipeRepository(vector<Medicine>& recipe) : recipe{ recipe } {}
	/// Returns the size of the recipe
	unsigned getLength() const noexcept;
	/// Returns the total sum of the medicines
	double getSum() const noexcept;
	/// Returns the recipe of medicines
	const vector<Medicine>& getMedicineRecipe() const noexcept;

	/// Adds a new medicine to the recipe
	void addMedicine(const Medicine& medicine);
	/// Removes all the medicines from the recipe
	void resetRecipe() noexcept;
	/// Generates random medicines from a list of medicines
	void generateMedicines(const vector<Medicine>& medicineList, unsigned numberOfMedicines);
	/// Exports the recipe to a certain file
	void exportRecipe(string file);
};
