using OnwardTravel.Models;
using OnwardTravel.Networking.DTO;
using System;

namespace OnwardTravel.Networking
{
    public interface IRequest {}

    [Serializable]
    public class LoginRequest : IRequest
    {
        public UserInfoDTO UserInfo { get; }
        public LoginRequest(string username, string password)
        {
            UserInfo = new UserInfoDTO(username, password);
        }
    }

    [Serializable]
    public class LogoutRequest : IRequest 
    {
        public User User { get; }
        public LogoutRequest(User user)
        {
            User = user;
        }
    }

    [Serializable]
    public class FindRidesRequest : IRequest
    {

    }

    [Serializable]
    public class FindEmptySeatsOnRideRequest : IRequest
    {
        public Ride Ride { get; }
        public FindEmptySeatsOnRideRequest(Ride ride)
        {
            Ride = ride;
        }
    }

    [Serializable]
    public class FindRidesByDestinationAndDepartureRequest : IRequest
    {
        public RideInfoDTO RideInfo { get; }
        public FindRidesByDestinationAndDepartureRequest(string destination, DateTime departure)
        {
            RideInfo = new RideInfoDTO(destination, departure);
        }
    }

    [Serializable]
    public class FindReservationsByRideRequest : IRequest
    {
        public Ride Ride { get; }
        public FindReservationsByRideRequest(Ride ride)
        {
            Ride = ride;
        }
    }

    [Serializable]
    public class CreateReservationRequest : IRequest
    {
        public ReservationInfoDTO ReservationInfo { get; } 
        public CreateReservationRequest(Ride ride, string clientName, string phoneNumber, int seatsCount)
        {
            ReservationInfo = new ReservationInfoDTO(ride, clientName, phoneNumber, seatsCount);
        }
    }
}