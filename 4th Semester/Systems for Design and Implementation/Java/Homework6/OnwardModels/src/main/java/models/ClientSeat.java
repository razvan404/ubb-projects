package models;

import java.io.Serializable;

public class ClientSeat implements Serializable {
    private final Client client;
    private final Reservation reservation;
    private final ReservedSeat seat;

    public ClientSeat(Client client, Reservation reservation, ReservedSeat seat) {
        this.client = client;
        this.reservation = reservation;
        this.seat = seat;
    }

    public Client getClient() {
        return client;
    }

    public Reservation getReservation() {
        return reservation;
    }

    public ReservedSeat getSeat() {
        return seat;
    }
}
