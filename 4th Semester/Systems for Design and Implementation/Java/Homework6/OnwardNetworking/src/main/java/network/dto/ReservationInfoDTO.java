package network.dto;

import models.Ride;

import java.io.Serializable;

public record ReservationInfoDTO(Ride ride, String clientName, String phoneNumber,
                                 int seatsCount) implements Serializable {}
