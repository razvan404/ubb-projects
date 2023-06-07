package ams;

import controllers.RidesView;
import models.Ride;
import services.*;
import utils.BlobSerializer;

import java.time.LocalDateTime;
import java.util.List;
import java.util.Objects;

public class RidesController implements NotificationSubscriber {
    private ServicesAMS server;
    private RidesView view;

    public RidesController(ServicesAMS server) {
        this.server = server;
    }

    public void setReceiver(NotificationReceiver receiver) {
        receiver.start(this);
    }

    public void setView(RidesView view) {
        this.view = view;
    }

    public void createRide(String destination, LocalDateTime departure) throws ServiceException {
       Ride ride = new Ride(destination, departure);
       server.createRide(ride);
    }

    public List<Ride> getAllRides() {
        return server.getRides();
    }

    @Override
    public void notificationReceived(Notification notification) {
        if (Objects.requireNonNull(notification.getType()) == NotificationType.RIDE_CREATED) {
            System.out.println("Ride created");
            view.handleRideCreated((Ride) BlobSerializer.fromString(notification.getNotificationBody()));
        }
    }
}
