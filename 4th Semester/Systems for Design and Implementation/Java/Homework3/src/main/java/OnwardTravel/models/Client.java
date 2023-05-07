package OnwardTravel.models;

import java.util.UUID;

public class Client extends Entity<UUID> {
    private final String name;
    private final String phoneNumber;

    public Client(UUID uuid, String name, String phoneNumber) {
        super(uuid);
        this.name = name;
        this.phoneNumber = phoneNumber;
    }

    public Client(String name, String phoneNumber) {
        this.name = name;
        this.phoneNumber = phoneNumber;
    }

    public String getName() {
        return name;
    }
    public String getPhoneNumber() {
        return phoneNumber;
    }
}
