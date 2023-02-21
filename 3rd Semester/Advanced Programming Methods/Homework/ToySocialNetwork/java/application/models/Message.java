package application.models;

import application.models.exceptions.ValidationException;

import java.time.LocalDateTime;
import java.util.UUID;

public class Message extends Entity<Long> {
    private final UUID fromUser;
    private final UUID toUser;
    private final String message;
    private final LocalDateTime time;
    public Message(Long aLong, UUID fromUser, UUID toUser, String message, LocalDateTime time) {
        super(aLong);
        this.fromUser = fromUser;
        this.toUser = toUser;
        this.message = message;
        this.time = time;
    }

    public static Message create(UUID fromUser, UUID toUser, String message) throws ValidationException {
        String error = "";
        if (fromUser == null) {
            error += "The user who sends the message mustn't be null!\n";
        }
        if (toUser == null) {
            error += "The user who receives the message mustn't be null!\n";
        }
        if (message == null || message.equals("")) {
            error += "The message mustn't be null!\n";
        }
        if (message != null && message.length() > 200) {
            error += "The message limit is 200 characters!\n";
        }
        if (!error.equals("")) {
            throw new ValidationException(error.substring(0, error.length() - 1));
        }

        return new Message(0L, fromUser, toUser, message, LocalDateTime.now());
    }

    public UUID getFromUser() {
        return fromUser;
    }

    public UUID getToUser() {
        return toUser;
    }

    public String getMessage() {
        return message;
    }

    public LocalDateTime getTime() {
        return time;
    }
}
