package repository;

import models.Reservation;
import models.Ride;

import java.util.List;
import java.util.UUID;

public interface ReservationRepository extends CrudRepository<UUID, Reservation> {
    List<Reservation> findReservationsByRide(Ride ride);
}
