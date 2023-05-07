package repository.hibernate;

import models.User;
import org.hibernate.Session;
import org.hibernate.Transaction;
import repository.UserRepository;
import repository.exceptions.DataChangeException;

import java.util.UUID;

public class UserHibernateRepository implements UserRepository {

    @Override
    public UUID save(User entity) {
        Transaction tx = null;
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            tx = session.beginTransaction();
            session.save(entity);
            tx.commit();
            User user = session.find(User.class, entity.getID());
            return user.getID();
        } catch (Exception ex) {
            if (tx != null) {
                tx.rollback();
            }
            return null;
        }
    }

    @Override
    public User find(UUID identifier) {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            return session.find(User.class, identifier);
        }
    }

    @Override
    public User update(User entity) {
        return null;
    }

    @Override
    public User delete(UUID identifier) {
        return null;
    }

    @Override
    public User tryLogin(String username, String password) {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            return session.createQuery("from User where username = :username and password = :password", User.class)
                    .setParameter("username", username)
                    .setParameter("password", password)
                    .uniqueResult();
        }
    }
}
