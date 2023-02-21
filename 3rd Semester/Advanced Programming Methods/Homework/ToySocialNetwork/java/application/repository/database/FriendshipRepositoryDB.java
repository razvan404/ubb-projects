package application.repository.database;

import application.models.Friendship;
import application.utils.pair.DistinctPair;
import application.repository.FriendshipRepository;
import application.utils.database.DataBase;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.Optional;
import java.util.TimeZone;
import java.util.UUID;

public class FriendshipRepositoryDB extends AbstractRepositoryDB<DistinctPair<UUID>, Friendship> implements FriendshipRepository {
    public FriendshipRepositoryDB(DataBase dataBase) {
        super(dataBase, "friendships");
    }

    @Override
    public Optional<Friendship> extractEntity(ResultSet resultSet) throws SQLException {
        return Optional.of(new Friendship(
                resultSet.getObject("first_user", UUID.class),
                resultSet.getObject("second_user", UUID.class),
                LocalDateTime.ofInstant(resultSet.getTimestamp("friends_from").toInstant(),
                        TimeZone.getDefault().toZoneId())));
    }

    @Override
    protected PreparedStatement findStatement(Connection connection, DistinctPair<UUID> userPair) throws SQLException {
        PreparedStatement preparedStatement = connection.prepareStatement(
        "SELECT * " +
             "FROM friendships " +
             "WHERE first_user = ? AND second_user = ?");
        preparedStatement.setObject(1, userPair.first(), Types.OTHER);
        preparedStatement.setObject(2, userPair.second(), Types.OTHER);
        return preparedStatement;
    }

    @Override
    protected PreparedStatement saveStatement(Connection connection, Friendship entity) throws SQLException {
        PreparedStatement preparedStatement = connection.prepareStatement(
        "INSERT INTO friendships (first_user, second_user, friends_from) " +
             "VALUES (?, ?, ?)");
        preparedStatement.setObject(1, entity.getID().first(), Types.OTHER);
        preparedStatement.setObject(2, entity.getID().second(), Types.OTHER);
        preparedStatement.setTimestamp(3, Timestamp.valueOf(entity.getFriendshipDate()));
        return preparedStatement;
    }

    @Override
    protected PreparedStatement deleteStatement(Connection connection, DistinctPair<UUID> userPair) throws SQLException {
        PreparedStatement preparedStatement = connection.prepareStatement(
        "DELETE FROM friendships " +
             "WHERE first_user = ? AND second_user = ?"
        );
        preparedStatement.setObject(1, userPair.first(), Types.OTHER);
        preparedStatement.setObject(2, userPair.second(), Types.OTHER);
        return preparedStatement;
    }

    @Override
    protected PreparedStatement updateStatement(Connection connection, Friendship entity) {
        return null;
    }

    @Override
    public void deleteFriendshipsOf(UUID user) {
        try (Connection connection = getConnection()){
            PreparedStatement preparedStatement = connection.prepareStatement(
            "DELETE FROM friendships " +
                 "WHERE first_user = ? OR second_user = ?"
            );
            preparedStatement.setObject(1, user, Types.OTHER);
            preparedStatement.setObject(2, user, Types.OTHER);

            preparedStatement.executeQuery();
        } catch (SQLException ignored) {}
    }
}
