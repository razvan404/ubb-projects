namespace JrNBALeagueRomania.models
{
    internal abstract class Entity<T>
        where T : notnull
    {
        public T ID { get; set; }

        /// <summary>
        /// Converts an entity to a string used to store that entity in files, by convention 
        /// it should contain it's important fields separated by the character ';'.
        /// </summary>
        /// <returns>The string used to store the entity in files</returns>
        public delegate string ToFileStringMethod(Entity<T> entity);
        public ToFileStringMethod Method;

        public Entity(T id, ToFileStringMethod method)
        {
            ID = id;
            Method = method;
        }        

        public override bool Equals(object? obj)
        {
            if (obj == null || obj.GetType() != GetType())
            {
                return false;
            }
            Entity<T> entity = (Entity<T>)obj;
            return ID.Equals(entity.ID);
        }

        public string ToFileString()
        {
            return Method(this);
        }

        public override int GetHashCode()
        {
            return ID.GetHashCode();
        }
    }
}
