package application.repository;

import application.models.Location;
import application.repository.generic.DataBaseRepository;
import application.utils.DataBase;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;
import java.util.Optional;

public class LocationRepository extends DataBaseRepository<Double, Location> {

    public LocationRepository(DataBase dataBase) {
        super(dataBase);
    }

    @Override
    public Optional<Location> extractEntity(ResultSet resultSet) throws SQLException {
        double id = resultSet.getDouble("location_id");
        String name = resultSet.getString("location_name");
        return Optional.of(new Location(id, name));
    }

    @Override
    public List<Location> findAll() {
        return findQueryResults("SELECT * FROM locations");
    }
}
