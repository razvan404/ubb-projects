using OnwardTravel.Models;
using System;

namespace OnwardTravel.Networking.DTO
{
    [Serializable]
    public class ReservationInfoDTO
    {
        public Ride Ride { get; }
        public string ClientName { get; }
        public string PhoneNumber { get; }
        public int SeatsCount { get; }
        
        public ReservationInfoDTO(Ride ride, string clientName, string phoneNumber, int seatsCount)
        {
            Ride = ride;
            ClientName = clientName;
            PhoneNumber = phoneNumber;
            SeatsCount = seatsCount;
        }
    }
}
