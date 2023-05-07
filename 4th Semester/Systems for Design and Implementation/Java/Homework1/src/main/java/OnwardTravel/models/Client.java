package OnwardTravel.models;

import java.util.UUID;

public class Client extends Entity<UUID> {
    private final String name;

    public Client(UUID uuid, String name) {
        super(uuid);
        this.name = name;
    }

    public Client(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }
}
