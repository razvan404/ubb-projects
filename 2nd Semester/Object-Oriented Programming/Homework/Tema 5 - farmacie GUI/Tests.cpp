#include <cassert>
#include <algorithm>
#include <sstream>

#include "Tests.h"
#include "Validator.h"
#include "PharmacyService.h"
#include "Exceptions.hpp"
#include "MedicineRepository.h"


using std::swap;
using std::ifstream;
using std::stringstream;

void Tests::runAllTests() {
	runMedicineTests();
	runValidatorsTests();
	runMedicineListRepositoryTests();
	runMedicineRecipeRepositoryTests();
	runServiceTests();
	runExportTests();
}

void Tests::runMedicineTests() {
	Medicine medicine("Atorvastatin", 19.99, "Lipitor", "atorvastatin calcium trihydrate");
	assert(medicine.getName() == "Atorvastatin");
	assert(medicine.getPrice() == 19.99);
	assert(medicine.getProducer() == "Lipitor");
	assert(medicine.getSubstance() == "atorvastatin calcium trihydrate");
	Medicine eq("Atorvastatin", 17.99, "Lipitor", "calcium trihydrate");
	assert(medicine == eq);
	swap(medicine, eq);
	assert(medicine.getPrice() == 17.99);
	Medicine copy = medicine;
	assert(copy.getName() == "Atorvastatin");
	assert(copy.getPrice() == 17.99);
}

void Tests::runValidatorsTests() {
	Validator valid;
	valid.validateMedicineName("Atorvastatin");
	try {
		valid.validateMedicineName("KD");
		assert(false);
	}
	catch (...) {
		assert(true);
	}
	valid.validateMedicinePrice(29.99);
	try {
		valid.validateMedicinePrice(0);
		assert(false);
	}
	catch (...) {
		assert(true);
	}
	valid.validateMedicineProducer("Lipitor");
	try {
		valid.validateMedicineProducer("Ana");
		assert(false);
	}
	catch (...) {
		assert(true);
	}
	valid.validateMedicineSubstance("atorvastatin calcium trihydrate");
	try {
		valid.validateMedicineSubstance("rice");
		assert(false);
	}
	catch (...) {
		assert(true);
	}
}

void Tests::runMedicineListRepositoryTests() {
	MedicineListRepository medicineListRepository;
	medicineListRepository.addMedicine(Medicine("Atorvastatin", 18.43, "Viatris", "atorvastatin calcium trihydrate"));
	medicineListRepository.addMedicine(Medicine("Augmentin", 12.44, "GSK", "amoxicillin"));
	medicineListRepository.addMedicine(Medicine("Lisinopril", 34.74, "Almus", "torasemide"));
	medicineListRepository.addMedicine(Medicine("Levothyroxine", 14.99, "Wockhardt", "levothyroxine sodium"));
	medicineListRepository.addMedicine(Medicine("Albuterol", 19.05, "Prahem", "albuterol sulfate"));
	medicineListRepository.addMedicine(Medicine("Metformin", 89.99, "Bristol-Myers Squibb", "metformin hydrochloride"));
	medicineListRepository.addMedicine(Medicine("Amlodipine", 17.86, "Synthon Pharmaceuticals", "amlodipine maleate"));
	medicineListRepository.addMedicine(Medicine("Metoprolol", 13.59, "Taj Pharma", "metoprolol tartrate"));
	try {
		medicineListRepository.addMedicine(Medicine("Metoprol", 13.59, "Taj Pharma", "metoprolol tartrate"), 10);
		assert(false);
	}
	catch (...) {
		assert(true);
	}
	assert(medicineListRepository.getLength() == 8);
	assert(medicineListRepository.getMedicineAt(2).getName() == "Lisinopril");
	assert(medicineListRepository.getMedicineAt(3).getPrice() == 14.99);
	assert(medicineListRepository.getMedicineAt(4).getProducer() == "Prahem");
	assert(medicineListRepository.getMedicineAt(5).getSubstance() == "metformin hydrochloride");
	medicineListRepository.updateMedicine(Medicine("Amlodipine", 17.86, "Synthon Pharmaceuticals", "maleate"), 6);
	assert(medicineListRepository.getMedicineAt(6).getSubstance() == "maleate");
	try {
		medicineListRepository.updateMedicine(Medicine("Amlodipine", 17.86, "Synthon Pharmaceuticals", "maleate"), 10);
		assert(false);
	}
	catch (...) {
		assert(true);
	}
	try {
		medicineListRepository.getMedicineAt(8);
		assert(false);
	}
	catch (const PharmacyException& except) {
		assert(except.what().find("Invalid position!") != string::npos);
	}
	medicineListRepository.deleteMedicine(7);
	assert(medicineListRepository.getLength() == 7);
	try {
		medicineListRepository.deleteMedicine(7);
		assert(false);
	}
	catch (...) {
		assert(true);
	}
}

void Tests::runMedicineRecipeRepositoryTests() {
	MedicineListRepository medicineListRepository;
	medicineListRepository.addMedicine(Medicine("Atorvastatin", 18.43, "Viatris", "atorvastatin calcium trihydrate"));
	medicineListRepository.addMedicine(Medicine("Augmentin", 12.44, "GSK", "amoxicillin"));
	medicineListRepository.addMedicine(Medicine("Lisinopril", 34.74, "Almus", "torasemide"));
	medicineListRepository.addMedicine(Medicine("Levothyroxine", 14.99, "Wockhardt", "levothyroxine sodium"));
	medicineListRepository.addMedicine(Medicine("Albuterol", 19.05, "Prahem", "albuterol sulfate"));
	medicineListRepository.addMedicine(Medicine("Metformin", 89.99, "Bristol-Myers Squibb", "metformin hydrochloride"));
	medicineListRepository.addMedicine(Medicine("Amlodipine", 17.86, "Synthon Pharmaceuticals", "amlodipine maleate"));
	medicineListRepository.addMedicine(Medicine("Metoprolol", 13.59, "Taj Pharma", "metoprolol tartrate"));

	MedicineRecipeRepository medicineRecipeRepository;
	assert(medicineRecipeRepository.getLength() == 0);
	assert(medicineRecipeRepository.getSum() == 0);
	medicineRecipeRepository.addMedicine(medicineListRepository.getMedicineAt(1));
	medicineRecipeRepository.addMedicine(medicineListRepository.getMedicineAt(4));
	medicineRecipeRepository.addMedicine(medicineListRepository.getMedicineAt(7));
	assert(medicineRecipeRepository.getLength() == 3);
	assert(medicineRecipeRepository.getSum() == 45.08);
	medicineRecipeRepository.resetRecipe();
	assert(medicineRecipeRepository.getLength() == 0);
	assert(medicineRecipeRepository.getSum() == 0);
	medicineRecipeRepository.generateMedicines(medicineListRepository.getMedicineList(), 10);
	assert(medicineRecipeRepository.getMedicineRecipe().size() == 10);
	medicineRecipeRepository.resetRecipe();
}

void Tests::runServiceTests() {
	MedicineListRepository medicineListRepository;
	MedicineRecipeRepository medicineRecipeRepository;
	PharmacyService pharmacyService(medicineListRepository, medicineRecipeRepository);

	pharmacyService.addMedicine("Atorvastatin", 18.43, "Viatris", "atorvastatin calcium trihydrate");
	pharmacyService.addMedicine("Augmentin", 12.44, "GSK", "amoxicillin");
	pharmacyService.addMedicine("Lisinopril", 34.74, "Almus", "torasemide");
	pharmacyService.addMedicine("Levothyroxine", 14.99, "Wockhardt", "levothyroxine sodium");
	pharmacyService.addMedicine("Albuterol", 19.05, "Prahem", "albuterol sulfate");
	pharmacyService.addMedicine("Metformin", 89.99, "Bristol-Myers Squibb", "metformin hydrochloride");
	pharmacyService.addMedicine("Amlodipine", 17.86, "Synthon Pharmaceuticals", "amlodipine maleate");
	pharmacyService.addMedicine("Metoprolol", 13.59, "Taj Pharma", "metoprolol tartrate");
	pharmacyService.addMedicine("Paracetamol", 0.63, "Zentiva", "paracetamol");
	assert(medicineListRepository.getLength() == 9);
	assert(medicineListRepository.getMedicineAt(1).getName() == "Augmentin");
	assert(medicineListRepository.getMedicineAt(2).getPrice() == 34.74);
	assert(medicineListRepository.getMedicineAt(3).getProducer() == "Wockhardt");
	assert(medicineListRepository.getMedicineAt(4).getSubstance() == "albuterol sulfate");
	try {
		pharmacyService.addMedicine("Amlodipine", 14.54, "Synthon Pharmaceuticals", "maleate");
		assert(false);
	}
	catch (...) {
		assert(true);
	}
	pharmacyService.deleteMedicine(3);
	assert(medicineListRepository.getLength() == 8);
	assert(medicineListRepository.getMedicineAt(3).getProducer() == "Prahem");
	try {
		medicineListRepository.deleteMedicine(8);
		assert(false);
	}
	catch (...) {
		assert(true);
	}
	pharmacyService.updateMedicine(2, "Levothyroxine", 14.99, "Wockhardt", "levothyroxine sodium");
	assert(medicineListRepository.getMedicineAt(2).getProducer() == "Wockhardt");
	try {
		pharmacyService.updateMedicine(8, "Levothyxine", 14.99, "Wockhardt", "levothyroxine sodium");
		assert(false);
	}
	catch (...) {
		assert(true);
	}
	try {
		pharmacyService.updateMedicine(5, "Levothyroxine", 13.29, "Wockhardt", "sodium");
		assert(false);
	}
	catch (...) {
		assert(medicineListRepository.getMedicineAt(5).getName() == "Amlodipine");
	}

	
	const vector<Medicine>& patternList = pharmacyService.findMedicineList("ol");
	assert(patternList.size() == 3);
	assert(patternList.at(0).getName() == "Albuterol");
	assert(patternList.at(1).getName() == "Metoprolol");
	assert(patternList.at(2).getName() == "Paracetamol");

	const vector<Medicine>& priceRange = pharmacyService.filterMedicinePriceRange(12, 18);
	assert(priceRange.size() == 4);
	assert(priceRange.at(0).getPrice() == 12.44);
	assert(priceRange.at(1).getPrice() == 14.99);
	assert(priceRange.at(2).getPrice() == 17.86);
	assert(priceRange.at(3).getPrice() == 13.59);
	
	const vector<Medicine>& sortedMedicineList = pharmacyService.sortMedicineList([](const Medicine& medicine, const Medicine& other) noexcept { return medicine.getPrice() > other.getPrice(); }, false);
	assert(sortedMedicineList.size() == 8);
	assert(sortedMedicineList.at(0).getPrice() == 89.99);
	assert(sortedMedicineList.at(1).getPrice() == 19.05);
	assert(sortedMedicineList.at(2).getPrice() == 18.43);

	const vector<Medicine>& reversedMedicineList = pharmacyService.sortMedicineList([](const Medicine& medicine, const Medicine& other) noexcept { return medicine.getPrice() > other.getPrice(); }, true);
	assert(reversedMedicineList.size() == 8);
	assert(reversedMedicineList.at(0).getPrice() == 0.63);
	assert(reversedMedicineList.at(1).getPrice() == 12.44);
	assert(reversedMedicineList.at(2).getPrice() == 13.59);

	try {
		const vector<Medicine>& sortedMedicineList = pharmacyService.sortMedicineList(nullptr, false);
		assert(false);
	}
	catch (...) {
		assert(true);
	}
	pharmacyService.addMedicine("Famotidine", 0.63, "Zentiva", "ibuprofen");
	auto report = pharmacyService.producerReportMap();
	assert(report["Zentiva"].size() == 2);

	pharmacyService.addMedicineToRecipe(0);
	pharmacyService.addMedicineToRecipe(1);
	pharmacyService.addMedicineToRecipe(2);
	assert(medicineRecipeRepository.getLength() == 3);
	assert(medicineRecipeRepository.getSum() == 45.86);

	try {
		pharmacyService.addMedicineToRecipe(9);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	pharmacyService.resetRecipe();
	assert(medicineRecipeRepository.getLength() == 0);
	assert(medicineRecipeRepository.getSum() == 0);

	pharmacyService.generateMedicinesToTheRecipe(10);
	assert(medicineRecipeRepository.getLength() == 10);
	assert(medicineRecipeRepository.getSum() != 0);

	pharmacyService.generateMedicinesToTheRecipe(2);
	assert(medicineRecipeRepository.getLength() == 12);

	pharmacyService.addMedicine("Lisinopril", 34.74, "Almus", "torasemide");
	assert(medicineListRepository.getLength() == 10);
	pharmacyService.undoLastOperation();
	assert(medicineListRepository.getLength() == 9);

	const Medicine auxMedicine = medicineListRepository.getMedicineAt(7);
	pharmacyService.deleteMedicine(7);
	assert(medicineListRepository.getLength() == 8);
	pharmacyService.undoLastOperation();
	assert(medicineListRepository.getLength() == 9);
	assert(medicineListRepository.getMedicineAt(7) == auxMedicine);

	pharmacyService.updateMedicine(7, "Lisinopril", 34.74, "Almus", "torasemide");
	assert(medicineListRepository.getMedicineAt(7).getName() == "Lisinopril");
	pharmacyService.undoLastOperation();
	assert(medicineListRepository.getMedicineAt(7) == auxMedicine);
	while (medicineListRepository.getLength()) {
		pharmacyService.undoLastOperation();
	}
	try {
		pharmacyService.undoLastOperation();
		assert(false);
	}
	catch (...) {
		assert(true);
	}
}

void Tests::runExportTests() {
	MedicineListRepository medicineListRepository;
	MedicineRecipeRepository medicineRecipeRepository;
	PharmacyService pharmacyService(medicineListRepository, medicineRecipeRepository);

	pharmacyService.addMedicine("Lisinopril", 34.74, "Almus", "torasemide");
	pharmacyService.addMedicine("Levothyroxine", 14.99, "Wockhardt", "levothyroxine sodium");
	pharmacyService.addMedicineToRecipe(0);
	pharmacyService.addMedicineToRecipe(1);
	medicineRecipeRepository.exportRecipe("testFile", "html");

	ifstream testFile("testFile.html");
	const string content((std::istreambuf_iterator<char>(testFile)),
		(std::istreambuf_iterator<char>()));
	
	assert(content.find("Lisinopril") != string::npos);
	assert(content.find("Levothyroxine") != string::npos);
	assert(content.find("Total sum: $49.73") != string::npos);

	testFile.close();
	remove("testFile.html");

	medicineRecipeRepository.resetRecipe();
	medicineRecipeRepository.exportRecipe("testFile", "html");

	ifstream testFileClear("testFile.html");
	const string contentClear((std::istreambuf_iterator<char>(testFileClear)),
		(std::istreambuf_iterator<char>()));

	assert(contentClear.find("There are no medicines in the recipe!") != string::npos);

	testFileClear.close();
	remove("testFile.html");
}
