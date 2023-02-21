package application.repository;

import application.models.Entity;

import java.util.Optional;

/**
 * The interface <b>Repository</b> contains only CRUD operations.
 *
 * @param <ID> type E must have an attribute of type ID
 * @param <E> type of entities saved in repository
 */
public interface AbstractRepository<ID, E extends Entity<ID>> {
    /**
     * Saves an entity in the repository
     *
     * @param entity the entity to be saved in the repository,
     *               must not be null
     * @return null if the entity was saved successfully,
     *         the entity otherwise
     * @throws IllegalArgumentException when the given entity is null
     */
    Optional<E> save(E entity) throws IllegalArgumentException;
    /**
     * Find an entity by its identifier.
     *
     * @param id the identifier of the entity to be returned,
     *           must not be null
     * @return the entity with the given identifier if it exists in the repository,
     * @throws IllegalArgumentException when the given identifier is null
     */
    Optional<E> find(ID id) throws IllegalArgumentException;

    /**
     * Removes the entity with the specified identifier
     *
     * @param id the identifier of the entity to be deleted,
     *           must not be null
     * @return the removed entity if there was an entity with the specified identifier,
     *         null otherwise
     * @throws IllegalArgumentException when the given identifier is null
     */
    Optional<E> delete(ID id) throws IllegalArgumentException;

    /**
     * Updates an entity at the specified identifier
     *
     * @param entity the updated version of the entity to be updated,
     *               must not be null
     * @return the old version of the entity if the update was successful,
     *         otherwise null
     * @throws IllegalArgumentException when one of the given arguments is null
     */
    Optional<E> update(E entity) throws IllegalArgumentException;

    /**
     * @return the number of entities in the container.
     */
    int size();
}
