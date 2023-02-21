#pragma warning (disable: 26823)// Dereferencing a possibly null pointer, the warning has no explanation on docs.microsoft.com

#include "UserInterfaceTools.hpp"
#include "UserInterface.h"

void UserInterface::begin() {
	populateMedicineList();
	clearScreen();
	while (const int option = globalMenu()) {
		clearScreen();
		if (option == 1) {
			medicineList();
		}
		elif(option == 2) {
			medicineRecipe();
		}
		elif(option == 3) {
			togSecureMode();
		}
		else {
			writeMiddle("Invalid option!", COLOR_RED);
		}
	}
	clearScreen();
}

int UserInterface::globalMenu() {
	try {
		newLine();
		writeMiddle(" _____ _                             ", COLOR_NEON_CYAN);
		writeMiddle("|  _  | |_ ___ ___ _____ ___ ___ _ _ ", COLOR_NEON_CYAN);
		writeMiddle("|   __|   | .'|  _|     | .'|  _| | |", COLOR_NEON_CYAN);
		writeMiddle("|__|  |_|_|__,|_| |_|_|_|__,|___|_  |", COLOR_NEON_CYAN);
		writeMiddle("                                |___|", COLOR_NEON_CYAN);
		newLine();
		writeMiddle("1) Medicine List     2) Medicine Recipe");
		writeMiddle("3) Secure Mode       0) Quit Application");
		newLine();
		writeHalfMiddle("Enter your choice: ", COLOR_CYAN, -1);
		return readInteger();
	}
	catch (...) {
		return -1;
	}
}

void UserInterface::togSecureMode() {
	string secureText = secureMode ? COLOR_RED + "disable" + COLOR_RESET : COLOR_GREEN + "enable" + COLOR_RESET;
	writeHalfMiddle("Type '" + COLOR_YELLOW + "YES" + COLOR_RESET "' if you are sure you want to " + secureText + " the secured mode: ", -3 + 32);
	if (readString() == "YES") {
		clearScreen();
		secureMode = true - secureMode;
		writeMiddle("Secure mode updated!", COLOR_GREEN);
		return;
	}
	writeMiddle("Secure mode not updated!", COLOR_RED);
}




void UserInterface::medicineList() {
	if (medicineRecipeRepository.getLength()) {
		displayMedicineList(medicineListRepository.getMedicineList());
		writeMiddle("You can't acces the medicine list managment menu while the medicine recipe list is not empty!", COLOR_RED);
		return;
	}
	while (const int option = medicineListMenu()) {
		clearScreen();
		if (option == 1) {
			displayMedicineList(medicineListRepository.getMedicineList());
		}
		elif(option == 2) {
			addMedicine();
		}
		elif(option == 3) {
			removeMedicine();
		}
		elif(option == 4) {
			updateMedicine();
		}
		elif(option == 5) {
			findMedicineList();
		}
		elif(option == 6) {
			filterMedicineList();
		}
		elif(option == 7) {
			sortMedicineList();
		}
		elif(option == 8) {
			producerReportMap();
		}
		elif(option == 9) {
			undoLastOperation();
		}
		else {
			writeMiddle("Invalid option!", COLOR_RED);
		}
	}
	clearScreen();
}

int UserInterface::medicineListMenu() {
	try {
		newLine();
		writeMiddle(" _____       _ _     _            __    _     _      _____                               _   ", COLOR_NEON_YELLOW);
		writeMiddle("|     |___ _| |_|___|_|___ ___   |  |  |_|___| |_   |     |___ ___ ___ ___ _____ ___ ___| |_ ", COLOR_NEON_YELLOW);
		writeMiddle("| | | | -_| . | |  _| |   | -_|  |  |__| |_ -|  _|  | | | | .'|   | .'| . |     | -_|   |  _|", COLOR_NEON_YELLOW);
		writeMiddle("|_|_|_|___|___|_|___|_|_|_|___|  |_____|_|___|_|    |_|_|_|__,|_|_|__,|_  |_|_|_|___|_|_|_|  ", COLOR_NEON_YELLOW);
		writeMiddle("                                                                      |___|                  ", COLOR_NEON_YELLOW);
		newLine();
		writeMiddle("1) Display Medicines   2) Add Medicine    ");
		writeMiddle("3) Remove Medicine     4) Update Medicine ");
		writeMiddle("5) Find Medicine       6) Filter Medicines");
		writeMiddle("7) Sort Medicines      8) Producer Report ");
		writeMiddle("9) Undo                0) Go back         ");
		newLine();
		writeHalfMiddle("Enter your choice: ", COLOR_YELLOW, -1);
		return readInteger();
	}
	catch (...) {
		return -1;
	}
}

Medicine UserInterface::readMedicine(string COLOR) {
	writeHalfMiddle("The name of the new medicine: ", -9);
	const string name = readString();
	validator.validateMedicineName(name);

	clearScreen();
	writeMiddle("The name of the new medicine: " + COLOR + name + COLOR_RESET, 16);

	writeHalfMiddle("The price of the new medicine: ", -5);
	const double price = readDouble();
	validator.validateMedicinePrice(price);
	string priceString = doubleToPriceString(price);

	clearScreen();
	writeMiddle("The name of the new medicine: " + COLOR + name + COLOR_RESET, 16);
	writeMiddle("The price of the new medicine: " + COLOR + priceString + COLOR_RESET, 16);

	writeHalfMiddle("The producer of the new medicine: ", -11);
	const string producer = readString();
	validator.validateMedicineProducer(producer);

	clearScreen();
	writeMiddle("The name of the new medicine: " + COLOR + name + COLOR_RESET, 16);
	writeMiddle("The price of the new medicine: " + COLOR + priceString + COLOR_RESET, 16);
	writeMiddle("The producer of the new medicine: " + COLOR + producer + COLOR_RESET, 16);

	writeHalfMiddle("The active substance of the new medicine: ", -19);
	const string substance = readString();
	validator.validateMedicineSubstance(substance);

	return Medicine(name, price, producer, substance);
}

void UserInterface::writeMedicine(const Medicine& medicine, string COLOR) {
	writeMedicine(medicine.getName(), medicine.getPrice(), medicine.getProducer(), medicine.getSubstance(), COLOR);
}

void UserInterface::writeMedicine(string name, double price, string producer, string substance, string COLOR) {
	string priceString = doubleToPriceString(price);

	writeMiddle("Name: " + COLOR + name + COLOR_RESET, 16);
	writeMiddle("Price: " + COLOR + priceString + COLOR_RESET, 16);
	writeMiddle("Producer: " + COLOR + producer + COLOR_RESET, 16);
	writeMiddle("Active substance: " + COLOR + substance + COLOR_RESET, 16);
}

void UserInterface::writeMedicine(const Medicine& medicine, string name, double price, string producer, string substance, string COLOR) {
	string oldPriceString = doubleToPriceString(medicine.getPrice());
	string priceString = doubleToPriceString(price);

	writeMiddle("Name: " + COLOR + medicine.getName() + COLOR_RESET + " -> " + COLOR + name + COLOR_RESET, 32);
	writeMiddle("Price: " + COLOR + oldPriceString + COLOR_RESET + " -> " + COLOR + priceString + COLOR_RESET, 32);
	writeMiddle("Producer: " + COLOR + medicine.getProducer() + COLOR_RESET + " -> " + COLOR + producer + COLOR_RESET, 32);
	writeMiddle("Active substance: " + COLOR + medicine.getSubstance() + COLOR_RESET + " -> " + COLOR + substance + COLOR_RESET, 32);
}

void UserInterface::populateMedicineList() {
	pharmacyService.addMedicine("Atorvastatin", 8.43, "Viatris", "atorvastatin calcium trihydrate");
	pharmacyService.addMedicine("Augmentin", 2.44, "Glaxo Smith Kline", "amoxicillin");
	pharmacyService.addMedicine("Lisinopril", 4.74, "Stada", "torasemide");
	pharmacyService.addMedicine("Levothyroxine", 4.99, "Actavis", "levothyroxine sodium");
	pharmacyService.addMedicine("Albuterol", 9.05, "Perrigo", "albuterol sulfate");
	pharmacyService.addMedicine("Dipyridamole", 6.34, "Zentiva", "dipyridamole");
	pharmacyService.addMedicine("Metformin", 9.99, "Actavis", "metformin hydrochloride");
	pharmacyService.addMedicine("Norvasc", 7.86, "Pfizer", "amlodipine maleate");
	pharmacyService.addMedicine("Metoprolol", 3.59, "Labormed", "metoprolol tartrate");
	pharmacyService.addMedicine("Nurofen Forte", 3.45, "Nurofen", "ibuprofen");
	pharmacyService.addMedicine("Paracetamol", 1.63, "Zentiva", "paracetamol");
	pharmacyService.addMedicine("Losec", 8.99, "Astra Zeneca", "omeprazole magnesium");
	pharmacyService.addMedicine("Famotidine", 5.34, "Zentiva", "ibuprofen");
	pharmacyService.addMedicine("Coldrex", 6.39, "Perrigo", "phenylephrine hydrochloride");
	pharmacyService.addMedicine("Nurofen Plus", 2.94, "Nurofen", "ibuprofen");
}

void UserInterface::displayMedicineList(const vector<Medicine>& medicineList) {
	if (medicineList.size() == 0) {
		writeMiddle("There are no medicines!", COLOR_RED);
		return;
	}

	string title = "|" + centerText(rainbowText("Medicine List"), 110 + 8 * 14) + "|";
	
	string firstLine = "|" + centerText("ID", 8) + "|" + centerText("Name", 20) + "|" + centerText("Price", 13) +
		"|" + centerText("Producer", 25) + "|" + centerText("Active substance", 40) + "|";
	writeMiddle(multipleStrings("=", 112));
	writeMiddle(title, 8 * 14);
	writeMiddle(multipleStrings("=", 112));
	writeMiddle(firstLine);
	writeMiddle(multipleStrings("=", 112));

	unsigned index = 0;

	for (const auto& i : medicineList) {
		const string position = rainbowHash(index) + to_string(index) + COLOR_RESET;
		const string name = i.getName();
		const string price = doubleToPriceString(i.getPrice(), COLOR_GREEN);
		const string producer = i.getProducer();
		const string substance = i.getSubstance();
		const string text = "|" + centerText(position, 8 + 16) + "|" + centerText(name, 20) + "|" +
			centerText(price, 13 + 16) + "|" + centerText(producer, 25) + "|" + centerText(substance, 40) + "|";
		writeMiddle(text, 16 + 16);
		index++;
	}
	writeMiddle(multipleStrings("=", 112));
	newLine();
}

void UserInterface::addMedicine() {
	try {
		Medicine newMedicine = readMedicine(rainbowHash(medicineListRepository.getLength()));

		const string name = newMedicine.getName();
		const double price = newMedicine.getPrice();
		const string producer = newMedicine.getProducer();
		const string substance = newMedicine.getSubstance();

		clearScreen();

		writeMedicine(name, price, producer, substance, rainbowHash(medicineListRepository.getLength()));
		if (secureMode) {
			writeHalfMiddle("Type '" + COLOR_GREEN + "YES" + COLOR_RESET + "' if you are sure you want to " + COLOR_GREEN + "add" + COLOR_RESET + " this medicine: ", -3 + 32);
		}
		if (!secureMode || readString() == "YES") {
			pharmacyService.addMedicine(name, price, producer, substance);
			writeMiddle("The medicine was added succesfully!", COLOR_GREEN);
			return;
		}
		clearScreen();
		writeMiddle("The medicine was not added!", COLOR_RED);
	}
	catch (const PharmacyException& except) {
		clearScreen();
		writeMiddle(except.what(), COLOR_RED);
	}
}

void UserInterface::removeMedicine() {
	try {
		displayMedicineList(medicineListRepository.getMedicineList());
		writeHalfMiddle("Choose the position of the medicine you want to delete from the list: ", -1);
		const int position = readInteger();

		clearScreen();

		writeMedicine(medicineListRepository.getMedicineAt(position), rainbowHash(position));

		if (secureMode) {
			writeHalfMiddle("Type '" + COLOR_MAGENTA + "YES" + COLOR_RESET + "' if you are sure you want to " + COLOR_MAGENTA + "remove" + COLOR_RESET + " this medicine: ", -3 + 32);
		}
		if (!secureMode || readString() == "YES") {
			pharmacyService.deleteMedicine(position);
			writeMiddle("The medicine was removed succesfully!", COLOR_GREEN);
			return;
		}
		clearScreen();
		writeMiddle("The medicine was not removed!", COLOR_RED);

		
	}
	catch (const PharmacyException& except) {
		clearScreen();
		writeMiddle(except.what(), COLOR_RED);
	}
}

void UserInterface::updateMedicine() {
	try {
		displayMedicineList(medicineListRepository.getMedicineList());
		writeHalfMiddle("Choose the position of the medicine you want to update from the list: ");
		const int position = readInteger();

		clearScreen();

		const Medicine updatedMedicine = readMedicine(rainbowHash(position));
		const string name = updatedMedicine.getName();
		const double price = updatedMedicine.getPrice();
		const string producer = updatedMedicine.getProducer();
		const string substance = updatedMedicine.getSubstance();

		clearScreen();
		writeMedicine(medicineListRepository.getMedicineAt(position), name, price, producer, substance, rainbowHash(position));
		if (secureMode) {
			writeHalfMiddle("Type '" + COLOR_YELLOW + "YES" + COLOR_RESET + "' if you are sure you want to " + COLOR_YELLOW + "update" + COLOR_RESET + " this medicine: ", -3 + 32);
		}
		if (!secureMode || readString() == "YES") {
			pharmacyService.updateMedicine(position, name, price, producer, substance);
			writeMiddle("The medicine was updated succesfully!", COLOR_GREEN);
			return;
		}
		clearScreen();
		writeMiddle("The medicine was not updated!", COLOR_RED);
	}
	catch (const PharmacyException& except) {
		clearScreen();
		writeMiddle(except.what(), COLOR_RED);
	}
}

void UserInterface::findMedicineList() {
	try {
		writeHalfMiddle("The pattern of the name of the searched medicine: ", -3);
		
		cout << COLOR_MAGENTA;
		string namePattern = readString();
		cout << COLOR_RESET;

		clearScreen();

		writeMiddle("The medicines that contains '" + COLOR_MAGENTA + namePattern + COLOR_RESET + "' in their name: ", 16);
		displayMedicineList(pharmacyService.findMedicineList(namePattern));

	}
	catch (const PharmacyException& except) {
		clearScreen();
		writeMiddle(except.what(), COLOR_RED);
	}
}

void UserInterface::filterMedicineList() {
	try {
		writeHalfMiddle("The minimum price: ");
		const int minPrice = readInteger();
		writeHalfMiddle("The maximum price: ");
		const int maxPrice = readInteger();

		if (minPrice >= maxPrice) {
			writeMiddle("The minimum price should be lower than the maximum price!", COLOR_RED);
			return;
		}

		clearScreen();

		writeMiddle("The medicines in the [" + to_string(minPrice) + ", " + to_string(maxPrice) + "] price range:");
		displayMedicineList(pharmacyService.filterMedicinePriceRange(minPrice, maxPrice));
	}
	catch (const PharmacyException& except) {
		clearScreen();
		writeMiddle(except.what(), COLOR_RED);
	}
}

void UserInterface::sortMedicineList() {
	try {
		writeMiddle("Select the " + COLOR_MAGENTA + "sort criteria" + COLOR_RESET, 16);
		newLine();
		writeMiddle("1) Name     ");
		writeMiddle("2) Price    ");
		writeMiddle("3) Producer ");
		writeMiddle("4) Substance");
		newLine();
		writeHalfMiddle("Enter your choice: ", COLOR_MAGENTA, -1);
		const int sortingOption = readInteger();

		clearScreen();

		if (sortingOption > 4 || sortingOption < 1) {
			writeMiddle("Invalid option!", COLOR_RED);
			return;
		}

		writeMiddle("Select the " + COLOR_CYAN + "sort order" + COLOR_RESET, 16);
		newLine();
		writeMiddle("1) Ascending ");
		writeMiddle("2) Descending");
		newLine();
		writeHalfMiddle("Enter your choice: ", COLOR_CYAN, -1);
		const int orderingOption = readInteger();

		clearScreen();

		if (orderingOption > 2 || orderingOption < 1) {
			writeMiddle("Invalid option!", COLOR_RED);
			return;
		}

		const bool reversedOption = orderingOption - 1;
		const string ordering = reversedOption ? "descending" : "ascending";
		
		if (sortingOption == 1) {
			writeMiddle("The medicine list sorted " + COLOR_CYAN + ordering + COLOR_RESET + ", by " + COLOR_MAGENTA + "name:" + COLOR_RESET, 32);
			displayMedicineList(pharmacyService.sortMedicineList([](const Medicine& medicine, const Medicine& other) {
				return medicine.getName() < other.getName(); }, reversedOption));
		}
		elif(sortingOption == 2) {
			writeMiddle("The medicine list sorted " + COLOR_CYAN + ordering + COLOR_RESET + ", by " + COLOR_MAGENTA + "price:" + COLOR_RESET, 32);
			displayMedicineList(pharmacyService.sortMedicineList([](const Medicine& medicine, const Medicine& other) noexcept {
				return medicine.getPrice() < other.getPrice(); }, reversedOption));
		}
		elif(sortingOption == 3) {
			writeMiddle("The medicine list sorted " + COLOR_CYAN + ordering + COLOR_RESET + ", by " + COLOR_MAGENTA + "producer:" + COLOR_RESET, 32);
			displayMedicineList(pharmacyService.sortMedicineList([](const Medicine& medicine, const Medicine& other) {
				return medicine.getProducer() < other.getProducer(); }, reversedOption));
		}
		else {
			writeMiddle("The medicine list sorted " + COLOR_CYAN + ordering + COLOR_RESET + ", by " + COLOR_MAGENTA + "active substance:" + COLOR_RESET, 32);
			displayMedicineList(pharmacyService.sortMedicineList([](const Medicine& medicine, const Medicine& other) {
				return medicine.getSubstance() < other.getSubstance(); }, reversedOption));
		}
	}
	catch (const PharmacyException& except) {
		clearScreen();
		writeMiddle(except.what(), COLOR_RED);
	}
}

void UserInterface::producerReportMap() {
	try {
		string title = "|" + centerText(rainbowText("Producer Report"), 39 + 8 * 16) + "|";
		string firstLine = "|" + centerText("Producer", 25) + "|" + centerText("Appearances", 13) + "|";

		writeMiddle(multipleStrings("=", 41));
		writeMiddle(title, 8 * 16);
		writeMiddle(multipleStrings("=", 41));
		writeMiddle(firstLine);
		writeMiddle(multipleStrings("=", 41));

		unsigned index = 0;
		for (const auto& pair : pharmacyService.producerReportMap()) {
			const string producer = pair.first;
			const string appearances = rainbowHash(index) + to_string(pair.second) + COLOR_RESET;

			const string text = "|" + centerText(producer, 25) + "|" + centerText(appearances, 13 + 16) + "|";
			writeMiddle(text, 16);
			index++;
		}

		writeMiddle(multipleStrings("=", 41));
		newLine();
	}
	catch (const PharmacyException& except) {
		clearScreen();
		writeMiddle(except.what(), COLOR_RED);
	}
}

void UserInterface::undoLastOperation() {
	try {
		if (secureMode) {
			writeHalfMiddle("Type '" + COLOR_RED + "YES" + COLOR_RESET + "' if you are sure you want to " + COLOR_RED + "undo" + COLOR_RESET + " the last operation: ", -3 + 32);
		}
		if (!secureMode || readString() == "YES") {
			pharmacyService.undoLastOperation();
			writeMiddle("Undo operation has been executed succesfully!", COLOR_GREEN);
			return;
		}
		writeMiddle("Undo operation has been canceled!", COLOR_RED);
	}
	catch (const PharmacyException& except) {
		clearScreen();
		writeMiddle(except.what(), COLOR_RED);
	}
}





void UserInterface::medicineRecipe() {
	while (const int option = medicineRecipeMenu()) {
		clearScreen();
		if (option == 1) {
			displayMedicineRecipe();
		}
		elif(option == 2) {
			addMedicineToRecipe();
		}
		elif(option == 3) {
			resetRecipe();
		}
		elif(option == 4) {
			generateMedicinesToTheRecipe();
		}
		elif(option == 5) {
			exportRecipe();
		}
		else {
			writeMiddle("Invalid option!", COLOR_RED);
		}
	}
	clearScreen();
}

int UserInterface::medicineRecipeMenu() {
	try {
		newLine();
		writeMiddle(" _____       _ _     _            _____         _            _____                               _   ", COLOR_NEON_GREEN);
		writeMiddle("|     |___ _| |_|___|_|___ ___   | __  |___ ___|_|___ ___   |     |___ ___ ___ ___ _____ ___ ___| |_ ", COLOR_NEON_GREEN);
		writeMiddle("| | | | -_| . | |  _| |   | -_|  |    -| -_|  _| | . | -_|  | | | | .'|   | .'| . |     | -_|   |  _|", COLOR_NEON_GREEN);
		writeMiddle("|_|_|_|___|___|_|___|_|_|_|___|  |__|__|___|___|_|  _|___|  |_|_|_|__,|_|_|__,|_  |_|_|_|___|_|_|_|  ", COLOR_NEON_GREEN);
		writeMiddle("                                                 |_|                          |___|                  ", COLOR_NEON_GREEN);
		newLine();
		writeMiddle("1) Display Recipe   2) Add to Recipe  ");
		writeMiddle("3) Clear Recipe     4) Generate Recipe");
		writeMiddle("5) Export Recipe    0) Go back        ");
		newLine();
		writeHalfMiddle("Enter your choice: ", COLOR_GREEN, -1);
		return readInteger();
	}
	catch (...) {
		return -1;
	}
}

void UserInterface::displayMedicineRecipe() {
	if (medicineRecipeRepository.getLength() == 0) {
		writeMiddle("There are no medicines in the recipe!", COLOR_RED);
		return;
	}

	string title = "|" + centerText(rainbowText("Medicine Recipe"), 110 + 8 * 16) + "|";
	string firstLine = "|" + centerText("ID", 8) + "|" + centerText("Name", 20) + "|" + centerText("Price", 13) +
		"|" + centerText("Producer", 25) + "|" + centerText("Active substance", 40) + "|";
	string totalSum = "Total sum: " + doubleToPriceString(medicineRecipeRepository.getSum());
	string lastLine = "|" + centerText(rainbowText(totalSum), 110 + 8 * (totalSum.size() + 1)) + "|";

	writeMiddle(multipleStrings("=", 112));
	writeMiddle(title, 8 * 16);
	writeMiddle(multipleStrings("=", 112));
	writeMiddle(firstLine);
	writeMiddle(multipleStrings("=", 112));

	unsigned index = 0;

	for (const auto& i : medicineRecipeRepository.getMedicineRecipe()) {
		const string position = rainbowHash(index) + to_string(index) + COLOR_RESET;
		const string name = i.getName();
		const string price = doubleToPriceString(i.getPrice(), COLOR_GREEN);
		const string producer = i.getProducer();
		const string substance = i.getSubstance();
		const string text = "|" + centerText(position, 8 + 16) + "|" + centerText(name, 20) + "|" +
			centerText(price, 13 + 16) + "|" + centerText(producer, 25) + "|" + centerText(substance, 40) + "|";
		writeMiddle(text, 16 + 16);
		index++;
	}

	writeMiddle(multipleStrings("=", 112));
	writeMiddle(lastLine, 8 * (totalSum.size() + 1));
	writeMiddle(multipleStrings("=", 112));
	newLine();
}

void UserInterface::addMedicineToRecipe() {
	try {
		displayMedicineList(medicineListRepository.getMedicineList());
		writeHalfMiddle("Choose the position of the medicine you want to add in the recipe: ", -1);
		const unsigned position = readInteger();

		clearScreen();

		writeMedicine(medicineListRepository.getMedicineAt(position), rainbowHash(position));
		if (secureMode) {
			writeHalfMiddle("Type '" + COLOR_GREEN + "YES" + COLOR_RESET + "' if you are sure you want to " + COLOR_GREEN + "add" + COLOR_RESET + " this medicine in the recipe: ", -3 + 32);
		}
		if (!secureMode || readString() == "YES") {
			pharmacyService.addMedicineToRecipe(position);
			writeMiddle("The medicine has been succesfully added in the recipe!", COLOR_GREEN);
			return;
		}
		clearScreen();
		writeMiddle("The medicine has not been added in the recipe!", COLOR_RED);
	}
	catch (const PharmacyException& except) {
		clearScreen();
		writeMiddle(except.what(), COLOR_RED);
	}
}
void UserInterface::resetRecipe() {
	try {
		displayMedicineRecipe();
		if (secureMode) {
			writeHalfMiddle("Type '" + COLOR_RED + "YES" + COLOR_RESET + "' if you are sure you want to " + COLOR_RED + "reset" + COLOR_RESET + " the recipe: ", -3 + 32);
		}
		if (!secureMode || readString() == "YES") {
			pharmacyService.resetRecipe();
			writeMiddle("The recipe has been succesfully reset!", COLOR_GREEN);
			return;
		}
		clearScreen();
		writeMiddle("The recipe has not been reset!", COLOR_RED);
	}
	catch (const PharmacyException& except) {
		clearScreen();
		writeMiddle(except.what(), COLOR_RED);
	}
}
void UserInterface::generateMedicinesToTheRecipe() {
	writeHalfMiddle("Choose how many medicines you want to generate in the recipe: ", -1);
	const unsigned count = readInteger();

	if (secureMode) {
		writeHalfMiddle("Type '" + COLOR_GREEN + "YES" + COLOR_RESET + "' if you are sure you want to " + COLOR_GREEN + "generate " + to_string(count) + " medicines" + COLOR_RESET + " to the recipe: ", -3 + 32);
	}
	if (!secureMode || readString() == "YES") {
		pharmacyService.generateMedicinesToTheRecipe(count);
		writeMiddle("There have been succesfully generated " + to_string(count) + " medicines in the recipe!", COLOR_GREEN);
		return;
	}
	clearScreen();
	writeMiddle("No medicines were generated in the recipe!", COLOR_RED);
}

void UserInterface::exportRecipe() {
	try {
		writeMiddle("The file will be automatically exported with the" + COLOR_MAGENTA + " html extension " + COLOR_RESET + "in the" + COLOR_MAGENTA + " Data directory" + COLOR_RESET, 32);
		writeHalfMiddle("The name of the file: ", -5);
		string file = readString();
		file = "Data/" + file + ".html";

		medicineRecipeRepository.exportRecipe(file);
		
		clearScreen();
		writeMiddle("The recipe has been succesfully exported!", COLOR_GREEN);
	}
	catch (const PharmacyException& except) {
		clearScreen();
		writeMiddle(except.what(), COLOR_RED);
	}
}
