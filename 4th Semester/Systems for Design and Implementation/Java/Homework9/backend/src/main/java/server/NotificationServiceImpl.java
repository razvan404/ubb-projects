package server;

import models.Ride;
import org.springframework.jms.core.JmsOperations;
import services.Notification;
import services.NotificationService;
import services.NotificationType;
import utils.BlobSerializer;

public class NotificationServiceImpl implements NotificationService {
    private final JmsOperations jmsOperations;

    public NotificationServiceImpl(JmsOperations operations) {
        jmsOperations = operations;
    }

    @Override
    public void rideCreated(Ride ride) {
        Notification notif = new Notification(NotificationType.RIDE_CREATED, BlobSerializer.toString(ride));
        jmsOperations.convertAndSend(notif);
        System.out.println("Sent message to ActiveMQ... " + notif);
    }
}
