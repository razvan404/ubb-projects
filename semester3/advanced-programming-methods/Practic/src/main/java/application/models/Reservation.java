package application.models;

import application.models.exceptions.ValidationException;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.Random;

public class Reservation extends Entity<Double> {
    private final long clientID;
    private final double hotelID;
    private final LocalDateTime startDate;
    private final int noNights;
    private static Random random = new Random();

    public Reservation(Double aDouble, long clientID, double hotelID, LocalDateTime startDate, int noNights) {
        super(aDouble);
        this.clientID = clientID;
        this.hotelID = hotelID;
        this.startDate = startDate;
        this.noNights = noNights;
    }

    public static Reservation create(Client client, Hotel hotel, LocalDateTime startDate, int noNights) throws ValidationException {
        if (client == null || hotel == null || startDate == null) {
            throw new ValidationException("Arguments shouldn't be null!");
        }
        if (startDate.isBefore(LocalDateTime.now())) {
            throw new ValidationException("The date should be after today!");
        }
        if (noNights < 0) {
            throw new ValidationException("You should reserve a positive number of nights!");
        }
        return new Reservation(random.nextDouble(), client.getID(), hotel.getID(), startDate, noNights);
    }

    public long getClientID() {
        return clientID;
    }

    public double getHotelID() {
        return hotelID;
    }

    public LocalDateTime getStartDate() {
        return startDate;
    }

    public int getNoNights() {
        return noNights;
    }
}
