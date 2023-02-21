#pragma once

#include <QAbstractItemView.h>
#include "PharmacyService.h"

class QRecipeList : public QAbstractListModel {
	vector<Medicine> medicines;
	const vector<Qt::GlobalColor> colors = { Qt::red, Qt::yellow, Qt::green, Qt::cyan, Qt::blue, Qt::magenta };
	const vector<Qt::GlobalColor> darkColors = { Qt::darkRed, Qt::darkYellow, Qt::darkGreen, Qt::darkCyan, Qt::darkBlue, Qt::darkMagenta };

public:
	QRecipeList(const vector<Medicine>& medicines)
		: medicines{ medicines } {};

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return medicines.size();
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			int ind = index.row();
			const Medicine& med = medicines.at(ind);
			return QString::fromStdString(med.getName()) + ", produced by: " + QString::fromStdString(med.getProducer());
		}
		if (role == Qt::BackgroundRole) {
			int ind = index.row();
			return QBrush{ darkColors.at(ind% darkColors.size()) };
		}
		if (role == Qt::ForegroundRole) {
			int ind = index.row();
			return QBrush{ colors.at(ind % colors.size()) };
		}
		return QVariant{};
	}

	void setMedicines(const vector<Medicine>& medicines) {
		this->medicines = medicines;
		const QModelIndex& topLeft = createIndex(0, 0);
		const QModelIndex& bottomRight = createIndex(rowCount(), 0);
		emit dataChanged(topLeft, bottomRight);
	}
};