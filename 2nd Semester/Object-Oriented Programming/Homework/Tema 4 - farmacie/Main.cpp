#include <crtdbg.h>

#include "UserInterface.h"
#include "Tests.h"

void run() {
	Tests TM;
	TM.runAllTests();
	MedicineListRepository medicineListRepository;
	UserInterface UI{ medicineListRepository };
	UI.begin();
}

int main() {
	run();
	_CrtDumpMemoryLeaks();
	return 0;
}
