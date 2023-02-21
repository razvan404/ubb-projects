package application.repository;

import application.models.SpecialOffer;
import application.repository.generic.DataBaseRepository;
import application.utils.DataBase;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.time.LocalDate;
import java.util.List;
import java.util.Optional;

public class SpecialOfferRepository extends DataBaseRepository<Double, SpecialOffer> {
    public SpecialOfferRepository(DataBase dataBase) {
        super(dataBase);
    }

    @Override
    public Optional<SpecialOffer> extractEntity(ResultSet resultSet) throws SQLException {
        double id = resultSet.getDouble("special_offer_id");
        double hotelID = resultSet.getDouble("hotel_id");
        LocalDate startDate = resultSet.getDate("start_date").toLocalDate();
        LocalDate endDate = resultSet.getDate("end_date").toLocalDate();
        int percents = resultSet.getInt("percents");
        return Optional.of(new SpecialOffer(id, hotelID, startDate, endDate, percents));
    }

    @Override
    public List<SpecialOffer> findAll() {
        return null;
    }

    public List<SpecialOffer> findAllFrom(double hotelID) {
        return findQueryResults("SELECT * FROM special_offers WHERE hotel_id = " + hotelID);
    }

    public List<SpecialOffer> findAllWithPercentsLowerThan(int percent) {
        return findQueryResults("SELECT * FROM special_offers WHERE percents < " + percent);
    }
}
