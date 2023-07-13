package api.persistence;

import api.models.Game;
import api.models.Player;

import java.util.List;
import java.util.UUID;

public interface GameRepository extends CrudRepository<UUID, Game> {
    Game findUnfinishedGameFrom(Player player);
    List<Game> findLeaderboard();
}
