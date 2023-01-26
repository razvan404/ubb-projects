#include "ExamX.h"
#include "Tests.h"
#include "GUI.h"
#include <QtWidgets/QApplication>

void run(int argc, char* argv[]) {
    QApplication a(argc, argv);
    Repo r{ "Data.txt" };
    Serv s{ r };
    GUI* g = new GUI{ s };

    g->show();

    a.exec();
}

int main(int argc, char *argv[]) {
    testAll();
    run(argc, argv);
    return EXIT_SUCCESS;
}
