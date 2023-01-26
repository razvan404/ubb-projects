package application.models.notification;

import application.models.Entity;
import application.models.exceptions.ValidationException;

import java.time.LocalDateTime;
import java.util.UUID;

public class Notification extends Entity<Long> {
    private final UUID fromUser;
    private final UUID toUser;
    private final String title;
    private final String message;
    private final LocalDateTime date;
    private final NotificationType type;

    public Notification(Long ID, UUID fromUser, UUID toUser, String title, String message, LocalDateTime date, NotificationType type) {
        super(ID);
        this.fromUser = fromUser;
        this.toUser = toUser;
        this.title = title;
        this.message = message;
        this.date = date;
        this.type = type;
    }

    public Notification(Long ID, UUID fromUser, UUID toUser, String title, String message, LocalDateTime date, short type) {
        this(ID, fromUser, toUser, title, message, date, NotificationFactory.getType(type));
    }

    public static Notification create(UUID fromUser, UUID toUser, String title, String message, NotificationType type) throws ValidationException {
        if (title.length() > 25) {
            throw new ValidationException("Title too long for the notification");
        }
        if (message.length() > 100) {
            throw new ValidationException("Message too long for the notification");
        }
        return new Notification(0L, fromUser, toUser, title, message, LocalDateTime.now(), type);
    }

    public UUID getFromUser() {
        return fromUser;
    }

    public UUID getToUser() {
        return toUser;
    }
    public String getTitle() {
        return title;
    }

    public String getMessage() {
        return message;
    }

    public LocalDateTime getDate() {
        return date;
    }

    public NotificationType getType() {
        return type;
    }

    public short getTypeID() {
        return NotificationFactory.getTypeID(type);
    }
}
