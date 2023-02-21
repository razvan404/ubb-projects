#pragma once

class Tests {
public:
	void runAllTests();

private:
	void runMedicineTests();
	void runValidatorsTests();
	void runMedicineListRepositoryTests();
	void runMedicineRecipeRepositoryTests();
	void runServiceTests();
	void runExportTests();
};

