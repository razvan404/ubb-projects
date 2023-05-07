package network.dto;

import java.io.Serializable;
import java.time.LocalDate;

public record RideInfoDTO(String destination, LocalDate departure) implements Serializable {}
