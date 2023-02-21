#pragma once
#include <vector>

class Observer {
public:
	virtual void update() = 0;
};

class Observable {
	std::vector<Observer*> v;
public:
	void addObserver(Observer* o) {
		v.push_back(o);
	}
	void notify() {
		for (auto& o : v) {
			o->update();
		}
	}
};