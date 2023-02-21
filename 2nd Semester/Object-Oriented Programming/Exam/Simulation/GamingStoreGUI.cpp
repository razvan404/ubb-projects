#include "GamingStoreGUI.h"

void GUI::buildGUI() {
	setLayout(mainL);

	QLabel* salutW = new QLabel("Salut GIGEL!\n Bine ai venit la Gaming Store!");
	salutW->setStyleSheet("font: 18px bold");
	listL->addWidget(salutW);
	listW->setColumnCount(2);
	listW->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	listW->setSelectionBehavior(QAbstractItemView::SelectRows);
	listW->setSelectionMode(QAbstractItemView::SingleSelection);
	listW->setFocusPolicy(Qt::NoFocus);

	listW->setMinimumHeight(350);
	listW->setMaximumWidth(210);
	listL->addWidget(listW);
	listL->addWidget(recomW);

	btnL->addStretch();
	btnL->addWidget(sortBtn);
	btnL->addWidget(filtBtn);
	btnL->addWidget(clrBtn);


	mainL->addLayout(listL);
	mainL->addLayout(btnL);
}

void GUI::connect() {
	QObject::connect(listW, &QTableWidget::itemSelectionChanged, this, [&]() {
		auto sel = listW->selectedItems();
		if (!sel.isEmpty()) {
			auto selItem1 = sel.at(0);
			auto selItem2 = sel.at(1);
			string name = selItem1->text().toStdString();
			unsigned price = selItem2->text().toUInt();

			unsigned position = serv.getPos(name, price);
			if (position != -1) {
				Joc& j = serv.at(position);
				string text = "Varsta minima recomandata: " + to_string(j.getAge());
				recomW->setText(QString::fromStdString(text));
				recomW->setStyleSheet("font: 17px bold italic");
			}
			else {
				recomW->clear();
			}
			//recomW->setText(QString)
		}
		else {
			recomW->clear();
		}
	});
	QObject::connect(sortBtn, &QPushButton::pressed, this, [&]() {
			vector<Joc> vct = serv.sorteazaCresc();
			reloadList(vct);
		});
	QObject::connect(clrBtn, &QPushButton::pressed, this, [&]() {
		reloadList(serv.getList());
		});
	QObject::connect(filtBtn, &QPushButton::pressed, this, [&]() {
		vector<Joc> vct = serv.ptCopii();
		reloadList(vct);
		});
}

void GUI::reloadList(vector<Joc>& list) {
	listW->clear();
	listW->setRowCount(list.size() + 1);

	QTableWidgetItem* item;

	item = new QTableWidgetItem;
	item->setText(QString("Titlu"));
	listW->setItem(0, 0, item);

	item = new QTableWidgetItem;
	item->setText(QString("Pret"));
	listW->setItem(0, 1, item);

	unsigned pos = 1;

	for (auto& j : list) {
		Qt::GlobalColor color = Qt::white;
		if (j.getPlatforma() == "PC") {
			color = Qt::black;
		}
		else if (j.getPlatforma() == "PlayStation") {
			color = Qt::blue;
		}
		else if (j.getPlatforma() == "XBOX") {
			color = Qt::green;
		}
		else if (j.getPlatforma() == "Nintendo") {
			color = Qt::red;
		}

		item = new QTableWidgetItem;
		item->setText(QString::fromStdString(j.getTitlu()));
		item->setBackground(color);
		item->setForeground(Qt::white);
		listW->setItem(pos, 0, item);

		item = new QTableWidgetItem;
		item->setText(QString::number(j.getPret()));
		item->setBackground(color);
		item->setForeground(Qt::white);
		listW->setItem(pos, 1, item);

		++pos;
	}
}