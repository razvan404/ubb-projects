#pragma warning (disable: 26486) // Don't pass a pointer that may be invalid to a function. Parameter 0 '@(temporary 1)' in call to 'icall' may be invalid (lifetime.3).
#pragma warning (disable: 26823) // Dereferencing a possibly null pointer 'result.->' (lifetime.1).
#include "Exceptions.hpp"
#include "MedicineRepository.h"

unsigned MedicineListRepository::getLength() const noexcept {
	return myList.size();
}
const Medicine& MedicineListRepository::getMedicineAt(unsigned i) const {
	if (i >= myList.size()) {
		throw IndexException{};
	}
	return myList.at(i);
}
void MedicineListRepository::addMedicine(const Medicine& medicine) {
	myList.emplace_back(Medicine());
	myList.back() = medicine;
}

void MedicineListRepository::addMedicine(const Medicine& medicine, unsigned i) {
	if (i > myList.size()) {
		throw IndexException{};
	}
	myList.insert(myList.begin() + i, Medicine());
	myList.at(i) = medicine;
}

void MedicineListRepository::deleteMedicine(unsigned i) {
	if (i >= myList.size()) {
		throw IndexException{};
	}
	myList.erase(myList.begin() + i);
}

void MedicineListRepository::updateMedicine(const Medicine& medicine, unsigned i) {
	if (i >= myList.size()) {
		throw IndexException{};
	}
	myList.at(i) = medicine;
}

unsigned MedicineListRepository::findMedicine(const Medicine& medicine) {
	const auto& iterator = find_if(myList.begin(), myList.end(), [&](const Medicine& other) noexcept { return medicine == other; });
	return distance(myList.begin(), iterator);
}

vector<Medicine> MedicineListRepository::getMedicineList() const {
	return myList;
}



unsigned MedicineRecipeRepository::getLength() const noexcept {
	return myRecipe.size();
}

double MedicineRecipeRepository::getSum() const noexcept {
	return totalSum;
}

const vector<Medicine>& MedicineRecipeRepository::getMedicineRecipe() const noexcept {
	return myRecipe;
}

void MedicineRecipeRepository::addMedicine(const Medicine& medicine) {
	myRecipe.emplace_back(medicine);
	totalSum += medicine.getPrice();
}

void MedicineRecipeRepository::resetRecipe() noexcept {
	totalSum = 0;
	myRecipe.clear();
}

void MedicineRecipeRepository::generateMedicines(const vector<Medicine>& medicineList, unsigned numberOfMedicines) {
	random_device device;
	mt19937 generator{ device() };
	const uniform_int_distribution<int> distribution(0, medicineList.size() - 1);

	while (numberOfMedicines) {
		const int random = distribution(generator);
		addMedicine(medicineList.at(random));
		--numberOfMedicines;
	}
}

void MedicineRecipeRepository::exportRecipe(string fileName, string fileType) const {
	if (fileType == "html") {
		const auto& exportHTML = make_unique<ExportAsHTML>(*this, fileName);
		if (exportHTML) {
			exportHTML->exportFile();
		}
	}
	else if (fileType == "csv") {
		const auto& exportCSV = make_unique<ExportAsCSV>(*this, fileName);
		if (exportCSV) {
			exportCSV->exportFile();
		}
	}
	else {
		throw OtherException{ "Invalid export type!" };
	}
}



void ExportAsHTML::exportFile() {
	const string file = fileName + ".html";
	ofstream fout(file);

	fout << "<!DOCTYPE html>\n";
	fout << "<html>\n";
	fout << "<style>\n";
	fout << "table, th, td{\n";
	fout << "border:1px solid black;\n";
	fout << "}\n";
	fout << "</style>\n";
	fout << "<body>\n";

	fout << "<h1>Medicine Recipe</h1>\n";

	if (recipe.getLength() == 0) {
		fout << "<h2>There are no medicines in the recipe!</h2>\n";
	}
	else {
		fout << "<table style=width:100%>\n";
		fout << "  <tr>\n";
		fout << "    <th><h2>ID</h2></th>\n";
		fout << "    <th><h2>Name</h2></th>\n";
		fout << "    <th><h2>Price</h2></th>\n";
		fout << "    <th><h2>Producer</h2></th>\n";
		fout << "    <th><h2>Active substance</h2></th>\n";
		fout << "  </tr>\n";

		unsigned index = 0;
		for (const auto& i : recipe.getMedicineRecipe()) {
			fout << "  <tr>\n";
			fout << "    <th>" << index << "</th>\n";
			fout << "    <th>" << i.getName() << "</th>\n";
			fout << "    <th>" << fixed << setprecision(2) << i.getPrice() << "</th>\n";
			fout << "    <th>" << i.getProducer() << "</th>\n";
			fout << "    <th>" << i.getSubstance() << "</th>\n";
			fout << "  </tr>\n";
			++index;
		}

		fout << "</table>\n";
	}

	fout << "<h2>Total sum: $" << fixed << setprecision(2) << recipe.getSum() << "</h2>\n";

	fout << "</body>\n";
	fout << "</html>\n";

	fout.close();
}

void ExportAsCSV::exportFile() {
	ofstream fout(fileName + ".csv");

	fout << "Medicine Recipe,,,,\n";

	if (recipe.getLength() == 0) {
		fout << "There are no medicines in the recipe,,,,\n";
	}
	else {
		fout << "ID,Name,Price,Producer,Active Substance\n";

		unsigned index = 0;
		for (const auto& i : recipe.getMedicineRecipe()) {
			fout << index << "," + i.getName() + ",$" << i.getPrice() << ",";
			fout << i.getProducer() << "," + i.getSubstance() + "\n";
			++index;
		}
	}

	fout << "Total sum: $" << recipe.getSum() << "\n";

	fout.close();
}
