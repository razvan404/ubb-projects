package application.repository;

import application.models.Client;
import application.models.Hotel;
import application.models.HotelType;
import application.repository.generic.DataBaseRepository;
import application.utils.DataBase;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;
import java.util.Optional;

public class HotelRepository extends DataBaseRepository<Double, Hotel> {

    public HotelRepository(DataBase dataBase) {
        super(dataBase);
    }

    @Override
    public Optional<Hotel> extractEntity(ResultSet resultSet) throws SQLException {
        double id = resultSet.getDouble("hotel_id");
        double locationID = resultSet.getDouble("location_id");
        String hotelName = resultSet.getString("hotel_name");
        int noRooms = resultSet.getInt("no_rooms");
        double pricePerNight = resultSet.getDouble("price_per_night");
        HotelType type = HotelType.valueOf(resultSet.getString("type"));
        return Optional.of(new Hotel(id, locationID, hotelName, noRooms, pricePerNight, type));
    }

    @Override
    public List<Hotel> findAll() {
        return findQueryResults("SELECT * FROM hotels");
    }

    public List<Hotel> findHotelsFrom(double locationID) {
        return findQueryResults("SELECT * FROM hotels WHERE location_id = " + locationID);
    }

    public Optional<Hotel> find(Double aDouble) {
        List<Hotel> results = findQueryResults("SELECT * FROM hotels WHERE hotel_id = " + aDouble);
        if (results.isEmpty()) {
            return Optional.empty();
        }
        return Optional.of(results.get(0));
    }
}
