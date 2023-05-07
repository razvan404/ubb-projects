package OnwardTravel.repository;

import OnwardTravel.models.Ride;
import OnwardTravel.repository.exceptions.DataLoadException;

import java.time.LocalDateTime;
import java.util.List;
import java.util.UUID;

public interface RideRepository extends CrudRepository<UUID, Ride> {
    List<Ride> findAll() throws DataLoadException;
    List<Ride> findByDestinationAndDeparture(String destination, LocalDateTime departure) throws DataLoadException;
}
