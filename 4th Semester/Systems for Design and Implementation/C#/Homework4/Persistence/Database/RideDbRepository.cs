using log4net;
using log4net.Util;
using OnwardTravel.Models;
using OnwardTravel.Utils;
using System;
using System.Collections.Generic;
using System.Data;

namespace OnwardTravel.Repository.Database
{
    public class RideDbRepository
        : IRideRepository
    {
        private readonly DbUtils DbUtils;
        private static readonly ILog Logger = LogManager.GetLogger("RideDbRepository");

        public RideDbRepository(MyProperties props)
        {
            DbUtils = new DbUtils(props);
        }

        protected static Ride ExtractRide(IDataReader dataR)
        {
            Guid guid = dataR.GetGuid(0);
            string destination = dataR.GetString(1);
            DateTime departure = dataR.GetDateTime(2);
            return new Ride(guid, destination, departure);
        }

        public Guid? Save(Ride entity)
        {
            Logger.InfoFormat("Saving the ride: {0}", entity);
            using (var comm = DbUtils.GetConnection().CreateCommand())
            {
                comm.CommandText = "INSERT INTO Rides(destination, departure) VALUES (@destination, @departure)";
                var paramDestination = comm.CreateParameter();
                paramDestination.ParameterName = "@destination";
                paramDestination.Value = entity.Destination;
                comm.Parameters.Add(paramDestination);

                var paramDeparture = comm.CreateParameter();
                paramDeparture.ParameterName = "@departure";
                paramDeparture.Value = entity.Departure;
                comm.Parameters.Add(paramDeparture);

                int result = comm.ExecuteNonQuery();
                if (result == 0)
                {
                    Logger.InfoExt(null);
                    return null;
                }
            }

            using (var comm = DbUtils.GetConnection().CreateCommand())
            {
                comm.CommandText = "SELECT ride_id FROM Rides WHERE destination = @destination AND departure = @departure";
                var paramDestination = comm.CreateParameter();
                paramDestination.ParameterName = "@destination";
                paramDestination.Value = entity.Destination;
                comm.Parameters.Add(paramDestination);

                var paramDeparture = comm.CreateParameter();
                paramDeparture.ParameterName = "@departure";
                paramDeparture.Value = entity.Departure;
                comm.Parameters.Add(paramDeparture);

                var result = DbUtils.FindQueryResults(comm, DbUtils.ExtractGuid);
                if (result.Count == 0)
                {
                    Logger.InfoExt(null);
                    return null;
                }
                Logger.InfoExt(result[0]);
                return result[0];
            }
        }

        public Ride Find(Guid identifier)
        {
            throw new NotImplementedException();
        }

        public Ride Update(Ride entity)
        {
            throw new NotImplementedException();
        }

        public Ride Delete(Guid identifier)
        {
            throw new NotImplementedException();
        }

        public IList<Ride> FindAll()
        {
            using (var comm = DbUtils.GetConnection().CreateCommand())
            {
                comm.CommandText = "SELECT * FROM rides";
                return DbUtils.FindQueryResults(comm, ExtractRide);
            }
        }

        public IList<Ride> FindByDestinationAndDeparture(string destination, DateTime departure)
        {
            using (var comm = DbUtils.GetConnection().CreateCommand())
            {
                comm.CommandText = "SELECT * FROM rides WHERE destination LIKE CONCAT('%', @destination, '%') AND DATE_TRUNC('day', departure) = DATE_TRUNC('day', @departure)";
                var paramDestination = comm.CreateParameter();
                paramDestination.ParameterName = "@destination";
                paramDestination.Value = destination;
                comm.Parameters.Add(paramDestination);

                var paramDeparture = comm.CreateParameter();
                paramDeparture.ParameterName = "@departure";
                paramDeparture.Value = departure;
                comm.Parameters.Add(paramDeparture);

                return DbUtils.FindQueryResults(comm, ExtractRide);
            }
        }
    }
}
