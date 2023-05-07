package OnwardTravel.repository;

import OnwardTravel.models.Entity;

public interface CrudRepository<ID, E extends Entity<ID>> {
    /**
     * Saves an entity into the Repository
     * @param entity the entity to be saved
     * @return the identifier of the saved entity, null if the entity could not be saved
     */
    ID save(E entity);

    /**
     * Finds an entity in the Repository by its identifier
     * @param identifier the identifier of the entity to be found
     * @return the entity with the given identifier, null if there is no such entity
     */
    E find(ID identifier);

    /**
     * Updates an entity in the Repository
     * @param entity the new entity, having the identifier of the entity to be updated
     * @return the old entity if the update is successfully done, null otherwise
     */
    E update(E entity);

    /**
     * Deletes an entity from the Repository
     * @param identifier the identifier of the entity to be deleted
     * @return the old entity if the deletion is successfully done, null otherwise
     */
    E delete(ID identifier);
}
