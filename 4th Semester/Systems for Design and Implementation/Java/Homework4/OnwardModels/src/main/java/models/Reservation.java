package models;

import java.util.List;
import java.util.UUID;

public class Reservation extends Entity<UUID> {
    private final Client client;
    private final Ride ride;
    private final List<ReservedSeat> seats;

    public Reservation(UUID uuid, Client client, Ride ride, ReservedSeat... seats) {
        super(uuid);
        this.client = client;
        this.ride = ride;
        this.seats = List.of(seats);
    }

    public Reservation(Client client, Ride ride,ReservedSeat... seats) {
        this.client = client;
        this.ride = ride;
        this.seats = List.of(seats);
    }

    public Reservation(UUID uuid, Client client, Ride ride, List<ReservedSeat> seats) {
        super(uuid);
        this.client = client;
        this.ride = ride;
        this.seats = seats;
    }

    public Reservation(Client client, Ride ride, List<ReservedSeat> seats) {
        this.client = client;
        this.ride = ride;
        this.seats = seats;
    }

    public Client getClient() {
        return client;
    }

    public Ride getRide() {
        return ride;
    }
    public List<ReservedSeat> getSeats() {
        return seats;
    }
}
