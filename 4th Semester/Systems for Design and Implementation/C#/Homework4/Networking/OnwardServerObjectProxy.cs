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
    public class OnwardServerProxy : IOnwardService
    {
        private readonly string host;
        private readonly int port;

        private IOnwardObserver client;

        private NetworkStream stream;

        private IFormatter formatter;
        private TcpClient connection;

        private Queue<IResponse> responses;
        private volatile bool finished;
        private EventWaitHandle _waitHandle;

        public OnwardServerProxy(string host, int port)
        {
            this.host = host;
            this.port = port;
            responses = new Queue<IResponse>();
        }

        public void HandleUpdate(IUpdateResponse update)
        {
            if (update is ReservationCreatedResponse rcUpd)
            {
                Reservation reservation = rcUpd.Reservation;
                Console.WriteLine("Reservation created: " + reservation);
                try
                {
                    client.HandleReservationCreated(reservation);
                }
                catch (InvalidDataException ex)
                {
                    Console.WriteLine(ex.StackTrace);
                }
            }
        }

        public virtual void Run()
        {
            while (!finished)
            {
                try
                {
                    object response = formatter.Deserialize(stream);
                    Console.WriteLine("Response received " + response);
                    if (response is IUpdateResponse update)
                    {
                        HandleUpdate(update);
                    }
                    else
                    {
                        lock (responses)
                        {
                            responses.Enqueue((IResponse) response);
                        }
                        _waitHandle.Set();
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Reading error: " + ex);
                }
            }
        }

        private void StartReader()
        {
            Thread thr = new Thread(Run);
            thr.Start();
        }

        private void InitializeConnection()
        {
            try
            {
                connection = new TcpClient(host, port);
                stream = connection.GetStream();
                formatter = new BinaryFormatter();
                finished = false;
                _waitHandle = new AutoResetEvent(false);
                StartReader();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.StackTrace);
            }
        }

        private IResponse ReadResponse()
        {
            IResponse response = null;
            try
            {
                _waitHandle.WaitOne();
                lock (responses)
                {
                    response = responses.Dequeue();
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.StackTrace);
            }
            return response;
        }

        private void SendRequest(IRequest request)
        {
            try
            {
                formatter.Serialize(stream, request);
                stream.Flush();
            }
            catch(Exception ex)
            {
                throw new InvalidDataException("Error sending object: " + ex);
            }
        }

        private void CloseConnection()
        {
            finished = true;
            try
            {
                stream.Close();
                connection.Close();
                _waitHandle.Close();
                client = null;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.StackTrace);
            }
        }

        public virtual User TryLogin(string username, string password, IOnwardObserver client)
        {
            InitializeConnection();
            SendRequest(new LoginRequest(username, password));
            var response = ReadResponse();
            if (response is LoginResponse loginResp)
            {
                this.client = client;
                return loginResp.User;
            }
            var err = (ErrorResponse)response;
            throw new InvalidDataException(err.Message);
        }

        public void TryLogout(User user, IOnwardObserver client)
        {
            SendRequest(new LogoutRequest(user));
            var response = ReadResponse();
            if (response is ErrorResponse err)
            {
                throw new InvalidDataException(err.Message);
            }
            CloseConnection();
        }

        public IList<Ride> FindAllRides()
        {
            SendRequest(new FindRidesRequest());
            var response = ReadResponse();
            if (response is FindRidesResponse findResp)
            {
                return findResp.Rides;
            }
            var err = (ErrorResponse) response;
            throw new InvalidDataException(err.Message);
        }

        public int FindEmptySeatsOnRide(Ride ride)
        {
            SendRequest(new FindEmptySeatsOnRideRequest(ride));
            var response = ReadResponse();
            if (response is FindEmptySeatsOnRideResponse findResp)
            {
                return findResp.EmptySeats;
            }
            var err = (ErrorResponse)response;
            throw new InvalidDataException(err.Message);
        }

        public IList<Ride> FindRidesByDestinationAndDeparture(string destination, DateTime departure)
        {
            SendRequest(new FindRidesByDestinationAndDepartureRequest(destination, departure));
            var response = ReadResponse();
            if (response is FindRidesByDestinationAndDepartureResponse findResp)
            {
                return findResp.Rides;
            }

            var err = (ErrorResponse)response;
            throw new InvalidDataException(err.Message);
        }

        public ClientSeat[] FindReservationsByRide(Ride ride)
        {
            SendRequest(new FindReservationsByRideRequest(ride));
            var response = ReadResponse();
            if (response is FindReservationsByRideResponse findResp)
            {
                return findResp.ClientSeats;
            }

            var err = (ErrorResponse)response;
            throw new InvalidDataException(err.Message);
        }

        public void CreateReservation(Ride ride, string clientName, string phoneNumber, int seatsCount)
        {
            SendRequest(new CreateReservationRequest(ride, clientName, phoneNumber, seatsCount));
            var response = ReadResponse();
            if (response is ErrorResponse err)
            {
                throw new InvalidDataException(err.Message);
            }
        }
    }
}
