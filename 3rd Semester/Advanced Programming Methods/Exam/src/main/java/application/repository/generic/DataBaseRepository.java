package application.repository.generic;

import application.models.Entity;
import application.utils.DataBase;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public abstract class DataBaseRepository<ID, E extends Entity<ID>> implements Repository<ID, E> {
    private final DataBase dataBase;


    protected DataBaseRepository(DataBase dataBase) {
        this.dataBase = dataBase;
    }

    /**
     * @return a connection to the database
     */
    protected Connection getConnection() throws SQLException {
        return dataBase.getConnection();
    }

    /**
     * @param resultSet the result set of the query applied to the database
     * @return the entity from the current row
     * @throws SQLException when the row is empty or when there was an invalid column
     */
    public abstract Optional<E> extractEntity(ResultSet resultSet) throws SQLException;

    /**
     * Executes a query and returns the list of the items found
     * @param query String, the query to be executed
     * @return the list of results
     */
    protected List<E> findQueryResults(String query) {
        List<E> result = new ArrayList<>();
        try {
            PreparedStatement preparedStatement = getConnection()
                    .prepareStatement(query);
            ResultSet resultSet = preparedStatement.executeQuery();
            while (resultSet.next()) {
                extractEntity(resultSet).ifPresent(result::add);
            }
        } catch (SQLException ignored) {}
        return result;
    }
}