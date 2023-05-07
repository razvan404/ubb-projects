using log4net;
using log4net.Util;
using OnwardTravel.Models;
using OnwardTravel.Utils;
using System;
using System.Collections.Generic;

namespace OnwardTravel.Repository.Database
{
    public class ReservationDbRepository
        : IReservationRepository
    {
        private readonly DbUtils DbUtils;
        private static readonly ILog Logger = LogManager.GetLogger("ReservationDbRepository");

        public ReservationDbRepository(MyProperties props)
        {
            DbUtils = new DbUtils(props);
        }

        public Guid? Save(Reservation entity)
        {
            Guid? reservationID = null;
            Logger.InfoFormat("Saving the reservation: {0}", entity);
            using (var comm0 = DbUtils.GetConnection().CreateCommand())
            {
                comm0.CommandText = "SELECT reservation_id FROM Reservations WHERE client_id = @client_id AND ride_id = @ride_id";
                var paramClientID = comm0.CreateParameter();
                paramClientID.ParameterName = "@client_id";
                paramClientID.Value = entity.Client.ID;
                comm0.Parameters.Add(paramClientID);

                var paramRideID = comm0.CreateParameter();
                paramRideID.ParameterName = "@ride_id";
                paramRideID.Value = entity.Ride.ID;
                comm0.Parameters.Add(paramRideID);

                var result = DbUtils.FindQueryResults(comm0, DbUtils.ExtractGuid);
                if (result.Count != 0)
                {
                    reservationID = result[0];
                }
            }
            using (var comm = DbUtils.GetConnection().CreateCommand())
            {
                if (reservationID == null)
                {
                    comm.CommandText = "INSERT INTO reservations(client_id, ride_id) VALUES (@client_id, @ride_id)";
                    var paramClientID = comm.CreateParameter();
                    paramClientID.ParameterName = "@client_id";
                    paramClientID.Value = entity.Client.ID;
                    comm.Parameters.Add(paramClientID);

                    var paramRideID = comm.CreateParameter();
                    paramRideID.ParameterName = "@ride_id";
                    paramRideID.Value = entity.Ride.ID;
                    comm.Parameters.Add(paramRideID);

                    if (comm.ExecuteNonQuery() == 0)
                    {
                        Logger.InfoExt(null);
                        return null;
                    }
                }
            }
            using (var comm1 = DbUtils.GetConnection().CreateCommand())
            {
                if (reservationID == null)
                {
                    comm1.CommandText = "SELECT reservation_id FROM Reservations WHERE client_id = @client_id AND ride_id = @ride_id";
                    var paramClientID = comm1.CreateParameter();
                    paramClientID.ParameterName = "@client_id";
                    paramClientID.Value = entity.Client.ID;
                    comm1.Parameters.Add(paramClientID);

                    var paramRideID = comm1.CreateParameter();
                    paramRideID.ParameterName = "@ride_id";
                    paramRideID.Value = entity.Ride.ID;
                    comm1.Parameters.Add(paramRideID);

                    var result = DbUtils.FindQueryResults(comm1, DbUtils.ExtractGuid);
                    if (result.Count == 0)
                    {
                        Logger.InfoExt(null);
                        return null;
                    }
                    reservationID = result[0];
                }
            }
            using (var comm2 = DbUtils.GetConnection().CreateCommand())
            {
                comm2.CommandText = "INSERT INTO reserved_seats(reservation_id, seat_number) VALUES (@reservation_id, @seat_number)";
                var paramReservationID = comm2.CreateParameter();
                paramReservationID.ParameterName = "@reservation_id";
                paramReservationID.Value = reservationID;
                comm2.Parameters.Add(paramReservationID);

                foreach (var seat in entity.Seats)
                {
                    var paramSeatID = comm2.CreateParameter();
                    paramSeatID.ParameterName = "@seat_number";
                    paramSeatID.Value = seat.SeatNumber;
                    comm2.Parameters.Add(paramSeatID);

                    comm2.ExecuteNonQuery();
                    comm2.Parameters.Remove(paramSeatID);
                }
            }

            Logger.InfoExt(reservationID);
            return reservationID;
        }

        public Reservation Find(Guid identifier)
        {
            throw new NotImplementedException();
        }

        public Reservation Update(Reservation entity)
        {
            throw new NotImplementedException();
        }

        public Reservation Delete(Guid identifier)
        {
            throw new NotImplementedException();
        }

        public IList<Reservation> FindReservationsOnRide(Ride ride)
        {
            Logger.InfoFormat("Finding the reservations for the ride: {0}", ride);

            IList<Guid> reservationIDs = new List<Guid>();
            IList<Guid> clientIDs = new List<Guid>();

            IList<Reservation> reservations = new List<Reservation>();
            using (var comm1 = DbUtils.GetConnection().CreateCommand())
            {
                comm1.CommandText = "SELECT reservation_id, client_id FROM reservations WHERE ride_id = @ride_id";
                var paramRideID = comm1.CreateParameter();
                paramRideID.ParameterName = "@ride_id";
                paramRideID.Value = ride.ID;
                comm1.Parameters.Add(paramRideID);

                using (var dataR1 = comm1.ExecuteReader())
                {
                    while (dataR1.Read())
                    {
                        reservationIDs.Add(dataR1.GetGuid(0));
                        clientIDs.Add(dataR1.GetGuid(1));
                    }
                }
            }

            for (int i = 0; i < reservationIDs.Count; ++i)
            {
                Client client = null;
                using (var comm2 = DbUtils.GetConnection().CreateCommand())
                {
                    comm2.CommandText = "SELECT * FROM clients WHERE client_id = @client_id";
                    var paramClientID = comm2.CreateParameter();
                    paramClientID.ParameterName = "@client_id";
                    paramClientID.Value = clientIDs[i];
                    comm2.Parameters.Add(paramClientID);

                    using (var dataR2 = comm2.ExecuteReader())
                    {
                        if (dataR2.Read())
                        {
                            client = ClientDbRepository.ExtractClient(dataR2);
                        }
                    }
                }
                if (client == null)
                {
                    continue;
                }

                IList<ReservedSeat> seats = new List<ReservedSeat>();
                using (var comm3 = DbUtils.GetConnection().CreateCommand())
                {
                    comm3.CommandText = "SELECT reserved_seat_id, seat_number FROM reserved_seats WHERE reservation_id = @reservation_id";
                    var paramReservationID = comm3.CreateParameter();
                    paramReservationID.ParameterName = "@reservation_id";
                    paramReservationID.Value = reservationIDs[i];
                    comm3.Parameters.Add(paramReservationID);

                    using (var dataR3 = comm3.ExecuteReader())
                    {
                        while (dataR3.Read())
                        {
                            Guid guid = dataR3.GetGuid(0);
                            int seatNumber = dataR3.GetInt32(1);
                            seats.Add(new ReservedSeat(guid, seatNumber));
                        }
                    }
                }
                reservations.Add(new Reservation(reservationIDs[i], client, ride, seats));
            }
            Logger.InfoExt(reservations);
            return reservations;
        }
    }
}
