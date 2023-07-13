package api.persistence.hibernate;

import api.models.Player;
import api.persistence.PlayerRepository;
import org.hibernate.Session;
import org.springframework.stereotype.Component;

import java.util.UUID;

@Component
public class HibPlayerRepository extends HibCrudRepository<UUID, Player> implements PlayerRepository {
    @Override
    public Player findByAlias(String alias) {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            return session.createQuery("from Player where alias = :alias", Player.class)
                    .setParameter("alias", alias)
                    .uniqueResult();
        }
    }
}
