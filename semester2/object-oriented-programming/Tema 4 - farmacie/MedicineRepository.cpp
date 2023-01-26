#pragma warning (disable: 26823) // Dereferencing a possibly null pointer 'i'. Skipped because is from the C++11 for in range, impossible to be nullptr.
#include "Exceptions.h"
#include "MedicineRepository.h"


unsigned MedicineListRepository::getLength() const noexcept {
	return list.size();
}
const Medicine& MedicineListRepository::getMedicineAt(unsigned i) const {
	if (i >= list.size()) {
		throw IndexException{};
	}
	return list.at(i);
}
void MedicineListRepository::addMedicine(const Medicine& medicine) {
	list.emplace_back(Medicine());
	list.back() = medicine;
}

void MedicineListRepository::addMedicine(const Medicine& medicine, unsigned i) {
	if (i >= list.size()) {
		throw IndexException{};
	}
	list.insert(list.begin() + i, Medicine());
	list.at(i) = medicine;
}

void MedicineListRepository::deleteMedicine(unsigned i) {
	if (i >= list.size()) {
		throw IndexException{};
	}
	list.erase(list.begin() + i);
}

void MedicineListRepository::updateMedicine(const Medicine& medicine, unsigned i) {
	if (i >= list.size()) {
		throw IndexException{};
	}
	list.at(i) = medicine;
}

unsigned MedicineListRepository::findMedicine(const Medicine& medicine) {
	const auto& iterator = find_if(list.begin(), list.end(), [&](const Medicine& other) noexcept { return medicine == other; });
	return distance(list.begin(), iterator);
}

const vector<Medicine>& MedicineListRepository::getMedicineList() const noexcept {
	return list;
}



unsigned MedicineRecipeRepository::getLength() const noexcept {
	return recipe.size();
}

double MedicineRecipeRepository::getSum() const noexcept {
	return totalSum;
}

const vector<Medicine>& MedicineRecipeRepository::getMedicineRecipe() const noexcept {
	return recipe;
}

void MedicineRecipeRepository::addMedicine(const Medicine& medicine) {
	recipe.push_back(medicine);
	totalSum += medicine.getPrice();
}

void MedicineRecipeRepository::resetRecipe() noexcept {
	totalSum = 0;
	recipe.clear();
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

void MedicineRecipeRepository::exportRecipe(string file) {
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

	if (recipe.size() == 0) {
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
		for (const auto& i : recipe) {
			fout << "  <tr>\n";
			fout << "    <th>" + to_string(index) + "</th>\n";
			fout << "    <th>" + i.getName() + "</th>\n";
			fout << "    <th>" + doubleToPriceString(i.getPrice()) + "</th>\n";
			fout << "    <th>" + i.getProducer() + "</th>\n";
			fout << "    <th>" + i.getSubstance() + "</th>\n";
			fout << "  </tr>\n";
			++index;
		}

		fout << "</table>\n";
	}

	fout << "<h2>Total sum: " + doubleToPriceString(getSum()) + "</h2>\n";

	fout << "</body>\n";
	fout << "</html>\n";

	fout.close();
}
