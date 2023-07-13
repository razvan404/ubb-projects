package api.persistence;

import api.models.Player;

import java.util.UUID;

public interface PlayerRepository extends CrudRepository<UUID, Player> {
    Player findByUsernameAndPassword(String username, String password);
}
