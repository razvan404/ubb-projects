#include "Pharmacy.h"
#include "Tests.h"
#include <QtWidgets/QApplication>
#include "PharmacyGUI.h"

void run(int argc, char* argv[]) {
    Tests T;
    T.runAllTests();
    MedicineListRepository medicineListRepository;

    QApplication APP{ argc, argv };
    PharmacyGUI GUI{ medicineListRepository };
    GUI.show();
    APP.exec();
}

int main(int argc, char* argv[]) {
    run(argc, argv);
    return EXIT_SUCCESS;
}
