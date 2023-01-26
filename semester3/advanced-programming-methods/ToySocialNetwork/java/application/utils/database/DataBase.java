package application.utils.database;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

/**
 * The class <b>DataBase</b> is used to store the data from an existing database, such as the URL of the database,
 * the user who is using the database and its password.
 */
public class DataBase {
    private final String url;
    private final String username;
    private final String password;

    /**
     * Constructs a new DataBase
     * @param url String, the URL where the database is stored
     * @param username String, the database user on whose behalf the connection is being made
     * @param password String, user's password
     */
    public DataBase(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    /**
     * @return a connection to the database
     * @throws RuntimeException when the connection cannot be established
     */
    public Connection getConnection() throws RuntimeException {
        try {
            return DriverManager.getConnection(url, username, password);
        }
        catch (SQLException sqlException) {
            throw new RuntimeException(sqlException);
        }
    }
}
