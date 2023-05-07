using Onward.Services.Observer;
using OnwardTravel.Models;
using OnwardTravel.Services;
using OnwardTravel.Services.Exceptions;
using System;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.Threading;

namespace OnwardTravel.Networking
{
    public class OnwardClientWorker : IOnwardObserver
    {
        private IOnwardService server;
        private TcpClient connection;

        private NetworkStream stream;
        private IFormatter formatter;
        private volatile bool connected;


        public OnwardClientWorker(IOnwardService service, TcpClient connection)
        {
            server = service;
            this.connection = connection;
            try
            {
                stream = connection.GetStream();
                formatter = new BinaryFormatter();
                connected = true;
            }
            catch(Exception ex)
            {
                Console.WriteLine(ex.StackTrace);
            }
        }

        private IResponse HandleRequest(IRequest request)
        {
            if (request is LoginRequest inReq)
            {
                Console.WriteLine("Login request ...");
                var username = inReq.UserInfo.Username;
                var password = inReq.UserInfo.Password;
                try
                {
                    User user;
                    lock (server)
                    {
                        user = server.TryLogin(username, password, this);
                    }
                    return new LoginResponse(user);
                }
                catch (InvalidDataException ex)
                {
                    connected = false;
                    return new ErrorResponse(ex.Message);
                }
            }
            else if (request is LogoutRequest outReq)
            {
                Console.WriteLine("Logout request ...");
                var user = outReq.User;
                try
                {
                    lock (server)
                    {
                        server.TryLogout(user, this);
                    }
                    connected = false;
                    return new OkResponse();
                }
                catch (InvalidDataException ex)
                {
                    return new ErrorResponse(ex.Message);
                }
            }
            else if (request is FindRidesRequest)
            {
                Console.WriteLine("Find rides request ...");
                try
                {
                    IList<Ride> rides;
                    lock (server)
                    {
                        rides = server.FindAllRides();
                    }
                    return new FindRidesResponse(rides);
                }
                catch (InvalidDataException ex)
                {
                    return new ErrorResponse(ex.Message);
                }
            }
            else if (request is FindEmptySeatsOnRideRequest seatsReq)
            {
                Console.WriteLine("Find empty seats on ride request ...");
                var ride = seatsReq.Ride;
                try
                {
                    int emptySeats;
                    lock (server)
                    {
                        emptySeats = server.FindEmptySeatsOnRide(ride);
                    }
                    return new FindEmptySeatsOnRideResponse(emptySeats);
                }
                catch (InvalidDataException ex)
                {
                    return new ErrorResponse(ex.Message);
                }
            }
            else if (request is FindRidesByDestinationAndDepartureRequest rideReq)
            {
                Console.WriteLine("Find rides by destination and departure request ...");
                var destination = rideReq.RideInfo.Destination;
                var departure = rideReq.RideInfo.Departure;
                try
                {
                    IList<Ride> rides;
                    lock (server)
                    {
                        rides = server.FindRidesByDestinationAndDeparture(destination, departure);
                    }
                    return new FindRidesByDestinationAndDepartureResponse(rides);
                }
                catch (InvalidDataException ex)
                {
                    return new ErrorResponse(ex.Message);
                }
            }
            else if (request is FindReservationsByRideRequest resReq)
            {
                Console.WriteLine("Find reservations by ride request ...");
                var ride = resReq.Ride;
                try
                {
                    ClientSeat[] clientSeats;
                    lock (server)
                    {
                        clientSeats = server.FindReservationsByRide(ride);
                    }
                    return new FindReservationsByRideResponse(clientSeats);
                }
                catch (InvalidDataException ex)
                {
                    return new ErrorResponse(ex.Message);
                }
            }
            else if (request is CreateReservationRequest creatReq)
            {
                Console.WriteLine("Create reservation request ...");
                var ride = creatReq.ReservationInfo.Ride;
                var clientName = creatReq.ReservationInfo.ClientName;
                var phoneNumber = creatReq.ReservationInfo.PhoneNumber;
                var seatsCount = creatReq.ReservationInfo.SeatsCount;
                try
                {
                    lock(server)
                    {
                        server.CreateReservation(ride, clientName, phoneNumber, seatsCount);
                    }
                    return new OkResponse();
                }
                catch (InvalidDataException ex)
                {
                    return new ErrorResponse(ex.Message);
                }
            }
            return null;
        }

        private void SendResponse(IResponse response)
        {
            Console.WriteLine("Sending response ..." + response);
            lock (stream)
            {
                formatter.Serialize(stream, response);
                stream.Flush();
            }
        }

        public virtual void Run()
        {
            while (connected)
            {
                try
                {
                    var request = formatter.Deserialize(stream);
                    var response = HandleRequest((IRequest)request);
                    if (response != null)
                    {
                        SendResponse(response);
                    }
                }
                catch (Exception ex)
                {
                    
                    Console.WriteLine(ex.StackTrace);
                }

                try
                {
                    Thread.Sleep(50);
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.StackTrace);
                }
            }
            try
            {
                stream.Close();
                connection.Close();
            }
            catch (Exception ex)
            {
                Console.WriteLine("Error" + ex);
            }
        }

        public void HandleReservationCreated(Reservation reservation)
        {
            Console.WriteLine("Reservation created " + reservation);
            try
            {
                SendResponse(new ReservationCreatedResponse(reservation));
            }
            catch (Exception ex) 
            {
                Console.WriteLine("Sending error: " + ex.Message);
            }
        }
    }
}
