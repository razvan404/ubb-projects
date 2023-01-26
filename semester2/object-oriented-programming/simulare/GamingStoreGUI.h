#pragma once
#include "Service.h"
#include <qwidget.h>
#include <qlayout.h>
#include <qtablewidget.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qheaderview.h>

class GUI : public QWidget {
private:
	Serv& serv;

	QHBoxLayout* mainL = new QHBoxLayout;

	QVBoxLayout* listL = new QVBoxLayout;
	QTableWidget* listW = new QTableWidget;
	QLabel* recomW = new QLabel;

	QVBoxLayout* btnL = new QVBoxLayout;
	QPushButton* sortBtn = new QPushButton("Sortare Pret");
	QPushButton* filtBtn = new QPushButton("Jocuri recomandate\npentru copii");
	QPushButton* clrBtn = new QPushButton("Refresh");

	void buildGUI();
	void connect();
	void reloadList(vector<Joc>& list);
public:
	GUI(Serv& serv)
		: serv{ serv } {
		buildGUI();
		connect();
		reloadList(serv.getList());
	}
};