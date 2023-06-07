package server;

import models.Ride;
import persistence.RideRepository;
import services.NotificationService;
import services.ServicesAMS;

import java.util.List;

public class ServerAMSImpl implements ServicesAMS {
    private final RideRepository rideRepository;
    private final NotificationService notificationService;
    public ServerAMSImpl(RideRepository rideRepository, NotificationService notificationService) {
        this.rideRepository = rideRepository;
        this.notificationService = notificationService;
    }

    @Override
    public void createRide(Ride ride) {
        rideRepository.save(ride);
        notificationService.rideCreated(ride);
    }

    @Override
    public List<Ride> getRides() {
        return rideRepository.findAll();
    }
}
