using System;

namespace OnwardTravel.Models
{
    [Serializable]
    public class ClientSeat
    {
        public Client Client { get; }
        public Reservation Reservation { get; }
        public ReservedSeat ReservedSeat { get; }

        public ClientSeat(Client client, Reservation reservation, ReservedSeat reservedSeat)
        {
            Client = client;
            Reservation = reservation;
            ReservedSeat = reservedSeat;
        }
    }
}
