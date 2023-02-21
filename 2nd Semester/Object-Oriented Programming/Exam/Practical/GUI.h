#pragma once
#include "Serv.h"
#include "QMyView.h"
#include <qwidget.h>
#include <qlayout.h>
#include <qtableview.h>
#include <qformlayout.h>
#include <qslider.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qheaderview.h>
#include <qmessagebox.h>
#include <qpainter.h>
#include <qlineedit.h>

class GUI : public QWidget, public Observer {
	Serv& s;
	vector<Qt::GlobalColor> colors = { Qt::red, Qt::yellow, Qt::green, Qt::cyan, Qt::blue, Qt::magenta };
	vector<Qt::GlobalColor> darkColors = { Qt::darkRed, Qt::darkYellow, Qt::darkGreen, Qt::darkCyan, Qt::darkBlue, Qt::darkMagenta };

	QVBoxLayout* mainL = new QVBoxLayout;
	QHBoxLayout* firstL = new QHBoxLayout;
	QVBoxLayout* lstL = new QVBoxLayout;
	QTableView* lstW = new QTableView;
	QMyView* lstV = new QMyView{ s };

	QVBoxLayout* rankLE = new QVBoxLayout;
	QSlider* rankS = new QSlider;
	QLabel* numeTxt = new QLabel;
	QLineEdit* numeLE = new QLineEdit;
	QLabel* rankTxt = new QLabel;
	QPushButton* rankBtn = new QPushButton("\nUpdate\n");

	QPushButton* delBtn = new QPushButton("\nDelete melody\n");

	QHBoxLayout* secondL = new QHBoxLayout;
	//QMyPainter* pntW = new QMyPainter{ s };

	void buildGUI();
	void connectSignals();

public:
	GUI(Serv& s) : s{ s } {
		s.addObserver(this);
		buildGUI();
		connectSignals();
	}
	void update() override {
		this->repaint();
	}
	void paintEvent(QPaintEvent* ev) override {
		QPainter painter(this);

		int x = 0, y = 320;

		for (int i = 0; i < 11; ++i) {
			painter.fillRect(x, y - 2, s.ranks[i] * 30 + 2, 14, darkColors[i % darkColors.size()]);
			painter.fillRect(x + 2, y, s.ranks[i] * 30 - 2, 10, colors[i % colors.size()]);
			y += 20;
		}
	}
};