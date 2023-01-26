using JrNBALeagueRomania.models;

namespace JrNBALeagueRomania.repository
{
    internal interface IRepository<ID, E>
        where ID : notnull
        where E : Entity<ID>
    {
        /// <summary>
        /// Saves an entity to the repository.
        /// </summary>
        /// <param name="entity">The entity to be saved</param>
        /// <returns>The entity if the save was unsuccessful, null otherwise</returns>
        /// <exception cref="ArgumentException">This exception is thrown when the given argument is null</exception>
        public E? Save(E? entity);

        /// <summary>
        /// Finds an entity by its identifier.
        /// </summary>
        /// <param name="identifier">The identifier of the entity to find</param>
        /// <returns>The entity if there is one with the given identifier, null otherwise</returns>
        /// <exception cref="ArgumentException">This exception is thrown when the given argument is null</exception>
        public E? Find(ID? identifier);

        /// <summary>
        /// Updates an entity in the repository, the given entity should have the same identifier as the one to update. 
        /// </summary>
        /// <param name="entity">The entity to update</param>
        /// <returns>The old entity if the update was successful, null otherwise</returns>
        /// <exception cref="ArgumentException">This exception is thrown when the given argument is null</exception>
        public E? Update(E? entity);

        /// <summary>
        /// Deletes an entity in the repository by its identifier.
        /// </summary>
        /// <param name="identifier">The identifier of the entity to delete</param>
        /// <exception cref="ArgumentException">This exception is thrown when the given argument is null</exception>
        public E? Delete(ID? identifier);

        /// <summary>
        /// Returns the list with all the entities in the repository.
        /// </summary>
        /// <returns>The list with all the entities</returns>
        public ICollection<E> FindAll();
    }
}
