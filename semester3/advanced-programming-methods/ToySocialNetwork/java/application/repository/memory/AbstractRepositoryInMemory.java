package application.repository.memory;

import application.models.Entity;
import application.repository.AbstractRepository;

import java.util.*;

/**
 * The class <b>InMemoryRepository</b> contains CRUD operations with the data stored in memory.
 * @param <ID> identifier of the Entity
 * @param <E> the type of Element, should extend Entity
 */
public class AbstractRepositoryInMemory<ID, E extends Entity<ID>> implements AbstractRepository<ID, E> {
    protected Map<ID, E> entities;

    /**
     * Constructs a new InMemoryRepository
     */
    @SafeVarargs
    public AbstractRepositoryInMemory(E... entities) {
        this.entities = new HashMap<>();
        Arrays.stream(entities).forEach(entity -> this.entities.put(entity.getID(), entity));
    }

    @Override
    public Optional<E> find(ID id) throws IllegalArgumentException {
        if (id == null) {
            throw new IllegalArgumentException("The identifier must not be null.");
        }
        E entity = entities.get(id);
        if (entity == null) {
            return Optional.empty();
        }
        return Optional.of(entity);
    }

    public Collection<E> findAll() {
        return entities.values();
    }

    @Override
    public Optional<E> save(E entity) throws IllegalArgumentException {
        if (entity == null) {
            throw new IllegalArgumentException("The identifier must not be null.");
        }
        if (find(entity.getID()).isPresent()) {
            return Optional.of(entity);
        }
        entities.put(entity.getID(), entity);
        return Optional.empty();
    }

    @Override
    public Optional<E> delete(ID id) throws IllegalArgumentException {
        if (id == null) {
            throw new IllegalArgumentException("The identifier must not be null.");
        }
        Optional<E> optionalEntity = find(id);
        if (optionalEntity.isEmpty()) {
            return Optional.empty();
        }
        entities.remove(optionalEntity.get().getID());
        return optionalEntity;
    }

    @Override
    public Optional<E> update(E entity) throws IllegalArgumentException {
        if (entity == null) {
            throw new IllegalArgumentException("The entity must not be null.");
        }
        Optional<E> oldEntity = find(entity.getID());
        if (oldEntity.isEmpty()) {
            return Optional.empty();
        }
        entities.remove(oldEntity.get().getID());
        entities.put(entity.getID(), entity);
        return oldEntity;
    }

    @Override
    public int size() {
        return entities.size();
    }
}
