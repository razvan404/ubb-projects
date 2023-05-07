using System;

namespace OnwardTravel.Networking.DTO
{
    [Serializable]
    public class RideInfoDTO
    {
        public string Destination { get; }
        public DateTime Departure { get; }

        public RideInfoDTO(string destination, DateTime departure)
        {
            Destination = destination;
            Departure = departure;
        }
    }
}
