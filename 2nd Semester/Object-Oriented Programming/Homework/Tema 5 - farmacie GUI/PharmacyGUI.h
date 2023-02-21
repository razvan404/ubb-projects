#pragma once
#include "PharmacyService.h"
#include "Validator.h"
#include "Medicine.h"
#include "RecipeGUI.h"

#include "PharmacyService.h"
#include "Observer.hpp"
#include <QLabel.h>
#include <QLineEdit.h>
#include <QPushButton.h>
#include <QListWidget.h>
#include <QWidget.h>
#include <QBoxLayout.h>
#include <QFormLayout.h>
#include <QMessageBox.h>
#include <QTableWidget.h>
#include <QHeaderView.h>
#include <QCheckBox.h>


class PharmacyGUI : public QWidget, Observable, Observer {
	friend class RecipeGUI;
private:
	Validator validator;
	MedicineListRepository& repository;
	MedicineRecipeRepository recipe;
	PharmacyService service;

	bool sortingType = false;
	bool (*sortingFunction)(const Medicine& medicine, const Medicine& other) = sortByNameLambda;
	string exportOption = "html";

	QVBoxLayout* allScreen = new QVBoxLayout;
	QHBoxLayout* mainLayout = new QHBoxLayout;

	QWidget* dynamicWidget = new QWidget;
	QHBoxLayout* dynamicLayout = new QHBoxLayout;
	
	QTableWidget* medicineList;
	QListWidget* medicineRecipe;

	QPushButton* addButton;
	QPushButton* removeButton;
	QPushButton* updateButton;
	QPushButton* findButton;
	QPushButton* filterButton;

	QLineEdit* nameText;
	QLineEdit* priceText;
	QLineEdit* producerText;
	QLineEdit* substanceText;

	QLineEdit* toFindText;
	QLineEdit* minimumPrice;
	QLineEdit* maximumPrice;

	QLineEdit* generationsNumber;
	QLineEdit* exportFile;

	QPushButton* sortByNameButton;
	QPushButton* sortByPriceButton;
	QPushButton* sortByProducerButton;
	QPushButton* sortBySubstanceButton;
	QPushButton* ascendingButton;
	QPushButton* descendingButton;
	QPushButton* sortButton;
	QPushButton* resetButton;

	QPushButton* openRecipeButton;
	QPushButton* openRecipeReadOnlyButton;

	QPushButton* generateButton;
	QPushButton* clearButton;
	QPushButton* htmlButton;
	QPushButton* csvButton;
	QPushButton* exportButton;

	map<string, QPushButton*> producerButton;

	QPushButton* recipeButton;
	QPushButton* undoButton;
	QPushButton* reportButton;

	void populateMedicineList();
	// Function to assemble the GUI
	void buildGUI();
	// Link signals and slots to define the behavior of the GUI
	void connectSignalsSlots();
	// Reloads the list of the medicines on the GUI
	void reloadList(const vector<Medicine>& medicines);
	// Reloads the prescriptions of the medicines on the GUI
	void reloadRecipe(const vector<Medicine>& medicines);

	void update() override {
		reloadList(repository.getMedicineList());
		reloadRecipe(recipe.getMedicineRecipe());
		notify();
	}

	Medicine getMedicineFromGUI();
	void addMedicine();
	void removeMedicine();
	void updateMedicine();
	void producerReport();


	QWidget* producerButonsWidget = new QWidget;
	QVBoxLayout* producerButonsLayout = new QVBoxLayout;

	void newProducerButton(const string& producer);
	void generateProducerButtons();
	void deleteProducerButtons();
	void reloadProducerButtons();
	void enableProducerButtons();

public:
	PharmacyGUI(MedicineListRepository& input) noexcept :
		service { input, recipe },
		repository{ input } {
		setStyleSheet("font: bold 14px");
		move(this->x() + this->size().width() / 3, this->y() + this->size().height() / 2);
		populateMedicineList();
		buildGUI();
		connectSignalsSlots();
		reloadList(repository.getMedicineList());
		reloadRecipe(recipe.getMedicineRecipe());
	};
};
