package OnwardTravel.repository;

import OnwardTravel.models.Reservation;
import OnwardTravel.models.Ride;
import OnwardTravel.repository.exceptions.DataLoadException;

import java.util.List;
import java.util.UUID;

public interface ReservationRepository extends CrudRepository<UUID, Reservation> {
    List<Reservation> findReservationsOnRide(Ride ride) throws DataLoadException;
}
