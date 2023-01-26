package application.repository.database;

import application.models.Contact;
import application.models.Friend;
import application.models.Message;
import application.repository.MessageRepository;
import application.utils.database.DataBase;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.*;

public class MessageRepositoryDB extends AbstractRepositoryDB<Long, Message> implements MessageRepository {
    public MessageRepositoryDB(DataBase dataBase) {
        super(dataBase, "messages");
    }

    @Override
    public Optional<Message> extractEntity(ResultSet resultSet) throws SQLException {
        return Optional.of(new Message(resultSet.getLong("message_id"),
                resultSet.getObject("from_user", UUID.class),
                resultSet.getObject("to_user", UUID.class),
                resultSet.getString("message"),
                LocalDateTime.ofInstant(resultSet.getTimestamp("time").toInstant(),
                        TimeZone.getDefault().toZoneId())));
    }

    @Override
    protected PreparedStatement findStatement(Connection connection, Long aLong) throws SQLException {
        PreparedStatement preparedStatement = connection.prepareStatement(
        "SELECT * " +
             "FROM messages " +
             "WHERE message_id = ?"
        );
        preparedStatement.setLong(1, aLong);
        return preparedStatement;
    }

    @Override
    protected PreparedStatement saveStatement(Connection connection, Message message) throws SQLException {
        PreparedStatement preparedStatement = connection.prepareStatement(
          "INSERT INTO messages(from_user, to_user, message, time) " +
               "VALUES (?, ?, ?, ?)"
        );
        preparedStatement.setObject(1, message.getFromUser(), Types.OTHER);
        preparedStatement.setObject(2, message.getToUser(), Types.OTHER);
        preparedStatement.setString(3, message.getMessage());
        preparedStatement.setTimestamp(4, Timestamp.valueOf(message.getTime()));
        return preparedStatement;
    }

    @Override
    protected PreparedStatement deleteStatement(Connection connection, Long aLong) throws SQLException {
        PreparedStatement preparedStatement = connection.prepareStatement(
        "DELETE FROM messages " +
             "WHERE message_id = ?"
        );
        preparedStatement.setObject(1, aLong);
        return preparedStatement;
    }

    @Override
    protected PreparedStatement updateStatement(Connection connection, Message entity) {
        return null;
    }

    @Override
    public List<Message> getMessagesBetween(UUID firstUser, UUID secondUser) {
        List<Message> messages = new ArrayList<>();
        try (Connection connection = getConnection()) {
            PreparedStatement preparedStatement = connection.prepareStatement(
            "SELECT * " +
                 "FROM messages " +
                 "WHERE (from_user = ? AND to_user = ?) OR (from_user = ? AND to_user = ?)"
            );
            preparedStatement.setObject(1, firstUser, Types.OTHER);
            preparedStatement.setObject(2, secondUser, Types.OTHER);
            preparedStatement.setObject(3, secondUser, Types.OTHER);
            preparedStatement.setObject(4, firstUser, Types.OTHER);

            ResultSet resultSet = preparedStatement.executeQuery();
            while (resultSet.next()) {
                extractEntity(resultSet).ifPresent(messages::add);
            }
        } catch (SQLException ignored) {}
        return messages;
    }

    @Override
    public List<Contact> getContactList(UUID user, List<Friend> friendList) {
        List<Contact> contacts = new ArrayList<>();
        try (Connection connection = getConnection()) {
            for (Friend friend : friendList) {
                PreparedStatement preparedStatement = connection.prepareStatement(
                "SELECT message_id, from_user, to_user, message, time " +
                     "FROM messages " +
                     "WHERE ((from_user = ? AND to_user = ?) OR (from_user = ? AND to_user = ?)) AND time = (" +
                        "SELECT MAX(time) FROM messages " +
                        "WHERE (from_user = ? AND to_user = ?) OR (from_user = ? AND to_user = ?))"
                );
                preparedStatement.setObject(1, user, Types.OTHER);
                preparedStatement.setObject(2, friend.getID(), Types.OTHER);
                preparedStatement.setObject(3, friend.getID(), Types.OTHER);
                preparedStatement.setObject(4, user, Types.OTHER);

                preparedStatement.setObject(5, user, Types.OTHER);
                preparedStatement.setObject(6, friend.getID(), Types.OTHER);
                preparedStatement.setObject(7, friend.getID(), Types.OTHER);
                preparedStatement.setObject(8, user, Types.OTHER);

                ResultSet resultSet = preparedStatement.executeQuery();
                if (resultSet.next()) {
                    contacts.add(new Contact(friend, extractEntity(resultSet).orElse(null)));
                }
                else {
                    contacts.add(new Contact(friend, null));
                }
            }
        } catch (SQLException ignored) {}
        return contacts;
    }
}
