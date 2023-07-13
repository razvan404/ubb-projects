package api.services.observer;

import api.services.notification.Notification;


@FunctionalInterface
public interface Observer {
    void notify(Notification notification);
}
