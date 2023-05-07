using System;
using System.Collections.Generic;

namespace OnwardTravel.Models
{
    [Serializable]
    public class Reservation : Entity<Guid>
    {
        public Client Client { get; }
        public Ride Ride { get; }
        public IList<ReservedSeat> Seats { get; }

        public Reservation(Guid guid, Client client, Ride ride, params ReservedSeat[] seats)
            : base(guid)
        {
            Client = client;
            Ride = ride;
            Seats = new List<ReservedSeat>(seats);
        }
        public Reservation(Client client, Ride ride, params ReservedSeat[] seats)
        {
            Client = client;
            Ride = ride;
            Seats = new List<ReservedSeat>(seats);
        }

        public Reservation(Guid guid, Client client, Ride ride, IList<ReservedSeat> seats)
            : base(guid)
        {
            Client = client;
            Ride = ride;
            Seats = seats;
        }
        public Reservation(Client client, Ride ride, IList<ReservedSeat> seats)
        {
            Client = client;
            Ride = ride;
            Seats = seats;
        }
    }
}
