package application.repository.database;

import application.models.Entity;
import application.repository.AbstractRepository;
import application.utils.database.DataBase;

import java.sql.*;
import java.util.*;

public abstract class AbstractRepositoryDB<ID, E extends Entity<ID>> implements AbstractRepository<ID, E> {
    private final DataBase dataBase;
    private final String table;


    protected AbstractRepositoryDB(DataBase dataBase, String table) {
        this.dataBase = dataBase;
        this.table = table;
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
     * Creates a statement to find an entity based on a given identifier
     * @param connection the connection to the database
     * @param id the identifier of the user
     * @return a statement to find the specified user
     * @throws SQLException when the prepared statement can't be created
     */
    protected abstract PreparedStatement findStatement(Connection connection, ID id) throws SQLException;
    protected abstract PreparedStatement saveStatement(Connection connection, E entity) throws SQLException;
    protected abstract PreparedStatement deleteStatement(Connection connection, ID id) throws SQLException;
    protected abstract PreparedStatement updateStatement(Connection connection, E entity) throws SQLException;

    @Override
    public Optional<E> find(ID id) throws IllegalArgumentException {
        if (id == null) {
            throw new IllegalArgumentException("The identifier must not be null!");
        }
        try (Connection connection = getConnection()) {
            ResultSet resultSet = findStatement(connection, id).executeQuery();
            if (resultSet.next()) {
                return extractEntity(resultSet);
            }

        } catch (SQLException ignored) {}

        return Optional.empty();
    }

    @Override
    public Optional<E> save(E entity) throws IllegalArgumentException {
        if (entity == null) {
            throw new IllegalArgumentException("The entity must not be null!");
        }
        Optional<E> optionalEntity = find(entity.getID());
        if (optionalEntity.isPresent()) {
            return optionalEntity;
        }
        try (Connection connection = getConnection()) {
            saveStatement(connection, entity).executeQuery();
        } catch (SQLException ignored) {}
        return Optional.empty();
    }

    @Override
    public Optional<E> delete(ID id) throws IllegalArgumentException {
        if (id == null) {
            throw new IllegalArgumentException("The entity must not be null!");
        }
        Optional<E> optionalEntity = find(id);
        if (optionalEntity.isPresent()) {
            try (Connection connection = getConnection()) {
                deleteStatement(connection, id).executeQuery();
            } catch (SQLException ignored) {}
        }
        return optionalEntity;
    }

    @Override
    public Optional<E> update(E entity) throws IllegalArgumentException {
        if (entity == null) {
            throw new IllegalArgumentException("The entity must not be null!");
        }
        Optional<E> optionalEntity = find(entity.getID());
        if (optionalEntity.isEmpty()) {
            return Optional.empty();
        }
        try (Connection connection = getConnection()) {
            updateStatement(connection, entity).executeQuery();
        } catch (SQLException ignored) {}
        return optionalEntity;
    }

    @Override
    public int size() {
        try (Connection connection = getConnection()) {
            PreparedStatement preparedStatement = connection.prepareStatement(
            "SELECT COUNT(*) " +
                "FROM " + table
            );
            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                return resultSet.getInt("count");
            }
        } catch (SQLException ignored) {}
        return 0;
    }
}
