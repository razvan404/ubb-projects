package OnwardTravel.repository.database;

import OnwardTravel.models.Ride;
import OnwardTravel.repository.RideRepository;
import OnwardTravel.repository.exceptions.DataLoadException;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Timestamp;
import java.time.LocalDateTime;
import java.util.List;
import java.util.Properties;
import java.util.UUID;

public class RideDbRepository implements RideRepository {
    private final DbUtils dbUtils;
    private static final Logger logger = LogManager.getLogger(RideDbRepository.class);

    public RideDbRepository(Properties props) {
        logger.traceEntry("Initializing UserDbRepository with properties: {}", props);
        dbUtils = new DbUtils(props);
    }

    public static Ride extractRide(ResultSet resultSet) {
        try {
            UUID rideID = resultSet.getObject("ride_id", UUID.class);
            String destination = resultSet.getString("destination");
            LocalDateTime departure = resultSet.getTimestamp("departure").toLocalDateTime();
            return new Ride(rideID, destination, departure);
        } catch (SQLException ex) {
            logger.error(ex);
            throw new RuntimeException(ex);
        }
    }

    @Override
    public UUID save(Ride entity) throws DataLoadException {
        return null;
    }

    @Override
    public Ride find(UUID identifier) throws DataLoadException {
        return null;
    }

    @Override
    public Ride update(Ride entity) {
        return null;
    }

    @Override
    public Ride delete(UUID identifier) {
        return null;
    }

    @Override
    public List<Ride> findAll() throws DataLoadException {
        try (PreparedStatement preparedStatement = dbUtils.getConnection().prepareStatement(
                "SELECT * FROM rides"
        )) {
            return DbUtils.findQueryResult(preparedStatement, RideDbRepository::extractRide);
        } catch (SQLException ex) {
            logger.error(ex);
            throw new DataLoadException(ex);
        }
    }

    @Override
    public List<Ride> findByDestinationAndDeparture(String destination, LocalDateTime departure) throws DataLoadException {
        try (PreparedStatement preparedStatement = dbUtils.getConnection().prepareStatement(
                "SELECT * FROM rides WHERE destination LIKE CONCAT('%', ?, '%') AND departure = departure"
        )) {
            preparedStatement.setString(1, destination);
            preparedStatement.setTimestamp(2, Timestamp.valueOf(departure));
            return DbUtils.findQueryResult(preparedStatement, RideDbRepository::extractRide);
        } catch (SQLException ex) {
            logger.error(ex);
            throw new DataLoadException(ex);
        }
    }
}
