package models;

import java.time.LocalDateTime;
import java.util.UUID;

public class Ride extends Entity<UUID> {
    private final String destination;
    private final LocalDateTime departure;

    public Ride(UUID uuid, String destination, LocalDateTime departure) {
        super(uuid);
        this.destination = destination;
        this.departure = departure;
    }

    public Ride(String destination, LocalDateTime departure) {
        this.destination = destination;
        this.departure = departure;
    }

    public String getDestination() {
        return destination;
    }

    public LocalDateTime getDeparture() {
        return departure;
    }
}
