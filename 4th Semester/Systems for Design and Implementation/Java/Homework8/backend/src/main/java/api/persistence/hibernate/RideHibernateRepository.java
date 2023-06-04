package api.persistence.hibernate;

import api.models.Ride;
import api.persistence.RideRepository;
import org.hibernate.Session;
import org.hibernate.Transaction;

import java.time.LocalDate;
import java.util.List;
import java.util.UUID;

public class RideHibernateRepository implements RideRepository {
    @Override
    public UUID save(Ride entity) {
        Transaction tx = null;
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            Ride ride = session.createQuery("from Ride where destination = :destination and departure = :departure", Ride.class)
                    .setParameter("destination", entity.getDestination())
                    .setParameter("departure", entity.getDeparture())
                    .uniqueResult();
            if (ride != null) {
                return null;
            }
            tx = session.beginTransaction();
            session.save(entity);
            UUID id = entity.getID();
            tx.commit();
            return id;
        } catch (Exception ex) {
            if (tx != null) {
                tx.rollback();
            }
        }
        return null;
    }

    @Override
    public Ride find(UUID identifier) {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            return session.find(Ride.class, identifier);
        }
    }

    @Override
    public Ride update(Ride entity) {
        Transaction tx = null;
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            tx = session.beginTransaction();
            session.update(entity);
            tx.commit();
            return session.find(Ride.class, entity.getID());
        } catch (Exception ex) {
            if (tx != null) {
                tx.rollback();
            }
            return null;
        }
    }

    @Override
    public Ride delete(UUID identifier) {
        Ride toDelete = find(identifier);
        Transaction tx = null;
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            tx = session.beginTransaction();
            session.delete(toDelete);
            tx.commit();
            return toDelete;
        } catch (Exception ex) {
            if (tx != null) {
                tx.rollback();
            }
            return null;
        }
    }

    @Override
    public List<Ride> findAll() {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            return session.createQuery("from Ride", Ride.class).list();
        }
    }

    @Override
    public List<Ride> findByDestinationAndDeparture(String destination, LocalDate departure) {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            return session.createQuery("from Ride where destination = :destination and departure = :departure", Ride.class)
                    .setParameter("destination", destination)
                    .setParameter("departure", departure)
                    .list();
        }
    }
}
