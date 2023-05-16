package repository.database;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;
import java.util.UUID;
import java.util.function.Function;

public class DbUtils {
    private final Properties dbProps;
    private static final Logger logger = LogManager.getLogger(DbUtils.class);
    private static Connection instance = null;

    public DbUtils(Properties props) {
        dbProps = props;
    }

    private Connection getNewConnection() {
        logger.traceEntry();
        String url = dbProps.getProperty("db.url");
        String user = dbProps.getProperty("db.user");
        String pass = dbProps.getProperty("db.pass");
        logger.info("Connecting to the repository.database {}", url);
        logger.info("Username: {}", user);
        logger.info("Password: {}", pass);

        try {
            Connection connection = user != null && pass != null ?
                    DriverManager.getConnection(url, user, pass) : DriverManager.getConnection(url);
            return logger.traceExit(connection);
        } catch (SQLException ex) {
            logger.error(ex);
            throw new RuntimeException(ex);
        }
    }

    public Connection getConnection() {
        logger.traceEntry();
        logger.info("Getting a connection to the repository.database: {}", dbProps.getProperty("db.url"));
        try {
            if (instance == null || instance.isClosed()) {
                instance = getNewConnection();
            }
            return logger.traceExit(instance);
        } catch (SQLException ex) {
            logger.error(ex);
            throw new RuntimeException(ex);
        }
    }

    public static <T> List<T> findQueryResult(PreparedStatement preparedStatement, Function<ResultSet, T> extractFunction) {
        logger.traceEntry("preparedStatement={} extractFunction={}", preparedStatement, extractFunction);
        try (ResultSet resultSet = preparedStatement.executeQuery()) {
            List<T> queryResult = new ArrayList<>();
            while (resultSet.next()) {
                queryResult.add(extractFunction.apply(resultSet));
            }
            return logger.traceExit(queryResult);
        } catch (SQLException ex) {
            logger.error(ex);
            throw new RuntimeException(ex);
        }
    }

    public static UUID extractUUID(ResultSet resultSet) {
        try {
            return resultSet.getObject(1, UUID.class);
        } catch (SQLException ex) {
            logger.error(ex);
            throw new RuntimeException(ex);
        }
    }
}
