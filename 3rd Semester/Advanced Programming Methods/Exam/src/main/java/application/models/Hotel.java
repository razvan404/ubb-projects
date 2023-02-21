package application.models;

public class Hotel extends Entity<Double> {
    private final double locationID;
    private final String hotelName;
    private final int noRooms;
    private final double perNight;
    private final HotelType type;

    public Hotel(Double aDouble, double locationID, String hotelName, int noRooms, double perNight, HotelType type) {
        super(aDouble);
        this.locationID = locationID;
        this.hotelName = hotelName;
        this.noRooms = noRooms;
        this.perNight = perNight;
        this.type = type;
    }

    public double getLocationID() {
        return locationID;
    }

    public String getHotelName() {
        return hotelName;
    }

    public int getNoRooms() {
        return noRooms;
    }

    public double getPerNight() {
        return perNight;
    }

    public HotelType getType() {
        return type;
    }
}
