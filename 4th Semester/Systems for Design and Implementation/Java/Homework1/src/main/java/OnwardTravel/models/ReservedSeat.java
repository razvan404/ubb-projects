package OnwardTravel.models;

import java.util.UUID;

public class ReservedSeat extends Entity<UUID> {
    private final int seatNumber;

    public ReservedSeat(UUID uuid, int seatNumber) {
        super(uuid);
        this.seatNumber = seatNumber;
    }

    public int getSeatNumber() {
        return seatNumber;
    }
}
