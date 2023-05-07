package repository.database;

import models.Client;
import models.Reservation;
import models.ReservedSeat;
import models.Ride;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import repository.ReservationRepository;
import repository.exceptions.DataChangeException;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Types;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;
import java.util.UUID;

public class ReservationDbRepository implements ReservationRepository {
    private final DbUtils dbUtils;
    private static final Logger logger = LogManager.getLogger(ReservationDbRepository.class);

    public ReservationDbRepository(Properties props) {
        logger.traceEntry("Initializing UserDbRepository with properties: {}", props);
        dbUtils = new DbUtils(props);
    }

    @Override
    public UUID save(Reservation entity) throws DataChangeException {
        logger.traceEntry("Saving the reservation: {}", entity);
        UUID reservationID;
        try (PreparedStatement preparedStatement0 = dbUtils.getConnection().prepareStatement(
                "SELECT reservation_id FROM reservations WHERE client_id = ? AND ride_id = ?")) {
            preparedStatement0.setObject(1, entity.getClient().getID(), Types.OTHER);
            preparedStatement0.setObject(2, entity.getRide().getID(), Types.OTHER);
            var result = DbUtils.findQueryResult(preparedStatement0, DbUtils::extractUUID);
            reservationID = result.isEmpty() ? null : result.get(0);
        } catch (SQLException ex) {
            logger.error(ex);
            throw new DataChangeException(ex);
        }

        if (reservationID != null) {
            try (PreparedStatement preparedStatement = dbUtils.getConnection().prepareStatement(
                    "INSERT INTO reservations(client_id, ride_id) VALUES (?, ?)")) {
                preparedStatement.setObject(1, entity.getClient().getID(), Types.OTHER);
                preparedStatement.setObject(2, entity.getRide().getID(), Types.OTHER);

                if (preparedStatement.executeUpdate() == 0) {
                    logger.traceExit(null);
                    return null;
                }
            } catch (SQLException ex) {
                logger.error(ex);
                throw new DataChangeException(ex);
            }
            try (PreparedStatement preparedStatement1 = dbUtils.getConnection().prepareStatement(
                    "SELECT reservation_id FROM reservations WHERE client_id = ? AND ride_id = ?")) {
                preparedStatement1.setObject(1, entity.getClient().getID(), Types.OTHER);
                preparedStatement1.setObject(2, entity.getRide().getID(), Types.OTHER);
                var result = DbUtils.findQueryResult(preparedStatement1, DbUtils::extractUUID);
                reservationID = result.isEmpty() ? null : result.get(0);
                if (reservationID == null) {
                    logger.traceExit(null);
                    return null;
                }
            } catch (SQLException ex) {
                logger.error(ex);
                throw new DataChangeException(ex);
            }
        }
        try (PreparedStatement preparedStatement2 = dbUtils.getConnection().prepareStatement(
                "INSERT INTO reserved_seats(reservation_id, seat_number) VALUES (?, ?)")) {
            preparedStatement2.setObject(1, reservationID, Types.OTHER);

            for (var seat : entity.getSeats()) {
                preparedStatement2.setInt(2, seat.getSeatNumber());
                preparedStatement2.executeUpdate();
            }
            return reservationID;
        } catch (SQLException ex) {
            logger.error(ex);
            throw new DataChangeException(ex);
        }
    }

    @Override
    public Reservation find(UUID identifier) {
        return null;
    }

    @Override
    public Reservation update(Reservation entity) {
        return null;
    }

    @Override
    public Reservation delete(UUID identifier) {
        return null;
    }

    @Override
    public List<Reservation> findReservationsByRide(Ride ride) {
        logger.traceEntry("Finding the reservations for the ride: {}", ride);

        List<Reservation> reservations = new ArrayList<>();
        try (PreparedStatement preparedStatement1 = dbUtils.getConnection().prepareStatement(
                "SELECT reservation_id, client_id FROM reservations WHERE ride_id = ?")) {
            preparedStatement1.setObject(1, ride.getID(), Types.OTHER);
            try (ResultSet resultSet1 = preparedStatement1.executeQuery()) {
                while (resultSet1.next()) {
                    UUID reservationID = resultSet1.getObject("reservation_id", UUID.class);
                    UUID clientID = resultSet1.getObject("client_id", UUID.class);

                    Client client;
                    try (PreparedStatement preparedStatement2 = dbUtils.getConnection().prepareStatement(
                            "SELECT * FROM clients WHERE client_id = ?"
                    )) {
                        preparedStatement2.setObject(1, clientID);
                        var result = DbUtils.findQueryResult(preparedStatement2, ClientDbRepository::extractClient);
                        client = result.isEmpty() ? null : result.get(0);
                    }

                    if (client == null) {
                        continue;
                    }
                    List<ReservedSeat> seats = new ArrayList<>();

                    try (PreparedStatement preparedStatement3 = dbUtils.getConnection().prepareStatement(
                            "SELECT reserved_seat_id, seat_number FROM reserved_seats WHERE reservation_id = ?")) {
                        preparedStatement3.setObject(1, reservationID);
                        try (ResultSet resultSet3 = preparedStatement3.executeQuery()) {
                            while (resultSet3.next()) {
                                UUID reservationSeatID = resultSet3.getObject("reserved_seat_id", UUID.class);
                                int seatNumber = resultSet3.getInt("seat_number");

                                seats.add(new ReservedSeat(reservationSeatID, seatNumber));
                            }
                        }
                    }
                    reservations.add(new Reservation(client, ride, seats));
                }
            }
        } catch (SQLException ex) {
            logger.error(ex);
            throw new RuntimeException(ex);
        }

        return logger.traceExit(reservations);
    }
}
