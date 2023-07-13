package api.services.observer;

import api.services.notification.Notification;

import java.util.HashMap;
import java.util.Map;

public abstract class Observable<T> {
    protected Map<T, Observer> observers = new HashMap<>();

    public void addObserver(T key, Observer observer) {
        observers.put(key, observer);
    }

    public T removeObserver(Observer observer) {
        T key = observers.entrySet().stream()
                .filter(entry -> entry.getValue().equals(observer))
                .map(Map.Entry::getKey)
                .findFirst()
                .orElse(null);
        if (key != null) {
            observers.remove(key);
        }
        return key;
    }

    public void notifyObservers(Notification notification) {
        observers.values().forEach(observer -> observer.notify(notification));
    }

    public void notifyObserver(T key, Notification notification) {
        observers.get(key).notify(notification);
    }
}
