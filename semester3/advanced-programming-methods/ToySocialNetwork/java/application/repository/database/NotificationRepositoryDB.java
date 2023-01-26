package application.repository.database;

import application.models.exceptions.ValidationException;
import application.models.notification.Notification;
import application.models.notification.NotificationFactory;
import application.models.notification.NotificationType;
import application.repository.NotificationsRepository;
import application.utils.database.DataBase;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.*;

public class NotificationRepositoryDB implements NotificationsRepository {
    private final DataBase dataBase;

    public NotificationRepositoryDB(DataBase dataBase) {
        this.dataBase = dataBase;
    }

    /**
     * @return a connection to the database
     */
    protected Connection getConnection() throws SQLException {
        return dataBase.getConnection();
    }

    private Notification extractEntity(ResultSet resultSet) throws SQLException {
        return new Notification(
                resultSet.getLong("notification_id"),
                resultSet.getObject("from_user", UUID.class),
                resultSet.getObject("to_user", UUID.class),
                resultSet.getString("title"),
                resultSet.getString("message"),
                LocalDateTime.ofInstant(resultSet.getTimestamp("date")
                        .toInstant(), TimeZone.getDefault().toZoneId()),
                resultSet.getShort("type")
        );
    }

    @Override
    public List<Notification> findUserNotifications(UUID userID) {
        List<Notification> notificationList = new ArrayList<>();
        try (Connection connection = getConnection()) {
            PreparedStatement preparedStatement = connection.prepareStatement(
                    "SELECT * " +
                            "FROM notifications " +
                            "WHERE to_user = ? " +
                            "ORDER BY date DESC");
            preparedStatement.setObject(1, userID);
            ResultSet resultSet = preparedStatement.executeQuery();
            while (resultSet.next()) {
                notificationList.add(extractEntity(resultSet));
            }

        } catch (SQLException ignored) {}
        return notificationList;
    }

    @Override
    public Optional<Notification> save(Notification notification) throws ValidationException {
        if (notification == null) {
            throw new IllegalArgumentException("The entity must not be null!");
        }

        if (notification.getType().equals(NotificationType.FRIEND_REQUEST)
                && getFriendRequest(notification.getFromUser(), notification.getToUser()).isPresent()) {
            return Optional.of(notification);
        }

        try (Connection connection = getConnection()) {
            PreparedStatement preparedStatement = connection.prepareStatement(
            "INSERT INTO notifications" +
                "(from_user, to_user, title, message, date, type) VALUES (?, ?, ?, ?, ?, ?)"
            );
            preparedStatement.setObject(1, notification.getFromUser(), Types.OTHER);
            preparedStatement.setObject(2, notification.getToUser(), Types.OTHER);
            preparedStatement.setString(3, notification.getTitle());
            preparedStatement.setString(4, notification.getMessage());
            preparedStatement.setTimestamp(5, Timestamp.valueOf(notification.getDate()));
            preparedStatement.setShort(6, notification.getTypeID());

            preparedStatement.executeQuery();

        } catch (SQLException ignored) {}
        return Optional.empty();
    }

    @Override
    public Optional<Notification> getFriendRequest(UUID firstUser, UUID secondUser) {
        try (Connection connection = getConnection()) {
            PreparedStatement preparedStatement = connection.prepareStatement(
            "SELECT * " +
                "FROM notifications " +
                "WHERE type = ? AND ((from_user = ? AND to_user = ?) OR (to_user = ? AND from_user = ?))"
            );
            preparedStatement.setShort(1, NotificationFactory.getTypeID(NotificationType.FRIEND_REQUEST));
            preparedStatement.setObject(2, firstUser, Types.OTHER);
            preparedStatement.setObject(3, secondUser, Types.OTHER);
            preparedStatement.setObject(4, firstUser, Types.OTHER);
            preparedStatement.setObject(5, secondUser, Types.OTHER);

            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                return Optional.of(extractEntity(resultSet));
            }

        } catch (SQLException ignored) {}
        return Optional.empty();
    }

    @Override
    public void delete(Long ID) {
        try (Connection connection = getConnection()) {
            PreparedStatement preparedStatement = connection.prepareStatement(
            "DELETE FROM notifications " +
                "WHERE notification_id = ?");
            preparedStatement.setLong(1, ID);

            preparedStatement.executeQuery();
        } catch (SQLException ignored) {}
    }

    @Override
    public void deleteNotificationsOf(UUID user) {
        try (Connection connection = getConnection()) {
            PreparedStatement preparedStatement = connection.prepareStatement(
            "DELETE FROM notifications " +
                "WHERE from_user = ? OR to_user = ?"
            );
            preparedStatement.setObject(1, user, Types.OTHER);
            preparedStatement.setObject(2, user, Types.OTHER);

            preparedStatement.executeQuery();
        } catch (SQLException ignored) {}
    }
}
