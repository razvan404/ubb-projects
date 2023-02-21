package application.utils.observer;

import java.util.HashSet;
import java.util.Set;

public abstract class Observable {
    private final Set<Observer> observers;

    protected Observable() {
        observers = new HashSet<>();
    }

    public void addObserver(Observer observer) {
        observers.add(observer);
    }

    protected void notifyObservers(Object... resources) {
        observers.forEach(observer -> observer.update(resources));
    }
}
