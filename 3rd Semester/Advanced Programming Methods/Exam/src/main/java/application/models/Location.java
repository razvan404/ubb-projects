package application.models;

public class Location extends Entity<Double> {
    private final String locationName;

    public Location(Double aDouble, String locationName) {
        super(aDouble);
        this.locationName = locationName;
    }

    public String getLocationName() {
        return locationName;
    }

    @Override
    public String toString() {
        return locationName;
    }
}
