#include "GUI.h"

void GUI::buildGUI() {
	setStyleSheet("font: bold 16px");
	setLayout(mainL);
	setMinimumHeight(550);

	mainL->addLayout(firstL);
	firstL->addLayout(lstL);
	lstL->addWidget(lstW);
	lstW->setModel(lstV);
	lstW->setSelectionMode(QAbstractItemView::SingleSelection);
	lstW->setSelectionBehavior(QAbstractItemView::SelectRows);
	lstW->setEditTriggers(QAbstractItemView::NoEditTriggers);
	lstW->setFocusPolicy(Qt::NoFocus);
	lstW->setMinimumWidth(530);
	lstW->setMaximumHeight(300);
	lstW->setMinimumHeight(300);
	lstW->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	lstW->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	lstW->horizontalHeader()->setVisible(false);
	lstW->verticalHeader()->setVisible(false);
	lstL->addStretch();

	firstL->addStretch();
	firstL->addLayout(rankLE);
	numeTxt->setText("Numele melodiei selectate: ");
	rankTxt->setText("Noul rank al melodiei: -");
	rankS->setRange(0, 10);
	rankS->setTickInterval(1);
	rankS->setTickPosition(QSlider::TicksRight);

	//numeLE->setEnabled(false);

	rankLE->addWidget(numeTxt);
	rankLE->addWidget(numeLE);
	rankLE->addWidget(rankTxt);
	rankLE->addWidget(rankS);
	rankLE->addWidget(rankBtn);
	rankLE->addWidget(delBtn);
	rankLE->addStretch();
	

	mainL->addLayout(secondL);
	secondL->addStretch();
	//pntW->show();
	//secondL->addWidget(pntW);
}

void GUI::connectSignals() {
	QObject::connect(rankS, &QSlider::valueChanged, [&]() {
		int x = rankS->value();
		rankTxt->setText(QString::fromStdString("Noul rank al melodiei: " + to_string(x)));
		});
	QObject::connect(lstW->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
		auto selected =  lstW->selectionModel()->selectedIndexes();
		if (selected.isEmpty()) {
			numeLE->setText("");
			rankTxt->setText("Noul rank al melodiei: -");
		}
		else {
			int i = selected.at(0).row();
			if (i == 0) {
				numeLE->setText("");
				rankTxt->setText("Noul rank al melodiei: -");
			}
			else {
				auto& m = s.getList().at(i - 1);
				numeLE->setText(QString::fromStdString(m.getTitlu()));
				rankTxt->setText(QString::fromStdString("Noul rank al melodiei: " + to_string(m.getRank())));
				rankS->setValue(m.getRank());
			}
		}
		});
	QObject::connect(rankBtn, &QPushButton::clicked, [&]() {
		try {
			int x = rankS->value();
			auto selected = lstW->selectionModel()->selectedIndexes();
			if (selected.isEmpty()) {
				QMessageBox::critical(this, "Eroare update", "Trebuie sa selectezi o melodie!");
			}
			else {
				int i = selected.at(0).row();
				if (i == 0) {
					QMessageBox::critical(this, "Eroare update", "Trebuie sa selectezi o melodie!");
				}
				else {
					string newTitle = numeLE->text().toStdString();
					s.updateTitleRank(i - 1, newTitle, x);
					QMessageBox::information(this, "Update", "Actualizarea a avut loc cu succes!");
				}
			}
		}
		catch (exception& e) {
			QMessageBox::critical(this, "Eroare modificare rank", e.what());
		}
		
		});
	QObject::connect(delBtn, &QPushButton::clicked, [&]() {
		try {
			auto selected = lstW->selectionModel()->selectedIndexes();
			if (selected.isEmpty()) {
				QMessageBox::critical(this, "Eroare stergere melodie", "Trebuie sa selectezi o melodie!");
			}
			else {
				int i = selected.at(0).row();
				if (i == 0) {
					QMessageBox::critical(this, "Eroare stergere melodie", "Trebuie sa selectezi o melodie!");
				}
				else {
					s.deleteMusic(i - 1);
					QMessageBox::information(this, "Stergere melodie", "Melodia a fost stearsa cu succes!");
				}
			}
		}
		catch (exception& e) {
			QMessageBox::critical(this, "Eroare stergere melodie", e.what());
			return;
		}
		});

}