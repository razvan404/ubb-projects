package api.persistence.hibernate;

import api.models.Player;
import api.persistence.PlayerRepository;
import org.hibernate.Session;
import org.springframework.stereotype.Component;

import java.util.UUID;

@Component
public class HibPlayerRepository extends HibCrudRepository<UUID, Player> implements PlayerRepository {
    @Override
    public Player findByUsernameAndPassword(String username, String password) {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            return session.createQuery("from Player where username = :username and password = :password", Player.class)
                    .setParameter("username", username)
                    .setParameter("password", password)
                    .uniqueResult();
        }
    }
}
