package service;

import models.ClientSeat;
import models.Ride;
import models.User;
import service.exceptions.InvalidDataException;
import service.observer.UserObserver;

import java.time.LocalDate;
import java.util.List;

public interface UserService {
    User tryLogin(User user, UserObserver requester) throws InvalidDataException;
    void logout(UserObserver requester);
    List<Ride> findAllRides();
    int findEmptySeatsOnRide(Ride ride);
    List<Ride> findRidesByDestinationAndDeparture(String destination, LocalDate departureDay);
    ClientSeat[] findReservationsByRide(Ride ride);
    void createReservation(Ride ride, String clientName, String phoneNumber, int seatsCount) throws InvalidDataException;
}
