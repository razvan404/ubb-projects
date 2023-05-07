package service.observer;

import models.Reservation;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public abstract class UserObservable {
    private final List<UserObserver> observers;
    public UserObservable() {
        observers = new ArrayList<>();
    }

    public void addObserver(UserObserver userObserver) {
        observers.add(userObserver);
    }

    public void removeObserver(UserObserver userObserver) {
        observers.remove(userObserver);
    }

    private int defaultThreadsNo = 5;
    public void notifyReservationCreated(Reservation reservation) {
        try (ExecutorService executorService = Executors.newFixedThreadPool(defaultThreadsNo)) {
            observers.forEach(observer -> executorService.execute(() -> observer.handleReservationCreated(reservation)));
        }
    }
}
