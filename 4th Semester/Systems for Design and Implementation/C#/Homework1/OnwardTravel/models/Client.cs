namespace OnwardTravel.models
{
    internal class Client : Entity<Guid>
    {
        public string Name { get; }

        public Client(Guid guid, string name)
            : base(guid)
        {
            Name = name;
        }

        public Client(string name)
        {
            Name = name;
        }
    }
}
