package api.persistence.hibernate;

import api.models.Game;
import api.models.Player;
import api.persistence.GameRepository;
import org.hibernate.Session;
import org.springframework.stereotype.Component;

import java.util.List;
import java.util.UUID;

@Component
public class HibGameRepository extends HibCrudRepository<UUID, Game> implements GameRepository {
    @Override
    public Game findUnfinishedGameFrom(Player player) {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            return session.createQuery("from Game where player = :player and finishedAt = null order by startedAt desc", Game.class)
                    .setParameter("player", player)
                    .setMaxResults(1)
                    .uniqueResult();
        }
    }

    @Override
    public List<Game> findLeaderboard() {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            return session.createQuery("from Game where finishedAt != null order by score asc", Game.class)
                    .list();
        }
    }
}
