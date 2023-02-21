#pragma once
#include "PharmacyService.h"
#include "Validator.h"
#include "Medicine.h"
#include "QRecipeList.hpp"

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
#include <QPainter.h>

class RecipeCrudGUI : public QWidget, public Observer, public Observable {
private:
	PharmacyService& service;

	QVBoxLayout* mainLayout = new QVBoxLayout;
	QListView* medicineRecipe = new QListView;
	QRecipeList* medicineModel;

	QPushButton* clearButton;
	QLineEdit* generationsNumber;
	QPushButton* generateButton;

	// Function to assemble the GUI
	void buildGUI();
	// Link signals and slots to define the behavior of the GUI
	void connectSignalsSlots();
	// Reloads the prescriptions of the medicines on the GUI
	void reloadRecipe();

	void update() override {
		reloadRecipe();
	}

public:
	RecipeCrudGUI(PharmacyService& input) noexcept :
		service{ input } {
		setStyleSheet("font: bold 14px");
		move(this->x() + this->size().width() / 3, this->y() + this->size().height() / 2);
		medicineModel = new QRecipeList{ service.getRecipe() };
		buildGUI();
		connectSignalsSlots();
		reloadRecipe();
	};
};


class RecipeReadOnlyGUI : public QWidget, public Observer {
private:
	PharmacyService& service;
	const int CONT_HEIGHT = 110;
	const int CONT_WIDTH = 15;
	const int MIN_HEIGHT = 550;
	const int MAX_WIDTH = 1000;

public:
	RecipeReadOnlyGUI(PharmacyService& input)
		: service{ input } {
		buildGUI();
	}
	void buildGUI() {
		setMinimumHeight(MIN_HEIGHT);
		setMinimumWidth(MAX_WIDTH);
		setMaximumWidth(MAX_WIDTH);
	}
	void update() override {
		this->repaint();
	}

	void paintEvent(QPaintEvent* ev) override {
		QPainter painter(this);
		vector<Qt::GlobalColor> colors = { Qt::red, Qt::yellow, Qt::green, Qt::cyan, Qt::blue, Qt::magenta };
		int x = 5;
		int y = 5;
		unsigned index = 0;
		for (auto& medicine : service.getRecipe()) {
			int height = medicine.getPrice() * 10;
			QColor color = colors[(index % colors.size())];
			painter.fillRect(x, y + (CONT_HEIGHT - height) / 2, CONT_WIDTH, height, color);
			index++;
			x += CONT_WIDTH + 5;
			if (x > MAX_WIDTH) {
				y += CONT_HEIGHT;
				x = 5;
			}
		}
	}
};