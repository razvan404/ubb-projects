#include "Simulare.h"
#include "Tests.h"
#include "GamingStoreGUI.h"
#include <QtWidgets/QApplication>

void run(int argc, char* argv[]) {
    testAll();

    QApplication a(argc, argv);
    Repo r{ "Data.txt" };
    Serv s{ r };
    GUI w{ s };
    w.show();
    a.exec();
}

int main(int argc, char *argv[]) {
    run(argc, argv);
    return EXIT_SUCCESS;
}
