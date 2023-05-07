using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Threading;
using System.Threading.Tasks;
using Google.Protobuf;
using OnwardTravel.Models;
using OnwardTravel.Networking;
using OnwardTravel.Services;
using OnwardTravel.Services.Observer;

namespace OnwardTravel.Server
{
    internal class ProtoClientWorker : IOnwardObserver
    {
        private User userWorker;
        private readonly IOnwardService service;
        private TcpClient connection;

        private NetworkStream stream;
        private volatile bool connected;

        public ProtoClientWorker(IOnwardService service, TcpClient connection)
        {
            this.service = service;
            this.connection = connection;

            try
            {
                stream = connection.GetStream();
                connected = true;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.StackTrace);
            }
        }

        private void sendResponse(OnwardResponse response)
        {
            try
            {
                Console.WriteLine("Sending response " + response);
                response.WriteDelimitedTo(stream);
                stream.Flush();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.StackTrace);
            }
        }

        public virtual void Run()
        {
            while (connected)
            {
                try
                {
                    OnwardRequest request = OnwardRequest.Parser.ParseDelimitedFrom(stream);
                    OnwardResponse response = handleRequest(request);
                    if (response != null)
                    {
                        sendResponse(response);
                    }
                }
                catch (Exception e)
                {
                    Console.WriteLine("Error " + e);
                    if (userWorker != null) service.TryLogout(userWorker, this);
                    break;
                }

                try
                {
                    Thread.Sleep(10);
                }
                catch (Exception e)
                {
                    Console.WriteLine(e.StackTrace);
                }
            }
            try
            {
                Console.WriteLine("Connection closed ...");
                stream.Close();
                connection.Close();
            }
            catch (Exception e)
            {
                Console.WriteLine("Error " + e);
            }
        }

        private OnwardResponse handleRequest(OnwardRequest request)
        {
            switch (request.Type)
            {
                case OnwardRequest.Types.RequestType.Login:
                    try
                    {
                        Console.WriteLine("Login request ...");
                        string username = request.Username;
                        string password = request.Password;
                        User user = null;
                        lock (service)
                        {
                            user = service.TryLogin(username, password, this);
                            userWorker = user;
                        }
                        return new OnwardResponse
                        { 
                            Type = OnwardResponse.Types.ResponseType.Login,
                            User = ProtoUtils.ModelToMessage(user) as UserMessage
                        };
                    }
                    catch (Exception ex)
                    {
                        return new OnwardResponse 
                        {
                            Type = OnwardResponse.Types.ResponseType.Login,
                            Error = ex.Message 
                        };
                    }
                case OnwardRequest.Types.RequestType.Logout:
                    try
                    {
                        Console.WriteLine("Logout request ...");
                        User user = ProtoUtils.MessageToModel(request.User) as User;
                        lock (service)
                        {
                            service.TryLogout(user, this);
                            userWorker = null;
                        }
                        return new OnwardResponse 
                        {
                            Type = OnwardResponse.Types.ResponseType.Empty
                        };
                    }
                    catch (Exception ex)
                    {
                        return new OnwardResponse 
                        {
                            Type = OnwardResponse.Types.ResponseType.Empty,
                            Error = ex.Message 
                        };
                    }
                case OnwardRequest.Types.RequestType.FindRides:
                    try
                    {
                        Console.WriteLine("Find all rides request ...");
                        IList<Ride> rides;
                        lock (service)
                        {
                            rides = service.FindAllRides();
                        }
                        return new OnwardResponse 
                        {
                            Type = OnwardResponse.Types.ResponseType.FindRides,
                            Rides = { rides.Select(r => ProtoUtils.ModelToMessage(r) as RideMessage) } 
                        };
                    }
                    catch (Exception ex)
                    {
                        return new OnwardResponse
                        {
                            Type = OnwardResponse.Types.ResponseType.FindRides,
                            Error = ex.Message 
                        };
                    }
                case OnwardRequest.Types.RequestType.FindEmptySeatsOnRide:
                    try
                    {
                        Console.WriteLine("Find empty seats on ride request ...");
                        Ride ride = ProtoUtils.MessageToModel(request.Ride) as Ride;
                        int emptySeats;
                        lock (service)
                        {
                            emptySeats = service.FindEmptySeatsOnRide(ride);
                        }
                        return new OnwardResponse 
                        {
                            Type = OnwardResponse.Types.ResponseType.FindEmptySeatsOnRide,
                            EmptySeats = emptySeats 
                        };
                    }
                    catch (Exception ex)
                    {
                        return new OnwardResponse 
                        { 
                            Type = OnwardResponse.Types.ResponseType.FindEmptySeatsOnRide,
                            Error = ex.Message 
                        };
                    }
                case OnwardRequest.Types.RequestType.FindRidesByDestinationAndDeparture:
                    try
                    {
                        Console.WriteLine("Find rides by destination and departure request ...");
                        string destination = request.Destination;
                        DateTime departure = (DateTime)ProtoUtils.MessageToModel(request.Departure);

                        IList<Ride> rides;
                        lock (service)
                        {
                            rides = service.FindRidesByDestinationAndDeparture(destination, departure);
                        }
                        return new OnwardResponse 
                        { 
                            Type = OnwardResponse.Types.ResponseType.FindEmptySeatsOnRide, 
                            Rides = { rides.Select(r => ProtoUtils.ModelToMessage(r) as RideMessage) } 
                        };
                    }
                    catch (Exception ex)
                    {
                        return new OnwardResponse 
                        {
                            Type = OnwardResponse.Types.ResponseType.FindEmptySeatsOnRide, 
                            Error = ex.Message 
                        };
                    }
                case OnwardRequest.Types.RequestType.FindReservationsByRide:
                    try
                    {
                        Console.WriteLine("Find reservations by ride request ...");
                        Ride ride = ProtoUtils.MessageToModel(request.Ride) as Ride;

                        ClientSeat[] clientSeats;
                        lock (service)
                        {
                            clientSeats = service.FindReservationsByRide(ride);
                        }
                        return new OnwardResponse 
                        { 
                            Type = OnwardResponse.Types.ResponseType.FindEmptySeatsOnRide, 
                            ClientSeats = { clientSeats.Select(r => ProtoUtils.ModelToMessage(r) as ClientSeatMessage) } 
                        };
                    }
                    catch (Exception ex)
                    {
                        return new OnwardResponse 
                        { 
                            Type = OnwardResponse.Types.ResponseType.FindEmptySeatsOnRide, 
                            Error = ex.Message 
                        };
                    }
                case OnwardRequest.Types.RequestType.CreateReservation:
                    try
                    {
                        Console.WriteLine("Create reservation request ...");
                        Ride ride = ProtoUtils.MessageToModel(request.Ride) as Ride;
                        string clientName = request.ClientName;
                        string phoneNumber = request.PhoneNumber;
                        int seatsCount = request.SeatsCount;

                        lock (service)
                        {
                            service.CreateReservation(ride, clientName, phoneNumber, seatsCount);
                        }
                        return new OnwardResponse 
                        { 
                            Type = OnwardResponse.Types.ResponseType.Empty
                        };
                    }
                    catch (Exception ex)
                    {
                        return new OnwardResponse 
                        {
                            Type = OnwardResponse.Types.ResponseType.Empty, 
                            Error = ex.Message
                        };
                    }
                default:
                    return null;
            }
        }

        public void HandleReservationCreated(Reservation reservation)
        {
            Console.WriteLine("Reservation created " + reservation);
            try
            {
                sendResponse(new OnwardResponse 
                {
                    Type = OnwardResponse.Types.ResponseType.ReservationCreated,
                    Reservation = ProtoUtils.ModelToMessage(reservation) as ReservationMessage 
                });
            }
            catch (Exception ex)
            {
                Console.WriteLine("Sending error: " + ex.Message);
            }
        }
    }
}
