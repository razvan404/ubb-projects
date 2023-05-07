package service.observer;

import models.Reservation;

import java.io.Serializable;

public interface UserObserver extends Serializable {
    void handleReservationCreated(Reservation reservation);
}
