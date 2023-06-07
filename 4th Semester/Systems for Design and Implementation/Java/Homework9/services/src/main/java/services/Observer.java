package services;

import models.Ride;

public interface Observer {
    void rideCreated(Ride ride);
}
