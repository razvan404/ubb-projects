package api.models;

import javax.persistence.*;
import java.time.LocalDateTime;
import java.util.UUID;


@Entity
@Table(name = "rides")
public class Ride extends Identifiable<UUID> {
    private String destination;
    private LocalDateTime departure;

    public Ride() {}
    public Ride(UUID uuid, String destination, LocalDateTime departure) {
        super(uuid);
        this.destination = destination;
        this.departure = departure;
    }

    public Ride(String destination, LocalDateTime departure) {
        this.destination = destination;
        this.departure = departure;
    }

    @Override
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    @Column(name = "ride_id", updatable = false, nullable = false)
    public UUID getID() {
        return super.getID();
    }

    @Override
    public void setID(UUID identifier) {
        super.setID(identifier);
    }

    @Column(name = "destination")
    public String getDestination() {
        return destination;
    }

    public void setDestination(String destination) {
        this.destination = destination;
    }

    @Column(name = "departure")
    public LocalDateTime getDeparture() {
        return departure;
    }

    public void setDeparture(LocalDateTime departure) {
        this.departure = departure;
    }

    @Override
    public String toString() {
        return "Ride{" +
                "id='" + getID() + '\'' +
                ", destination='" + destination + '\'' +
                ", departure=" + departure +
                '}';
    }
}
