package application.service;

import application.models.exceptions.ValidationException;
import application.models.notification.Notification;
import application.models.notification.NotificationType;
import application.repository.NotificationsRepository;
import application.service.exceptions.AlreadyExistsException;

import java.util.List;
import java.util.UUID;

public class NotificationService {
    private final NotificationsRepository repository;

    public NotificationService(NotificationsRepository repository) {
        this.repository = repository;
    }

    public List<Notification> findUserNotifications(UUID userID) {
        return repository.findUserNotifications(userID);
    }

    public void delete(Long ID) {
        repository.delete(ID);
    }

    public void save(UUID fromUserID, UUID toUserID, String title, String message,
                     NotificationType notificationType) throws ValidationException, AlreadyExistsException {
        if (repository.save(Notification.create(fromUserID, toUserID, title, message, notificationType)).isPresent()) {
            throw new AlreadyExistsException("You have already sent a friend request to that user!");
        }
    }

    public Notification getFriendRequest(UUID firstUser, UUID secondUser) {
        return repository.getFriendRequest(firstUser, secondUser).orElse(null);
    }

    public void deleteNotificationsOf(UUID user) {
        repository.deleteNotificationsOf(user);
    }
}
