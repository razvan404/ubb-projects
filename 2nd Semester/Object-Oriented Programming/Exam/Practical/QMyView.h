#pragma once
#include "Observer.h"
#include "Serv.h"
#include <qtableview.h>

class QMyView : public QAbstractTableModel, public Observer {
	Serv& s;
	vector<Qt::GlobalColor> colors = { Qt::darkRed, Qt::darkYellow, Qt::darkGreen, Qt::darkCyan, Qt::darkBlue, Qt::darkMagenta };
public:
	QMyView(Serv& s) : s{ s } {
		s.addObserver(this);
		update();
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return s.getList().size() + 1;
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 5;
	}

	QVariant data(const QModelIndex& index, int role) const override {
		if (role == Qt::DisplayRole) {
			int i = index.row();
			int j = index.column();

			if (i == 0) {
				if (j == 0) {
					return QString("ID");
				}
				if (j == 1) {
					return QString("Titlu");
				}
				if (j == 2) {
					return QString("Artist");
				}
				if (j == 3) {
					return QString("Rank");
				}
				if (j == 4) {
					return QString("Same Rank");
				}
				return QString();
			}

			int poz = i - 1;
			Melodie& m = s.getList().at(poz);
			if (j == 0) {
				return QString::number(m.getID());
			}
			if (j == 1) {
				return QString::fromStdString(m.getTitlu());
			}
			if (j == 2) {
				return QString::fromStdString(m.getArtist());
			}
			if (j == 3) {
				return QString::number(m.getRank());
			}
			if (j == 4) {
				return QString::number(s.ranks[m.getRank()]);
			}

			return QString();
		}
		if (role == Qt::BackgroundRole) {
			return QBrush(Qt::white);
		}
		if (role == Qt::ForegroundRole) {
			int i = index.row();
			if (i > 0) {
				int k = i - 1;
				return QBrush(colors[k % colors.size()]);
			}
		}

		return QVariant();
	}
	void update() override {
		QModelIndex topLeft = createIndex(0, 0);
		QModelIndex bottomRight = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomRight);
		emit layoutChanged();
	}
};