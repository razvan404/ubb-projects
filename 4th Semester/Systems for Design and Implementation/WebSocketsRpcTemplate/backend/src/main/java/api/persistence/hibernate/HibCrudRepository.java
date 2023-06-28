package api.persistence.hibernate;

import api.models.Identifiable;
import api.persistence.CrudRepository;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.hibernate.Session;
import org.hibernate.Transaction;

import java.io.Serializable;
import java.lang.reflect.ParameterizedType;
import java.util.List;

public abstract class HibCrudRepository<ID extends Serializable, E extends Identifiable<ID>> implements CrudRepository<ID, E> {
    private final Class<E> type;
    protected static final Logger logger = LogManager.getLogger();

    @SuppressWarnings("unchecked")
    public HibCrudRepository() {
        type = (Class<E>) ((ParameterizedType) getClass().getGenericSuperclass()).getActualTypeArguments()[1];
        logger.info("HibernateCrudRepository for {} created.", type.getSimpleName());
    }

    @Override
    public E findOne(ID id) {
        logger.traceEntry("findOne({}): {}", id, type.getSimpleName());
        logger.info("Entering findOne({}): {}...", id, type.getSimpleName());
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            E entity = session.find(type, id);
            logger.info("Exiting findOne({}): {}...", id, entity);
            return logger.traceExit(entity);
        }
    }

    @Override
    public List<E> findAll() {
        logger.traceEntry("findAll(): {}[]", type.getSimpleName());
        logger.info("findAll(): {}[]", type.getSimpleName());
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            List<E> entities = session.createQuery("from " + type.getSimpleName(), type).list();
            logger.info("Exiting findAll(): {}", entities);
            return logger.traceExit(entities);
        }
    }

    @Override
    public E save(E entity) {
        logger.traceEntry("save({}): {}", entity, type.getSimpleName());
        logger.info("save({}): {}", entity, type.getSimpleName());
        Transaction tx = null;
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            tx = session.beginTransaction();
            session.persist(entity);
            tx.commit();
            logger.info("Exiting save({}): {}", entity, entity);
            return logger.traceExit(entity);
        } catch (Exception ex) {
            System.err.println(ex.getMessage());
            if (tx != null) {
                tx.rollback();
            }
        }
        logger.info("Exiting save({}): {}", entity, null);
        return logger.traceExit((E) null);
    }

    @Override
    public E update(E entity) {
        logger.traceEntry("update({}): {}", entity, type.getSimpleName());
        logger.info("update({}): {}", entity, type.getSimpleName());
        Transaction tx = null;
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            tx = session.beginTransaction();
            session.merge(entity);
            tx.commit();
            logger.info("Exiting update({}): {}", entity, entity);
            return logger.traceExit(entity);
        } catch (Exception ex) {
            System.err.println(ex.getMessage());
            if (tx != null) {
                tx.rollback();
            }
        }
        logger.info("Exiting update({}): {}", entity, null);
        return logger.traceExit((E) null);
    }

    @Override
    public E delete(ID id) {
        logger.traceEntry("delete({}): {}", id, type.getSimpleName());
        logger.info("delete({}): {}", id, type.getSimpleName());
        Transaction tx = null;
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            tx = session.beginTransaction();
            E entity = session.find(type, id);
            session.remove(entity);
            tx.commit();
            logger.info("Exiting delete({}): {}", id, entity);
            return logger.traceExit(entity);
        } catch (Exception ex) {
            System.err.println(ex.getMessage());
            if (tx != null) {
                tx.rollback();
            }
        }
        logger.info("Exiting delete({}): {}", id, null);
        return logger.traceExit((E) null);
    }
}
