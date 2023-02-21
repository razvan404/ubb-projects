#pragma once
#include <string>

using namespace std;

class Joc {
private:
	string titlu;
	unsigned pret;
	string platforma;
	unsigned age;
public:
	// Constructorul
	//	titlu: string, titlul jocului
	//	pret: unsigned, pretul jocului
	//	platforma: string, platforma jocului
	//	age: unsigned, PEGI age rating
	Joc(string titlu, unsigned pret, string platforma, unsigned age)
		: titlu{ titlu }, pret{ pret },
		platforma{ platforma }, age{ age } {};
	
	// returneaza titlul jocului
	//	return: string, titlul jocului 
	string getTitlu() {
		return titlu;
	}

	// returneaza pretul jocului
	//	return: unsigned, pretul jocului
	unsigned getPret() {
		return pret;
	}

	// returneaza platforma jocului
	//	return: string, platforma jocului
	string getPlatforma() {
		return platforma;
	}

	// returneaza PEGI age rating al jocului
	//	return:  unsigned, PEGI age rating
	unsigned getAge() {
		return age;
	}

	// Compara daca 2 jocuri au acelasi titlu si pret
	//	return: Adevarat / Fals daca jocurile au acelasi titlu si pret
	bool operator==(Joc& oth) {
		return titlu == oth.titlu && pret == oth.pret;
	}
};