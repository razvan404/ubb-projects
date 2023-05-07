package repository;

import models.Ride;

import java.time.LocalDate;
import java.util.List;
import java.util.UUID;

public interface RideRepository extends CrudRepository<UUID, Ride> {
    List<Ride> findAll();
    List<Ride> findByDestinationAndDeparture(String destination, LocalDate departureDay);
}
