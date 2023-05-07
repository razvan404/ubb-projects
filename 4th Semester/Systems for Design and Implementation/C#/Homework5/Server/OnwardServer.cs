using OnwardTravel.Models;
using OnwardTravel.Services;
using OnwardTravel.Repository;
using OnwardTravel.Services.Observer;
using OnwardTravel.Utils;
using System.Collections.Generic;
using OnwardTravel.Services.Exceptions;
using System;

namespace OnwardTravel.Server
{
    public class OnwardServer : OnwardObservable, IOnwardService
    {
        private readonly IUserRepository _userRepository;
        private readonly IClientRepository _clientRepository;
        private readonly IRideRepository _rideRepository;
        private readonly IReservationRepository _reservationRepository;

        public OnwardServer(IUserRepository userRepository, IClientRepository clientRepository,
            IRideRepository rideRepository, IReservationRepository reservationRepository)
        {
            _userRepository = userRepository;
            _clientRepository = clientRepository;
            _rideRepository = rideRepository;
            _reservationRepository = reservationRepository;
        }

        public User TryLogin(string username, string password, IOnwardObserver userObserver)
        {
            User user = _userRepository.TryLogin(username, password)
                ?? throw new InvalidDataException("Invalid username or password!");
            AddObserver(user, userObserver);
            return user;
        }

        public void TryLogout(User user, IOnwardObserver userObserver)
        {
            RemoveObserver(user, userObserver);
        }

        public IList<Ride> FindAllRides()
        {
            return _rideRepository.FindAll();
        }

        public int FindEmptySeatsOnRide(Ride ride)
        {
            int occupiedSeatsCount = 0;
            foreach (Reservation reservation in _reservationRepository.FindReservationsOnRide(ride))
            {
                occupiedSeatsCount += reservation.Seats.Count;
            }
            return 18 - occupiedSeatsCount;
        }

        public IList<Ride> FindRidesByDestinationAndDeparture(string destination, DateTime departure)
        {
            return _rideRepository.FindByDestinationAndDeparture(destination, departure);
        }

        public ClientSeat[] FindReservationsByRide(Ride ride)
        {
            ClientSeat[] occupiedSeats = new ClientSeat[18];
            foreach (Reservation reservation in _reservationRepository.FindReservationsOnRide(ride))
            {
                foreach (ReservedSeat reservedSeat in reservation.Seats)
                {
                    occupiedSeats[reservedSeat.SeatNumber - 1] = new ClientSeat(reservation.Client, reservation, reservedSeat);
                }
            }
            for (int i = 0; i < 18; ++i)
            {
                if (occupiedSeats[i] == null)
                {
                    occupiedSeats[i] = new ClientSeat(null, null, new ReservedSeat(i + 1));
                }
            }
            return occupiedSeats;
        }

        public void CreateReservation(Ride ride, string clientName, string phoneNumber, int seatsCount)
        {
            if (ride == null)
            {
                throw new InvalidDataException("Cannot create a reservation if there is no ride selected!");
            }
            if (clientName == null || clientName.Length == 0)
            {
                throw new InvalidDataException("Invalid name!");
            }
            if (phoneNumber == null || phoneNumber.Length == 0)
            {
                throw new InvalidDataException("Invalid phone number!");
            }
            try
            {
                int.Parse(phoneNumber);
            }
            catch (FormatException)
            {
                throw new InvalidDataException("Invalid phone number!");

            }

            if (seatsCount < 1 || seatsCount > FindEmptySeatsOnRide(ride))
            {
                throw new InvalidDataException("Invalid number of seats!");
            }

            Client client = _clientRepository.FindByNameAndPhone(clientName, phoneNumber);
            if (client == null)
            {
                client = new Client(clientName, phoneNumber);
                Guid? id = _clientRepository.Save(client);
                if (id == null)
                {
                    throw new InvalidDataException("Cannot save the client!");
                }
                else
                {
                    client.ID = (Guid)id;
                }
            }

            IList<ReservedSeat> seatsToReserve = new List<ReservedSeat>();
            foreach (ClientSeat clientSeat in FindReservationsByRide(ride))
            {
                if (clientSeat.Client == null)
                {
                    seatsToReserve.Add(clientSeat.ReservedSeat);
                    if (seatsToReserve.Count == seatsCount)
                    {
                        break;
                    }
                }
            }

            Reservation reservation = new Reservation(client, ride, seatsToReserve);
            _reservationRepository.Save(reservation);
            NotifyReservationCreated(reservation);
        }
    }
}
