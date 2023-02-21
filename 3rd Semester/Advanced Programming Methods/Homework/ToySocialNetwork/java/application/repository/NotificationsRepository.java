package application.repository;

import application.models.exceptions.ValidationException;
import application.models.notification.Notification;

import java.util.List;
import java.util.Optional;
import java.util.UUID;

public interface NotificationsRepository {
    List<Notification> findUserNotifications(UUID userID);
    Optional<Notification> save(Notification entity) throws IllegalArgumentException, ValidationException;
    Optional<Notification> getFriendRequest(UUID firstUser, UUID secondUser);
    void delete(Long ID);
    void deleteNotificationsOf(UUID user);
}
