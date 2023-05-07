using Onward.Services.Observer;
using OnwardTravel.Models;
using OnwardTravel.Services;
using System;
using System.Collections.Generic;

namespace OnwardTravel.Client
{
    public class ClientController : IOnwardObserver
    {
        public event EventHandler<ClientEventArgs> UpdateEvent;
        private readonly IOnwardService server;
        public User CurrentUser { get; private set; }

        public ClientController(IOnwardService server)
        {
            this.server = server;
            CurrentUser = null;
        }

        public void Login(string username, string password)
        {
            CurrentUser = server.TryLogin(username, password, this);
            Console.WriteLine("Login succeeded ...");
        }

        
        public void Logout()
        {
            server.TryLogout(CurrentUser, this);
            Console.WriteLine("Logout succeeded ...");
            CurrentUser = null;
        }

        public IList<Ride> FindAllRides()
        {
            return server.FindAllRides();
        }

        public int FindEmptySeatsOnRide(Ride ride)
        {
            return server.FindEmptySeatsOnRide(ride);
        }

        public IList<Ride> FindRidesByDestinationAndDeparture(string destination, DateTime departure)
        {
            return server.FindRidesByDestinationAndDeparture(destination, departure);
        }

        public ClientSeat[] FindReservationsByRide(Ride ride)
        {
            return server.FindReservationsByRide(ride);
        }

        public void CreateReservation(Ride ride, string clientName, string phoneNumber, int seatsCount)
        {
            server.CreateReservation(ride, clientName, phoneNumber, seatsCount);
        }


        public void HandleReservationCreated(Reservation reservation)
        {
            ClientEventArgs userArgs = new ClientEventArgs(UserEvent.RESERVATION_CREATED, null);
            Console.WriteLine("Reservation created " + reservation);
            OnUserEvent(userArgs);
        }

        public virtual void OnUserEvent(ClientEventArgs ev)
        {
            if (UpdateEvent == null) return;
            UpdateEvent(this, ev);
            Console.WriteLine("Update Event called");
        }
    }
}
