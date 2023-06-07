package services;

public class Notification {
    private NotificationType type;
    private String notificationBody;

    public Notification() {
    }

    public Notification(NotificationType type) {
        this.type = type;
    }

    public Notification(NotificationType type, String notificationBody) {
        this.type = type;
        this.notificationBody = notificationBody;
    }

    public NotificationType getType() {
        return type;
    }

    public void setType(NotificationType type) {
        this.type = type;
    }

    public String getNotificationBody() {
        return notificationBody;
    }

    public void setNotificationBody(String notificationBody) {
        this.notificationBody = notificationBody;
    }

    @Override
    public String toString() {
        return "Notification{" +
                "type=" + type +
                ", body='" + notificationBody + '\'' +
                '}';
    }
}
