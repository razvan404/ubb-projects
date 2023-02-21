package application.repository;

import application.models.Reservation;
import application.repository.generic.DataBaseRepository;
import application.utils.DataBase;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Timestamp;
import java.util.List;
import java.util.Optional;
import java.util.Random;

public class ReservationRepository extends DataBaseRepository<Double, Reservation> {

    public ReservationRepository(DataBase dataBase) {
        super(dataBase);
    }

    @Override
    public Optional<Reservation> extractEntity(ResultSet resultSet) throws SQLException {
        return Optional.empty();
    }

    public void save(Reservation reservation) {
        try {
            PreparedStatement preparedStatement = getConnection().prepareStatement(
              "INSERT INTO reservations(reservation_id, client_id, hotel_id, start_date, no_nights)  " +
                      "VALUES (?, ?, ?, ?, ?)"
            );
            preparedStatement.setDouble(1, reservation.getID());
            preparedStatement.setLong(2, reservation.getClientID());
            preparedStatement.setDouble(3, reservation.getHotelID());
            preparedStatement.setTimestamp(4, Timestamp.valueOf(reservation.getStartDate()));
            preparedStatement.setInt(5, reservation.getNoNights());

            System.out.println(preparedStatement);

            preparedStatement.executeQuery();
        } catch (SQLException ignored) {}
    }

    @Override
    public List<Reservation> findAll() {
        return null;
    }
}
