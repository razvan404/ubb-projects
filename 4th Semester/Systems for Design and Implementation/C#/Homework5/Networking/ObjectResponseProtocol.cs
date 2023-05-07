using OnwardTravel.Models;
using System;
using System.Collections.Generic;

namespace OnwardTravel.Networking
{
    public interface IResponse {}

    [Serializable]
    public class OkResponse : IResponse
    {

    }

    [Serializable]
    public class ErrorResponse : IResponse
    {
        public string Message { get; }
        public ErrorResponse(string message)
        {
            Message = message;
        }
    }

    public interface IUpdateResponse : IResponse { }


    [Serializable]
    public class ReservationCreatedResponse : IUpdateResponse
    {
        public Reservation Reservation { get; }
        public ReservationCreatedResponse(Reservation reservation)
        {
            Reservation = reservation;
        }
    }

    [Serializable]
    public class LoginResponse : OkResponse
    {
        public User User { get; }
        public LoginResponse(User user)
        {
            User = user;
        }
    }


    [Serializable]
    public class FindRidesResponse : OkResponse
    {
        public IList<Ride> Rides { get; }
        public FindRidesResponse(IList<Ride> rides)
        {
            Rides = rides;
        }
    }

    [Serializable]
    public class FindEmptySeatsOnRideResponse : OkResponse
    {
        public int EmptySeats { get; }
        public FindEmptySeatsOnRideResponse(int emptySeats)
        {
            EmptySeats = emptySeats;
        }
    }

    [Serializable]
    public class FindRidesByDestinationAndDepartureResponse : OkResponse
    {
        public IList<Ride> Rides { get; }
        public FindRidesByDestinationAndDepartureResponse(IList<Ride> rides)
        {
            Rides = rides;
        }
    }

    [Serializable]
    public class FindReservationsByRideResponse : OkResponse
    {
        public ClientSeat[] ClientSeats { get; }
        public FindReservationsByRideResponse(ClientSeat[] clientSeats)
        {
            ClientSeats = clientSeats;
        }
    }
}
