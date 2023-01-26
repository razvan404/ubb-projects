#include "Service.h"

vector<Joc> Serv::sorteazaCresc() {
	vector<Joc> sortat = repo.getList();
	sort(sortat.begin(), sortat.end(), [&](Joc& j1, Joc& j2) {
		return j1.getPret() < j2.getPret();
		});
	return sortat;
}

vector<Joc> Serv::ptCopii() {
	vector<Joc> filt;
	for (auto& j : repo.getList()) {
		if (j.getAge() < 12) {
			filt.push_back(j);
		}
	}
	return filt;
}

Joc& Serv::at(unsigned pos) {
	if (pos >= repo.getList().size()) {
		throw exception("Invalid position");
	}
	return repo.getList().at(pos);
}