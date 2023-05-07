namespace OnwardTravel.models
{
    internal class Entity<T>
    {
        public T? ID { get; set; }
        public Entity(T iD)
        {
            ID = iD;
        }
        public Entity() {}
    }
}
