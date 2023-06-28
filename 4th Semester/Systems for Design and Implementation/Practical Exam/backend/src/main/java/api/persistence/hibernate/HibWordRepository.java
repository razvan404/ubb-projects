package api.persistence.hibernate;


import api.models.Game;
import api.models.Word;
import api.persistence.WordRepository;
import org.hibernate.Session;
import org.springframework.stereotype.Component;

import java.util.List;
import java.util.UUID;

@Component
public class HibWordRepository extends HibCrudRepository<UUID, Word> implements WordRepository {
    @Override
    public List<Word> findRandomWords(int count) {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            return session.createQuery("from Word", Word.class)
                    .setMaxResults(count)
                    .list();
        }
    }
}
