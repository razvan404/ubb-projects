package OnwardTravel.repository.database;

import OnwardTravel.models.Client;
import OnwardTravel.repository.ClientRepository;
import OnwardTravel.repository.exceptions.DataChangeException;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Properties;
import java.util.UUID;

public class ClientDbRepository implements ClientRepository {
    private final DbUtils dbUtils;
    private static final Logger logger = LogManager.getLogger(ClientDbRepository.class);

    public ClientDbRepository(Properties props) {
        logger.traceEntry("props={}", props);
        dbUtils = new DbUtils(props);
    }

    public static Client extractClient(ResultSet resultSet) {
        try {
            UUID clientID = resultSet.getObject("client_id", UUID.class);
            String name = resultSet.getString("name");
            String phoneNumber = resultSet.getString("phone_number");
            return new Client(clientID, name, phoneNumber);
        } catch (SQLException ex) {
            logger.error(ex);
            throw new RuntimeException(ex);
        }
    }

    @Override
    public UUID save(Client entity) throws DataChangeException {
        try (PreparedStatement preparedStatement = dbUtils.getConnection().prepareStatement(
                "INSERT INTO clients(name, phone_number) VALUES (?, ?)"
        )) {
            preparedStatement.setString(1, entity.getName());
            preparedStatement.setString(2, entity.getPhoneNumber());
            if (preparedStatement.executeUpdate() == 0) {
                return null;
            }
        } catch (SQLException ex) {
            logger.error(ex);
            throw new DataChangeException(ex);
        }
        return findByNameAndPhone(entity.getName(), entity.getPhoneNumber()).getID();
    }

    @Override
    public Client find(UUID identifier) {
        return null;
    }

    @Override
    public Client update(Client entity) {
        return null;
    }

    @Override
    public Client delete(UUID identifier) {
        return null;
    }

    @Override
    public Client findByNameAndPhone(String name, String phoneNumber) {
        logger.traceEntry("Finding the client with the name {} and phone number {}", name, phoneNumber);
        try (PreparedStatement preparedStatement = dbUtils.getConnection().prepareStatement(
                "SELECT * FROM clients WHERE name = ? AND phone_number = ?")) {
            preparedStatement.setString(1, name);
            preparedStatement.setString(2, phoneNumber);
            var result = DbUtils.findQueryResult(preparedStatement, ClientDbRepository::extractClient);
            return logger.traceExit("Found client: {}", result.isEmpty() ? null : result.get(0));
        } catch (SQLException ex) {
            logger.error(ex);
            throw new RuntimeException(ex);
        }
    }
}
