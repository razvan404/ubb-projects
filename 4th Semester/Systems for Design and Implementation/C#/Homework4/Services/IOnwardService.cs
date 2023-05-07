using Onward.Services.Observer;
using OnwardTravel.Models;
using System;
using System.Collections.Generic;

namespace OnwardTravel.Services
{
    public interface IOnwardService
    {
        User TryLogin(string username, string password, IOnwardObserver client);
        void TryLogout(User user, IOnwardObserver client);
        IList<Ride> FindAllRides();
        int FindEmptySeatsOnRide(Ride ride);
        IList<Ride> FindRidesByDestinationAndDeparture(string destination, DateTime departure);
        ClientSeat[] FindReservationsByRide(Ride ride);
        void CreateReservation(Ride ride, string clientName, string phoneNumber, int seatsCount);
    }
}