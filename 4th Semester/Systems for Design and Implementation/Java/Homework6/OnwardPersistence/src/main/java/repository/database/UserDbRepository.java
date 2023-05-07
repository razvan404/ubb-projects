package repository.database;

import models.User;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import repository.UserRepository;
import repository.exceptions.DataChangeException;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Types;
import java.util.Properties;
import java.util.UUID;

public class UserDbRepository implements UserRepository {
    private final DbUtils dbUtils;
    private static final Logger logger = LogManager.getLogger(UserDbRepository.class);

    public UserDbRepository(Properties props) {
        logger.traceEntry("Initializing UserDbRepository with properties: {}", props);
        dbUtils = new DbUtils(props);
    }

    protected static User extractUser(ResultSet resultSet) {
        logger.traceEntry("Result set: {}", resultSet);
        try {
            UUID identifier = resultSet.getObject("user_id", UUID.class);
            String username = resultSet.getString("username");
            String password = resultSet.getString("password");
            return logger.traceExit(new User(identifier, username, password));
        } catch (SQLException ex) {
            logger.error(ex);
            throw new RuntimeException(ex);
        }
    }

    @Override
    public UUID save(User entity) throws DataChangeException {
        logger.traceEntry("models.User to save: {}", entity);
        try (PreparedStatement preparedStatement = dbUtils.getConnection().prepareStatement(
                "INSERT INTO users(username, password) VALUES (?, ?)")) {
            preparedStatement.setString(1, entity.getUsername());
            preparedStatement.setString(2, entity.getPassword());
            preparedStatement.executeUpdate();
        } catch (SQLException ex) {
            logger.error(ex);
            throw new DataChangeException(ex);
        }
        try (PreparedStatement preparedStatement = dbUtils.getConnection().prepareStatement(
                "SELECT * FROM users WHERE username = ?")) {
            preparedStatement.setString(1, entity.getUsername());
            var result = DbUtils.findQueryResult(preparedStatement, UserDbRepository::extractUser);
            return logger.traceExit("ID of the new user: {}", result.isEmpty() ? null : result.get(0).getID());
        } catch (SQLException ex) {
            logger.error(ex);
            throw new DataChangeException(ex);
        }
    }

    @Override
    public User find(UUID identifier) {
        logger.traceEntry("ID of the user to find: {}", identifier);
        try (PreparedStatement preparedStatement = dbUtils.getConnection().prepareStatement(
                "SELECT * FROM users WHERE user_id = ?")) {
            preparedStatement.setObject(1, identifier, Types.OTHER);
            var result = DbUtils.findQueryResult(preparedStatement, UserDbRepository::extractUser);
            return logger.traceExit( "Found user: {}", result.isEmpty() ? null : result.get(0));
        } catch (SQLException ex) {
            logger.error(ex);
            throw new RuntimeException(ex);
        }
    }

    @Override
    public User update(User entity) {
        return null;
    }

    @Override
    public User delete(UUID identifier) {
        return null;
    }

    @Override
    public User tryLogin(String username, String password) {
        logger.traceEntry("Username of the user who is trying to log in: {}", username);
        try (PreparedStatement preparedStatement = dbUtils.getConnection().prepareStatement(
                "SELECT * FROM users WHERE username = ? AND password = ?")) {
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, password);
            var result = DbUtils.findQueryResult(preparedStatement, UserDbRepository::extractUser);
            return logger.traceExit("Logged in user: {}", result.isEmpty() ? null : result.get(0));
        } catch (SQLException ex) {
            logger.error(ex);
            throw new RuntimeException(ex);
        }
    }
}
