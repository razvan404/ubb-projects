package application.utils;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class DataBase {
    private final Connection activeConnection;

    public DataBase(String url, String username, String password) {
        try {
            activeConnection = DriverManager.getConnection(url, username, password);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public Connection getConnection() {
        return activeConnection;
    }

    public void closeConnection() {
        try {
            activeConnection.close();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
