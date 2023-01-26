#include "RecipeGUI.h"
#include "QRecipeList.hpp"

void RecipeCrudGUI::buildGUI() {
	setLayout(mainLayout);
	setMinimumHeight(500);

	QLabel* prescriptionTitle = new QLabel("Medicine Prescription");
	prescriptionTitle->setStyleSheet("font: bold 30px");
	prescriptionTitle->setAlignment(Qt::AlignCenter);
	
	mainLayout->addWidget(prescriptionTitle);

	clearButton = new QPushButton("Clear Prescription");
	mainLayout->addWidget(clearButton);

	medicineRecipe->setModel(medicineModel);
	mainLayout->addWidget(medicineRecipe);

	QWidget* generateWidget = new QWidget;
	QFormLayout* generateFormLayout = new QFormLayout;
	generateWidget->setLayout(generateFormLayout);


	generationsNumber = new QLineEdit;
	generateButton = new QPushButton("Generate Medicines");
	generateFormLayout->addRow(generationsNumber);
	generateFormLayout->addWidget(generateButton);

	mainLayout->addWidget(generateWidget);
}

void RecipeCrudGUI::connectSignalsSlots() {
	QObject::connect(generateButton, &QPushButton::clicked, [&]() {
		unsigned no = generationsNumber->text().toUInt();
		service.generateMedicinesToTheRecipe(no);
		reloadRecipe();
		notify();
		});
	QObject::connect(clearButton, &QPushButton::clicked, [&]() {
		service.resetRecipe();
		reloadRecipe();
		notify();
		});
}

void RecipeCrudGUI::reloadRecipe() {
	medicineModel->setMedicines(service.getRecipe());
}