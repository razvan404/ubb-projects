package application.models;

import application.models.exceptions.ValidationException;

import java.time.LocalDate;

public class SpecialOffer extends Entity<Double> {
    private final double hotelID;
    private final LocalDate startDate;
    private final LocalDate endDate;
    private final int percents;

    public SpecialOffer(Double aDouble, double hotelID, LocalDate startDate, LocalDate endDate, int percents) {
        super(aDouble);
        this.hotelID = hotelID;
        this.startDate = startDate;
        this.endDate = endDate;
        this.percents = percents;
    }

    public static SpecialOffer create(Hotel hotel, LocalDate startDate, LocalDate endDate, int percents)
            throws ValidationException {
        if (hotel == null || startDate == null || endDate == null) {
            throw new ValidationException("Cannot give null parameters!");
        }
        if (startDate.isAfter(endDate)) {
            throw new ValidationException("The start date should be before the end date!");
        }
        if (percents < 1 || percents > 100) {
            throw new ValidationException("The percent value should be between 1 and 100!");
        }
        return new SpecialOffer(-1d, hotel.getID(), startDate, endDate, percents);
    }

    public double getHotelID() {
        return hotelID;
    }

    public LocalDate getStartDate() {
        return startDate;
    }

    public LocalDate getEndDate() {
        return endDate;
    }

    public int getPercents() {
        return percents;
    }
}
