#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Pharmacy.h"

class Pharmacy : public QMainWindow {
    Q_OBJECT

public:
    Pharmacy(QWidget *parent = Q_NULLPTR);

private:
    Ui::PharmacyClass ui;
};
