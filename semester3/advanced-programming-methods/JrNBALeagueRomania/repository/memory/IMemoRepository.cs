using JrNBALeagueRomania.models;

namespace JrNBALeagueRomania.repository.memory
{
    internal class IMemoRepository<ID, E> : IRepository<ID, E>
        where ID : notnull
        where E : Entity<ID>
    {
        protected readonly Dictionary<ID, E> Dict;

        public IMemoRepository()
        {
            Dict = new Dictionary<ID, E>();
        }

        public virtual E? Save(E? entity)
        {
            if (entity is null)
            {
                throw new ArgumentException("You can't save a null entity into the repository!");
            }
            if (Dict.ContainsKey(entity.ID))
            {
                return entity;
            }
            Dict.Add(entity.ID, entity);
            return null;
        }

        public E? Find(ID? identifier)
        {
            if (identifier is null)
            {
                throw new ArgumentException("There is no entity with the null identifier in the repository!");
            }
            if (!Dict.ContainsKey(identifier))
            {
                return null;
            }
            return Dict.GetValueOrDefault(identifier);
        }

        public virtual E? Update(E? entity)
        {
            if (entity is null)
            {
                throw new ArgumentException("There is no null entity to be updated in the repository!");
            }
            if (!Dict.ContainsKey(entity.ID))
            {
                return null;
            }
            E? oldEntity = Dict.GetValueOrDefault(entity.ID);
            Dict.Remove(entity.ID);
            Dict.Add(entity.ID, entity);
            return oldEntity;
        }
        public virtual E? Delete(ID? identifier)
        {
            if (identifier is null)
            {
                throw new ArgumentException("There is no entity with a null identifier to be deleted in the repository!");
            }
            if (!Dict.ContainsKey(identifier))
            {
                return null;
            }
            E? oldEntity = Dict.GetValueOrDefault(identifier);
            Dict.Remove(identifier);
            return oldEntity;
        }

        public virtual ICollection<E> FindAll()
        {
            return Dict.Values;
        }
    }
}
