namespace OnwardTravel.Models
{
    internal class ClientSeatDTO
    {
        public Client Client { get; }
        public Reservation Reservation { get; }
        public ReservedSeat ReservedSeat { get; }

        public ClientSeatDTO(Client client, Reservation reservation, ReservedSeat reservedSeat)
        {
            Client = client;
            Reservation = reservation;
            ReservedSeat = reservedSeat;
        }
    }
}
