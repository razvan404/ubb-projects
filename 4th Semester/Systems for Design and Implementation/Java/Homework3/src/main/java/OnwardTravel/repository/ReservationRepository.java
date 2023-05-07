package OnwardTravel.repository;

import OnwardTravel.models.Reservation;
import OnwardTravel.models.Ride;

import java.util.List;
import java.util.UUID;

public interface ReservationRepository extends CrudRepository<UUID, Reservation> {
    List<Reservation> findReservationsByRide(Ride ride);
}
