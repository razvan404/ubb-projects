namespace OnwardTravel.Models
{
    internal class Ride : Entity<Guid>
    {
        public string Destination { get; }
        public DateTime Departure { get; }

        public Ride(Guid guid, string destination, DateTime departure)
            : base(guid)
        {
            Destination = destination;
            Departure = departure;
        }

        public Ride(string destination, DateTime departure)
        {
            Destination = destination;
            Departure = departure;
        }
    }
}
