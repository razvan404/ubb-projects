#pragma once
#include <string>
#include <algorithm>
#include <unordered_map>

#include "MedicineRepository.h"
#include "Undo.h"

using std::unique_ptr;
using std::unordered_map;
using std::copy_if;
using std::distance;
using std::make_unique;

class PharmacyService {
private:
	MedicineListRepository& medicineListRepository;
	MedicineRecipeRepository& medicineRecipeRepository;
	vector<unique_ptr<UndoAction>> undoList;

public:
	/// Service Class Constructor
	PharmacyService(MedicineListRepository& medicineListRepository, MedicineRecipeRepository& medicineRecipeRepository) noexcept :
		medicineListRepository{ medicineListRepository },
		medicineRecipeRepository{ medicineRecipeRepository } {}
	/// Service Class Destructor
	~PharmacyService() = default;

	/// Adds a medicine to the medicine list repository
	void addMedicine(string name, double price, string producer, string substance);
	/// Removes a medicine from the medicine list repository
	void deleteMedicine(unsigned position);
	/// Updates a medicine from the medicine list repository
	void updateMedicine(unsigned position, string newName, double newPrice, string newProducer, string newSubstance);
	/// Returns a vector with the medicines containing a substring
	vector<Medicine> findMedicineList(string namePattern);
	/// Returns a vector with the medicines with the price in the specified range
	vector<Medicine> filterMedicinePriceRange(double minPrice, double maxPrice);
	/// Returns a vector sorted by the function given as a parameter
	vector<Medicine> sortMedicineList(bool (*cmp)(const Medicine&, const Medicine&), bool reverse);
	/// Returns the frequency map of the producers
	unordered_map<string, unsigned> producerReportMap();

	/// Adds a medicine to the medicine recipe repository
	void addMedicineToRecipe(unsigned position);
	/// Resets the medicine list repository
	void resetRecipe() noexcept;
	/// Generates some medicines to the medicine recipe repository
	void generateMedicinesToTheRecipe(unsigned numberOfMedicines);
	void undoLastOperation();
};
