using OnwardTravel.Models;

namespace OnwardTravel.Repository
{
    internal interface ICrudRepository<ID, E>
        where E : Entity<ID>
        where ID : struct
    {
        /// <summary>
        /// Saves an entity into the Repository
        /// </summary>
        /// <param name="entity">the entity to be saved</param>
        /// <returns>the identifier of the saved entity, null if the entity could not be saved</returns>
        ID? Save(E entity);

        /// <summary>
        /// Finds an entity in the Repository by its identifier
        /// </summary>
        /// <param name="identifier">the identifier of the entity to be found</param>
        /// <returns>the entity with the given identiier, null if there is no such entity</returns>
        E Find(ID identifier);

        /// <summary>
        /// Updates an entity in the Repository
        /// </summary>
        /// <param name="entity">the new entity, having the identifier of the entity to be updated</param>
        /// <returns>the old entity if the update is successfully done, null otherwise</returns>
        E Update(E entity);

        /// <summary>
        /// Deletes an entity from the Repository
        /// </summary>
        /// <param name="identifier">the identifier of the entity to be deleted</param>
        /// <returns>the old entity if the deletion is successfully done, null otherwise</returns>
        E Delete(ID identifier);
    }
}
