#include "Tests.h"
#include "Joc.hpp"
#include "Repository.h"
#include "Service.h"
#include <cassert>

void testJoc() {
	Joc j{ "GodOfWar", 90, "PlayStation", 18 };
	assert(j.getTitlu() == "GodOfWar");
	assert(j.getPret() == 90);
	assert(j.getPlatforma() == "PlayStation");
	assert(j.getAge() == 18);
	Joc j2{ "GodOfWar", 90, "PC", 16 };

	assert(j == j2);
}

void testRepo() {
	Repo r{ "Tests.txt" };
	auto& v = r.getList();
	assert(v.size() == 3);
	assert(v.at(0).getTitlu() == "GodOfWar");
	assert(v.at(1).getTitlu() == "HaloInfinite");
	assert(v.at(2).getTitlu() == "MarioKartDeluxe");
}

void testServ() {
	Repo r{ "Tests.txt" };
	Serv s{ r };

	auto v = s.getList();
	assert(v.size() == 3);
	assert(v.at(0).getTitlu() == "GodOfWar");
	assert(v.at(1).getTitlu() == "HaloInfinite");
	assert(v.at(2).getTitlu() == "MarioKartDeluxe");
	
	assert(s.getPos("HaloInfinite", 320) == 1);
	assert(s.getPos("HaloInfinite", 310) == -1);

	assert(s.at(1).getTitlu() == "HaloInfinite");
	try {
		s.at(3);
		assert(false);
	}
	catch (...) {
		assert(true);
	}
	v = s.ptCopii();
	assert(v.size() == 1);
	assert(v.at(0).getAge() == 3);

	v = s.sorteazaCresc();
	assert(v.at(0).getPret() == 90);
	assert(v.at(1).getPret() == 230);
	assert(v.at(2).getPret() == 320);

}

void testAll() {
	testJoc();
	testRepo();
	testServ();
}