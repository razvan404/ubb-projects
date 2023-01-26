#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ExamX.h"

class ExamX : public QMainWindow
{
    Q_OBJECT

public:
    ExamX(QWidget *parent = Q_NULLPTR);

private:
    Ui::ExamXClass ui;
};
