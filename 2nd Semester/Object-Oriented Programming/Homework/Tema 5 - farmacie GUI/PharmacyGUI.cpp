#include "PharmacyGUI.h"
#include "Exceptions.hpp"

void PharmacyGUI::populateMedicineList() {
	service.addMedicine("Atorvastatin", 8.43, "Viatris", "atorvastatin calcium trihydrate");
	service.addMedicine("Augmentin", 2.44, "Glaxo Smith Kline", "amoxicillin");
	service.addMedicine("Lisinopril", 4.74, "Stada", "torasemide");
	service.addMedicine("Levothyroxine", 4.99, "Actavis", "levothyroxine sodium");
	service.addMedicine("Albuterol", 9.05, "Perrigo", "albuterol sulfate");
	service.addMedicine("Dipyridamole", 6.34, "Zentiva", "dipyridamole");
	service.addMedicine("Metformin", 9.99, "Actavis", "metformin hydrochloride");
	service.addMedicine("Norvasc", 7.86, "Pfizer", "amlodipine maleate");
	service.addMedicine("Metoprolol", 3.59, "Labormed", "metoprolol tartrate");
	service.addMedicine("Nurofen Forte", 3.45, "Nurofen", "ibuprofen");
	service.addMedicine("Paracetamol", 1.63, "Zentiva", "paracetamol");
	service.addMedicine("Losec", 8.99, "Astra Zeneca", "omeprazole magnesium");
	service.addMedicine("Famotidine", 5.34, "Zentiva", "ibuprofen");
	service.addMedicine("Coldrex", 6.39, "Perrigo", "phenylephrine hydrochloride");
	service.addMedicine("Nurofen Plus", 2.94, "Nurofen", "ibuprofen");
}

void PharmacyGUI::buildGUI() {
	setLayout(allScreen);

	QWidget* mainWidget = new QWidget;
	mainWidget->setLayout(mainLayout);

	// Adding the list and the sorting buttons
	QWidget* leftWidget = new QWidget;
	QVBoxLayout* leftLayout = new QVBoxLayout;
	leftWidget->setLayout(leftLayout);

	QLabel* listTitle = new QLabel("Medicine List");
	listTitle->setStyleSheet("font: bold 30px");

	leftLayout->addWidget(listTitle);

	resetButton = new QPushButton("Clear Filters");
	leftLayout->addWidget(resetButton);

	medicineList = new QTableWidget;

	medicineList->setMinimumWidth(550);

	medicineList->setEditTriggers(QAbstractItemView::NoEditTriggers);
	medicineList->setFocusPolicy(Qt::NoFocus);
	medicineList->setSelectionBehavior(QAbstractItemView::SelectRows);
	medicineList->setSelectionMode(QAbstractItemView::SingleSelection);

	medicineList->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	medicineList->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	medicineList->horizontalHeader()->setVisible(false);
	medicineList->verticalHeader()->setVisible(false);
	medicineList->horizontalHeader()->setStretchLastSection(true);

	medicineList->setColumnCount(5);
	leftLayout->addWidget(medicineList);

	QWidget* leftButtonsWidget = new QWidget;
	
	sortByNameButton = new QPushButton("Name");
	sortByPriceButton = new QPushButton("Price");
	sortByProducerButton = new QPushButton("Producer");
	sortBySubstanceButton = new QPushButton("Active substance");
	QLabel* sortSeparator = new QLabel("|");
	ascendingButton = new QPushButton("Ascending");
	descendingButton = new QPushButton("Descending");

	sortByNameButton->setEnabled(false);
	ascendingButton->setEnabled(false);

	QHBoxLayout* leftButtonsLayout = new QHBoxLayout;
	leftButtonsWidget->setLayout(leftButtonsLayout);

	leftButtonsLayout->addWidget(sortByNameButton);
	leftButtonsLayout->addWidget(sortByPriceButton);
	leftButtonsLayout->addWidget(sortByProducerButton);
	leftButtonsLayout->addWidget(sortBySubstanceButton);
	leftButtonsLayout->addWidget(sortSeparator);
	leftButtonsLayout->addWidget(ascendingButton);
	leftButtonsLayout->addWidget(descendingButton);

	leftLayout->addWidget(leftButtonsWidget);

	sortButton = new QPushButton("Sort the Medicine List");
	leftLayout->addWidget(sortButton);

	mainLayout->addWidget(leftWidget);

	QWidget* middleWidget = new QWidget;
	QVBoxLayout* middleLayout = new QVBoxLayout;
	middleWidget->setLayout(middleLayout);

	QWidget* detailsWidget = new QWidget;
	QFormLayout* detailsForm = new QFormLayout;
	detailsWidget->setLayout(detailsForm);

	nameText = new QLineEdit;
	detailsForm->addRow(new QLabel("Name:"), nameText);
	priceText = new QLineEdit;
	detailsForm->addRow(new QLabel("Price:"), priceText);
	producerText = new QLineEdit;
	detailsForm->addRow(new QLabel("Producer:"), producerText);
	substanceText = new QLineEdit;
	detailsForm->addRow(new QLabel("Active substance:"), substanceText);

	middleLayout->addWidget(detailsWidget);

	QWidget* medicineWidget = new QWidget;
	QHBoxLayout* medicineLayout = new QHBoxLayout;
	medicineWidget->setLayout(medicineLayout);

	addButton = new QPushButton("Add");
	removeButton = new QPushButton("Remove");
	updateButton = new QPushButton("Update");

	medicineLayout->addWidget(addButton);
	medicineLayout->addWidget(removeButton);
	medicineLayout->addWidget(updateButton);

	middleLayout->addWidget(medicineWidget);

	recipeButton = new QPushButton("Add to Prescription");
	middleLayout->addWidget(recipeButton);

	QWidget* findWidget = new QWidget;
	QFormLayout* findLayout = new QFormLayout;
	findWidget->setLayout(findLayout);

	toFindText = new QLineEdit;
	findLayout->addRow(new QLabel("Substring to find:"), toFindText);
	findButton = new QPushButton("Find");
	findLayout->addWidget(findButton);

	middleLayout->addWidget(findWidget);

	QWidget* filterWidget = new QWidget;
	QFormLayout* filterLayout = new QFormLayout;
	filterWidget->setLayout(filterLayout);

	minimumPrice = new QLineEdit;
	filterLayout->addRow(new QLabel("Minimum price:  "), minimumPrice);
	maximumPrice = new QLineEdit;
	filterLayout->addRow(new QLabel("Maximum price:  "), maximumPrice);
	filterButton = new QPushButton("Filter");
	filterLayout->addWidget(filterButton);

	middleLayout->addWidget(filterWidget);


	undoButton = new QPushButton("Undo");
	reportButton = new QPushButton("Producer Report");
	
	
	middleLayout->addStretch();
	middleLayout->addWidget(reportButton);
	middleLayout->addStretch();
	middleLayout->addWidget(undoButton);

	mainLayout->addWidget(middleWidget);

	QWidget* rightWidget = new QWidget;
	QVBoxLayout* rightLayout = new QVBoxLayout;
	rightWidget->setLayout(rightLayout);

	QLabel* prescriptionTitle = new QLabel("Medicine Prescription");
	prescriptionTitle->setStyleSheet("font: bold 30px");
	prescriptionTitle->setAlignment(Qt::AlignRight);

	rightLayout->addWidget(prescriptionTitle);

	clearButton = new QPushButton("Clear Prescription");
	rightLayout->addWidget(clearButton);

	medicineRecipe = new QListWidget;

	medicineRecipe->setMinimumWidth(550);

	medicineRecipe->setEditTriggers(QAbstractItemView::NoEditTriggers);
	medicineRecipe->setFocusPolicy(Qt::NoFocus);
	medicineRecipe->setSelectionMode(QAbstractItemView::NoSelection);

	// medicineRecipe->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	// medicineRecipe->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	// medicineRecipe->horizontalHeader()->setVisible(false);
	// medicineRecipe->verticalHeader()->setVisible(false);
	// medicineRecipe->horizontalHeader()->setStretchLastSection(true);

	// medicineRecipe->setColumnCount(5);
	//rightLayout->addWidget(medicineRecipe);

	openRecipeButton = new QPushButton("\n\nOpen The\nCrud Recipe\n\n");
	rightLayout->addWidget(openRecipeButton);
	openRecipeReadOnlyButton = new QPushButton("\n\nOpen The\nRead Only Recipe\n\n");
	rightLayout->addWidget(openRecipeReadOnlyButton);

	QWidget* rightButtonsWidget = new QWidget;
	QHBoxLayout* rightButtonsLayout = new QHBoxLayout;
	rightButtonsWidget->setLayout(rightButtonsLayout);

	//rightButtonsLayout->addStretch();

	QWidget* generateWidget = new QWidget;
	QFormLayout* generateFormLayout = new QFormLayout;
	generateWidget->setLayout(generateFormLayout);

	generationsNumber = new QLineEdit;
	generateButton = new QPushButton("Generate Medicines");
	generateFormLayout->addRow(generationsNumber);
	generateFormLayout->addWidget(generateButton);

	rightButtonsLayout->addWidget(generateWidget);
	//rightButtonsLayout->addStretch();


	QWidget* exportWidget = new QWidget;
	QFormLayout* exportFormLayout = new QFormLayout;
	exportWidget->setLayout(exportFormLayout);


	exportFile = new QLineEdit;
	htmlButton = new QPushButton("Export as HTML");
	csvButton = new QPushButton("Export as CSV");
	exportFormLayout->addRow(exportFile);
	exportFormLayout->addWidget(htmlButton);
	exportFormLayout->addWidget(csvButton);

	rightButtonsLayout->addWidget(exportWidget);

	rightLayout->addWidget(rightButtonsWidget);

	mainLayout->addWidget(rightWidget);

	allScreen->addWidget(mainWidget);
	
	dynamicWidget->setLayout(dynamicLayout);
	QLabel* dynamicWidgetTitle = new QLabel("Producers List |");
	dynamicWidgetTitle->setStyleSheet("font: bold 17px");
	dynamicWidgetTitle->setAlignment(Qt::AlignRight);
	dynamicLayout->addWidget(dynamicWidgetTitle);

	generateProducerButtons();

	allScreen->addWidget(dynamicWidget);
}


void PharmacyGUI::newProducerButton(const string& producer) {
	if (producerButton[producer] == NULL) {
		producerButton[producer] = new QPushButton(QString::fromStdString(producer));
		producerButonsLayout->addWidget(producerButton[producer]);
		dynamicLayout->addWidget(producerButton[producer]);
	}
	QObject::connect(producerButton[producer], &QPushButton::clicked, [&, producer]() {
		auto map = service.producerReportMap();
		if (map[producer].size() == 0) {
			producerButton[producer]->close();
			producerButton[producer] = NULL;
		}
		reloadList(map[producer]);
		producerButton[producer]->setEnabled(false);
		});

}


void PharmacyGUI::generateProducerButtons() {
	const auto& producerMap = service.producerReportMap();
	for (const auto& pair : producerMap) {
		newProducerButton(pair.first);
	}
}

void PharmacyGUI::deleteProducerButtons() {
	for (const auto& button : producerButton) {
		if (producerButton[button.first]) {
			delete button.second;
			producerButton[button.first] = NULL;
		}
		//producerButton.erase(button.first);
	}
}

void PharmacyGUI::reloadProducerButtons() {
	deleteProducerButtons();
	generateProducerButtons();
	enableProducerButtons();
}

void PharmacyGUI::enableProducerButtons() {
	for (const auto& button : producerButton) {
		if (producerButton[button.first]) {
			button.second->setEnabled(true);
		}
	}
}


void PharmacyGUI::connectSignalsSlots() {
	QObject::connect(addButton, &QPushButton::clicked, this, &PharmacyGUI::addMedicine);
	QObject::connect(removeButton, &QPushButton::clicked, this, &PharmacyGUI::removeMedicine);
	QObject::connect(updateButton, &QPushButton::clicked, this, &PharmacyGUI::updateMedicine);
	QObject::connect(findButton, &QPushButton::clicked, [&]() {
		string substring = toFindText->text().toStdString();
		reloadList(service.findMedicineList(substring));
		});
	QObject::connect(filterButton, &QPushButton::clicked, [&]() {
		double minimum;
		if (minimumPrice->text().toStdString() != "") {
			minimum = minimumPrice->text().toDouble();
		}
		else {
			minimum = 0;
		}
		double maximum;
		if (maximumPrice->text().toStdString() != "") {
			maximum = maximumPrice->text().toDouble();
		}
		else {
			maximum = 10000;
		}
		reloadList(service.filterMedicinePriceRange(minimum, maximum));
		});
	QObject::connect(undoButton, &QPushButton::clicked, [&]() {
		try {
			service.undoLastOperation();
			reloadList(repository.getMedicineList());
		}
		catch (const PharmacyException& exception) {
			QMessageBox::critical(this, "Undo Error", QString::fromStdString(exception.what()));
		}
		});
	QObject::connect(sortByNameButton, &QPushButton::clicked, [&]() {
		sortingFunction = sortByNameLambda;
		sortByNameButton->setEnabled(false);
		sortByPriceButton->setEnabled(true);
		sortByProducerButton->setEnabled(true);
		sortBySubstanceButton->setEnabled(true);
		});
	QObject::connect(sortByPriceButton, &QPushButton::clicked, [&]() {
		sortingFunction = sortByPriceLambda;
		sortByNameButton->setEnabled(true);
		sortByPriceButton->setEnabled(false);
		sortByProducerButton->setEnabled(true);
		sortBySubstanceButton->setEnabled(true);
		});
	QObject::connect(sortByProducerButton, &QPushButton::clicked, [&]() {
		sortingFunction = sortByProducerLambda;
		sortByNameButton->setEnabled(true);
		sortByPriceButton->setEnabled(true);
		sortByProducerButton->setEnabled(false);
		sortBySubstanceButton->setEnabled(true);
		});
	QObject::connect(sortBySubstanceButton, &QPushButton::clicked, [&]() {
		sortingFunction = sortBySubstanceLambda;
		sortByNameButton->setEnabled(true);
		sortByPriceButton->setEnabled(true);
		sortByProducerButton->setEnabled(true);
		sortBySubstanceButton->setEnabled(false);
		});
	QObject::connect(ascendingButton, &QPushButton::clicked, [&]() {
		sortingType = false;
		ascendingButton->setEnabled(false);
		descendingButton->setEnabled(true);
		});
	QObject::connect(descendingButton, &QPushButton::clicked, [&]() {
		sortingType = true;
		ascendingButton->setEnabled(true);
		descendingButton->setEnabled(false);
		});
	QObject::connect(sortButton, &QPushButton::clicked, [&]() {
		reloadList(service.sortMedicineList(sortingFunction, sortingType));
		QMessageBox::information(this, "Sorting information", QString::fromStdString("The list was successful sorted"));
		});
	QObject::connect(resetButton, &QPushButton::clicked, [&]() {
		reloadList(repository.getMedicineList());
		});
	QObject::connect(medicineList->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
		auto selected = medicineList->selectedItems();
		if (selected.isEmpty()) {
			nameText->setText("");
			priceText->setText("");
			producerText->setText("");
			substanceText->setText("");
		}
		else {
			if (selected.at(0)->text().toStdString() == "") {
				nameText->setText("");
				priceText->setText("");
				producerText->setText("");
				substanceText->setText("");
			}
			else {
				nameText->setText(selected.at(1)->text());
				priceText->setText(QString::fromStdString(selected.at(2)->text().toStdString().erase(0, 1)));
				producerText->setText(selected.at(3)->text());
				substanceText->setText(selected.at(4)->text());
			}
		}
		});
	QObject::connect(reportButton, &QPushButton::clicked, this, &PharmacyGUI::producerReport);

	QObject::connect(openRecipeButton, &QPushButton::clicked, this, [&]() {
		RecipeCrudGUI* w = new RecipeCrudGUI{ service };
		addObserver(w);
		w->addObserver((Observer*) this);
		w->show();
		});

	QObject::connect(openRecipeReadOnlyButton, &QPushButton::clicked, this, [&]() {
		RecipeReadOnlyGUI* w = new RecipeReadOnlyGUI{ service };
		addObserver(w);
		w->show();
		});

	QObject::connect(recipeButton, &QPushButton::clicked, [&]() {
		try {
			Medicine fromGUI = getMedicineFromGUI();
			unsigned position = repository.findMedicine(fromGUI);
			if (position == repository.getLength()) {
				QMessageBox::critical(this, "Prescription Error", QString::fromStdString("There is no medicine with the given informations!"));
				return;
			}
			service.addMedicineToRecipe(position);
			notify();
		}
		catch (...) {
			QMessageBox::critical(this, "Prescription Error", QString::fromStdString("There is no medicine with the given informations!"));
			return;
		}
		});
	QObject::connect(generateButton, &QPushButton::clicked, [&]() {
		unsigned no = generationsNumber->text().toUInt();
		service.generateMedicinesToTheRecipe(no);
		notify();
		});
	QObject::connect(clearButton, &QPushButton::clicked, [&]() {
		service.resetRecipe();
		notify();
		});
	QObject::connect(htmlButton, &QPushButton::clicked, [&]() {
		string fileName = "Exports/" + exportFile->text().toStdString();
		recipe.exportRecipe(fileName, "html");
		QMessageBox::information(this, "Export Success", QString::fromStdString("The export was done succesfully!"));
		});
	QObject::connect(csvButton, &QPushButton::clicked, [&]() {
		string fileName = "Exports/" + exportFile->text().toStdString();
		recipe.exportRecipe(fileName, "csv");
		QMessageBox::information(this, "Export Success", QString::fromStdString("The export was done succesfully!"));
		});
}


void PharmacyGUI::reloadList(const vector<Medicine>& medicines) {
	reloadProducerButtons();
	medicineList->clear();
	medicineList->setRowCount(medicines.size() + 1);
	QTableWidgetItem* item;

	item = new QTableWidgetItem(QString::fromStdString(""));
	item->setBackground(QBrush{ Qt::black });
	medicineList->setItem(0, 0, item);
	item = new QTableWidgetItem(QString::fromStdString("Name"));
	item->setBackground(QBrush{ Qt::black });
	item->setForeground(Qt::white);
	medicineList->setItem(0, 1, item);
	item = new QTableWidgetItem(QString::fromStdString("Price"));
	item->setBackground(QBrush{ Qt::black });
	item->setForeground(Qt::white);
	medicineList->setItem(0, 2, item);
	item = new QTableWidgetItem(QString::fromStdString("Producer"));
	item->setBackground(QBrush{ Qt::black });
	item->setForeground(Qt::white);
	medicineList->setItem(0, 3, item);
	item = new QTableWidgetItem(QString::fromStdString("Active Substance"));
	item->setBackground(QBrush{ Qt::black });
	item->setForeground(Qt::white);
	medicineList->setItem(0, 4, item);

	vector<Qt::GlobalColor> colors = { Qt::red, Qt::yellow, Qt::green, Qt::cyan, Qt::blue, Qt::magenta };
	vector<Qt::GlobalColor> darkColors = { Qt::darkRed, Qt::darkYellow, Qt::darkGreen, Qt::darkCyan, Qt::darkBlue, Qt::darkMagenta };

	unsigned index = 1;
	for (const auto& medicine : medicines) {
		item = new QTableWidgetItem(QString::number(index - 1));
		item->setBackground(Qt::black);
		item->setForeground(QBrush{ colors[(index - 1) % colors.size()]});
		medicineList->setItem(index, 0, item);
		item = new QTableWidgetItem(QString::fromStdString(medicine.getName()));
		item->setForeground(QBrush{ darkColors[(index - 1) % darkColors.size()] });
		medicineList->setItem(index, 1, item);
		string priceString;
		if (int(medicine.getPrice() * 100) % 100 == 0) {
			priceString = "$" + std::to_string(int(medicine.getPrice())) + ".00";
		}
		else if (int(medicine.getPrice() * 100) % 100 < 10) {
			priceString = "$" + std::to_string(int(medicine.getPrice())) + ".0" + std::to_string(int(medicine.getPrice() * 100) % 100);
		}
		else {
			priceString = "$" + std::to_string(int(medicine.getPrice())) + "." + std::to_string(int(medicine.getPrice() * 100) % 100);
		}
		item = new QTableWidgetItem(QString::fromStdString(priceString));
		item->setForeground(QBrush{ darkColors[(index - 1) % darkColors.size()] });
		medicineList->setItem(index, 2, item);
		item = new QTableWidgetItem(QString::fromStdString(medicine.getProducer()));
		item->setForeground(QBrush{ darkColors[(index - 1) % darkColors.size()] });
		medicineList->setItem(index, 3, item);
		item = new QTableWidgetItem(QString::fromStdString(medicine.getSubstance()));
		item->setForeground(QBrush{ darkColors[(index - 1) % darkColors.size()] });
		medicineList->setItem(index, 4, item);
		++index;
	}
}

Medicine PharmacyGUI::getMedicineFromGUI() {
	string name = nameText->text().toStdString();
	validator.validateMedicineName(name);
	double price = priceText->text().toDouble();
	validator.validateMedicinePrice(price);
	string producer = producerText->text().toStdString();
	validator.validateMedicineProducer(producer);
	string substance = substanceText->text().toStdString();
	validator.validateMedicineSubstance(substance);
	return Medicine(name, price, producer, substance);
}

void PharmacyGUI::addMedicine() {
	try {
		Medicine medicineFromGUI = getMedicineFromGUI();
		service.addMedicine(medicineFromGUI.getName(), medicineFromGUI.getPrice(), medicineFromGUI.getProducer(), medicineFromGUI.getSubstance());
		reloadList(repository.getMedicineList());
		reloadProducerButtons();
	}
	catch (const PharmacyException& exception) {
		QMessageBox::critical(this, "Adding Error", QString::fromStdString(exception.what()));
	}
}

void PharmacyGUI::removeMedicine() {
	try {
		Medicine medicineFromGUI = getMedicineFromGUI();
		unsigned position = repository.findMedicine(medicineFromGUI);
		service.deleteMedicine(position);
		reloadList(repository.getMedicineList());
		reloadProducerButtons();
	}
	catch (const PharmacyException& exception) {
		QMessageBox::critical(this, "Removing Error", QString::fromStdString("There is no medicine with the given informations!"));
	}
}

void PharmacyGUI::updateMedicine() {
	Medicine medicineFromGUI;
	unsigned position;
	try {
		medicineFromGUI = getMedicineFromGUI();
		position = repository.findMedicine(medicineFromGUI);
	}
	catch (const PharmacyException& exception) {
		QMessageBox::critical(this, "Updating Error", QString::fromStdString("There is no medicine with the given informations!"));
		return;
	}

	if (position == repository.getLength()) {
		QMessageBox::critical(this, "Updating Error", QString::fromStdString("There is no medicine with the given informations!"));
		return;
	}

	QWidget* updateWidget = new QWidget;
	updateWidget->setStyleSheet("font: bold 14px");
	QFormLayout* updateFormLayout = new QFormLayout;
	updateWidget->setLayout(updateFormLayout);

	QLineEdit* updatedName = new QLineEdit;
	const string oldName = "Name (from " + medicineFromGUI.getName() + ")";
	updateFormLayout->addRow(new QLabel(QString::fromStdString(oldName)), updatedName);

	QLineEdit* updatedPrice = new QLineEdit;
	const string oldPrice = "Price (from $" + QString::number(medicineFromGUI.getPrice()).toStdString() + ")";
	updateFormLayout->addRow(new QLabel(QString::fromStdString(oldPrice)), updatedPrice);

	QLineEdit* updatedProducer = new QLineEdit;
	const string oldProducer = "Producer (from " + medicineFromGUI.getProducer() + ")";
	updateFormLayout->addRow(new QLabel(QString::fromStdString(oldProducer)), updatedProducer);

	QLineEdit* updatedSubstance = new QLineEdit;
	const string oldSubstance = "Active Substance (from " + medicineFromGUI.getSubstance() + ")";
	updateFormLayout->addRow(new QLabel(QString::fromStdString(oldSubstance)), updatedSubstance);

	QPushButton* update = new QPushButton("Update");
	updateFormLayout->addWidget(update);

	updateWidget->show();

	QObject::connect(update, &QPushButton::clicked, this, [&, updateWidget, position, updatedName, updatedPrice, updatedProducer, updatedSubstance]() {
		try {
			string name = updatedName->text().toStdString();
			validator.validateMedicineName(name);
			double price = updatedPrice->text().toDouble();
			validator.validateMedicinePrice(price);
			string producer = updatedProducer->text().toStdString();
			validator.validateMedicineProducer(producer);
			string substance = updatedSubstance->text().toStdString();
			validator.validateMedicineSubstance(substance);
			service.updateMedicine(position, name, price, producer, substance);
			reloadList(repository.getMedicineList());
			reloadProducerButtons();
			updateWidget->close();
		}
		catch (const PharmacyException& exception) {
			QMessageBox::critical(this, "Updating Error", QString::fromStdString(exception.what()));
			updateWidget->close();
		}
		});
}

void PharmacyGUI::reloadRecipe(const vector<Medicine>& medicines) {
	medicineRecipe->clear();
	//medicineRecipe->setRowCount(medicines.size() + 1);
	QListWidgetItem* item;

	item = new QListWidgetItem(QString::fromStdString("Name"));
	item->setBackground(QBrush{ Qt::black });
	item->setForeground(Qt::white);
	medicineRecipe->addItem(item);

	vector<Qt::GlobalColor> colors = { Qt::red, Qt::yellow, Qt::green, Qt::cyan, Qt::blue, Qt::magenta };
	vector<Qt::GlobalColor> darkColors = { Qt::darkRed, Qt::darkYellow, Qt::darkGreen, Qt::darkCyan, Qt::darkBlue, Qt::darkMagenta };

	unsigned index = 1;
	for (const auto& medicine : medicines) {
		item = new QListWidgetItem(QString::fromStdString(medicine.getName()));
		item->setForeground(QBrush{ darkColors[(index - 1) % colors.size()] });
		medicineRecipe->addItem(item);
		index++;
	}
}

void PharmacyGUI::producerReport() {
	QTableWidget* producerMapWidget = new QTableWidget;

	producerMapWidget->setStyleSheet("font: bold 14px");
	producerMapWidget->setMinimumWidth(400);

	producerMapWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	producerMapWidget->setFocusPolicy(Qt::NoFocus);
	producerMapWidget->setSelectionMode(QAbstractItemView::NoSelection);

	producerMapWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	producerMapWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	producerMapWidget->horizontalHeader()->setVisible(false);
	producerMapWidget->verticalHeader()->setVisible(false);
	producerMapWidget->horizontalHeader()->setStretchLastSection(true);

	producerMapWidget->setColumnCount(4);

	const auto& producerMap = service.producerReportMap();

	producerMapWidget->setRowCount(producerMap.size() + 1);
	QTableWidgetItem* item;

	item = new QTableWidgetItem(QString::fromStdString(""));
	item->setBackground(QBrush{ Qt::black });
	producerMapWidget->setItem(0, 0, item);
	item = new QTableWidgetItem(QString::fromStdString("Producer"));
	item->setBackground(QBrush{ Qt::black });
	item->setForeground(Qt::white);
	producerMapWidget->setItem(0, 1, item);
	item = new QTableWidgetItem(QString::fromStdString("Occurrences"));
	item->setBackground(QBrush{ Qt::black });
	item->setForeground(Qt::white);
	producerMapWidget->setItem(0, 2, item);
	item = new QTableWidgetItem(QString::fromStdString("Medicines"));
	item->setBackground(QBrush{ Qt::black });
	item->setForeground(Qt::white);
	producerMapWidget->setItem(0, 3, item);

	vector<Qt::GlobalColor> colors = { Qt::red, Qt::yellow, Qt::green, Qt::cyan, Qt::blue, Qt::magenta };
	vector<Qt::GlobalColor> darkColors = { Qt::darkRed, Qt::darkYellow, Qt::darkGreen, Qt::darkCyan, Qt::darkBlue, Qt::darkMagenta };

	unsigned index = 1;
	for (const auto& pair : producerMap) {
		item = new QTableWidgetItem(QString::number(index - 1));
		item->setBackground(Qt::black);
		item->setForeground(QBrush{ colors[(index - 1) % colors.size()] });
		producerMapWidget->setItem(index, 0, item);
		item = new QTableWidgetItem(QString::fromStdString(pair.first));
		item->setForeground(QBrush{ darkColors[(index - 1) % darkColors.size()] });
		producerMapWidget->setItem(index, 1, item);
		item = new QTableWidgetItem(QString::number(pair.second.size()));
		item->setForeground(QBrush{ darkColors[(index - 1) % darkColors.size()] });
		producerMapWidget->setItem(index, 2, item);

		string names;

		for (const auto& medicine : pair.second) {
			names += medicine.getName() + '\n';
		}

		names.erase(names.end() - 1, names.end());

		item = new QTableWidgetItem(QString::fromStdString(names));
		item->setForeground(QBrush{ darkColors[(index - 1) % darkColors.size()] });
		producerMapWidget->setItem(index, 3, item);

		index++;
	}

	producerMapWidget->show();
};
