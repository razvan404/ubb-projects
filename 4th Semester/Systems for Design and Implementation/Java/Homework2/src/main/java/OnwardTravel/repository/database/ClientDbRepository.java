package OnwardTravel.repository.database;

import OnwardTravel.models.Client;
import OnwardTravel.repository.ClientRepository;
import OnwardTravel.repository.exceptions.DataLoadException;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

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
            UUID clientID = resultSet.getObject("user_id", UUID.class);
            String name = resultSet.getString("name");
            String phoneNumber = resultSet.getString("phone_number");
            return new Client(clientID, name, phoneNumber);
        } catch (SQLException ex) {
            logger.error(ex);
            throw new RuntimeException(ex);
        }
    }

    @Override
    public UUID save(Client entity) throws DataLoadException {
        return null;
    }

    @Override
    public Client find(UUID identifier) throws DataLoadException {
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
}
