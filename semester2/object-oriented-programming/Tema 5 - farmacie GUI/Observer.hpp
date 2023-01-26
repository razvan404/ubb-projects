#pragma once
#include <vector>

/* Update method needs to be implemented by observers
 Alternative names: Listener */
class Observer {
public:
	/* Invoked when Observable change
	Alternative names:properyChanged */
	virtual void update() = 0;
};
/* Derive from this class if you want to provide notifications
 Alternative names: Subject, ChangeNotifier */
class Observable {
private:
	/*Non owning pointers to observer objects*/
	std::vector<Observer*> observers;
public:
	/* Observers use this method to register for notification
	 Alternative names: attach, register, subscribe, addListener */
	void addObserver(Observer* obs) {
		observers.push_back(obs);
	}
	/* Observers use this to cancel the registration
	!!!Before an observer is destroyed need to cancel the registration
	 Alternative names: detach, unregister, removeListener */
	void removeObserver(Observer* obs) {
		observers.erase(std::remove(begin(observers), end(observers), obs),
			observers.end());
	}
protected:
	/* Invoked by the observable object
	 in order to notify interested observer */
	void notify() {
		for (auto obs : observers) {
			obs->update();
		}
	}
};