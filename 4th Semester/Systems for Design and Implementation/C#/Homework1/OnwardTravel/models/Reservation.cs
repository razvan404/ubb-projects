namespace OnwardTravel.models
{
    internal class Reservation : Entity<Guid>
    {
        public Client Client { get; }
        public Ride Ride { get; }
        public List<ReservedSeat> Seats { get; }

        public Reservation(Guid guid, Client client, Ride ride, params ReservedSeat[] seats)
            : base(guid)
        {
            Client = client;
            Ride = ride;
            Seats = new(seats);
        }
        public Reservation(Client client, Ride ride, params ReservedSeat[] seats)
        {
            Client = client;
            Ride = ride;
            Seats = new(seats);
        }
    }
}
