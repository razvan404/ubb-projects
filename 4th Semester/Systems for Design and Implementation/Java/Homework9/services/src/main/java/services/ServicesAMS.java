package services;

import models.Ride;

import java.util.List;

public interface ServicesAMS {
    List<Ride> getRides();
    void createRide(Ride ride) throws ServiceException;
}
