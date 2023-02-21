#pragma once
#include "PharmacyService.h"
#include "Validator.h"
#include "Medicine.h"

class UserInterface {
private:
	bool secureMode = true;

	Validator validator;
	MedicineListRepository& medicineListRepository;
	MedicineRecipeRepository medicineRecipeRepository;
	PharmacyService pharmacyService;

	Medicine readMedicine(string COLOR);
	void writeMedicine(const Medicine& medicine, string COLOR);
	void writeMedicine(string name, double price, string producer, string substance, string COLOR);
	void writeMedicine(const Medicine& medicine, string name, double price, string producer, string substance, string COLOR);

	int globalMenu();
	void togSecureMode();

	void medicineList();
	int medicineListMenu();
	void populateMedicineList();
	void displayMedicineList(const vector<Medicine>& medicineList);
	void addMedicine();
	void removeMedicine();
	void updateMedicine();
	void findMedicineList();
	void filterMedicineList();
	void sortMedicineList();
	void producerReportMap();
	void undoLastOperation();

	void medicineRecipe();
	int medicineRecipeMenu();
	void displayMedicineRecipe();
	void addMedicineToRecipe();
	void resetRecipe();
	void generateMedicinesToTheRecipe();
	void exportRecipe();

public:
	UserInterface(MedicineListRepository& input) noexcept :
		pharmacyService{ input, medicineRecipeRepository },
		medicineListRepository{ input } {};
	void begin();
};