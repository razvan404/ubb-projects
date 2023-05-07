using log4net;
using log4net.Util;
using OnwardTravel.Models;
using OnwardTravel.Utils;
using System;
using System.Data;

namespace OnwardTravel.Repository.Database
{
    public class ClientDbRepository
        : IClientRepository
    {
        private readonly DbUtils DbUtils;
        private static readonly ILog Logger = LogManager.GetLogger("ClientDbRepository");

        public ClientDbRepository(MyProperties props)
        {
            DbUtils = new DbUtils(props);
        }

        public static Client ExtractClient(IDataReader dataR)
        {
            Guid guid = dataR.GetGuid(0);
            string name = dataR.GetString(1);
            string phoneNumber = dataR.GetString(2);
            return new Client(guid, name, phoneNumber);
        }

        public Guid? Save(Client entity)
        {
            Logger.InfoFormat("Saving the client: {0}", entity);
            using (var comm = DbUtils.GetConnection().CreateCommand())
            {
                comm.CommandText = "INSERT INTO clients(name, phone_number) VALUES (@name, @phone_number)";
                var paramName = comm.CreateParameter();
                paramName.ParameterName = "@name";
                paramName.Value = entity.Name;
                comm.Parameters.Add(paramName);

                var paramPhoneNumber = comm.CreateParameter();
                paramPhoneNumber.ParameterName = "@phone_number";
                paramPhoneNumber.Value = entity.PhoneNumber;
                comm.Parameters.Add(paramPhoneNumber);

                int result = comm.ExecuteNonQuery();
                if (result == 0)
                {
                    Logger.InfoExt(null);
                    return null;
                }
            }

            return FindByNameAndPhone(entity.Name, entity.PhoneNumber)?.ID;
        }

        public Client Find(Guid identifier)
        {
            Logger.InfoFormat("Finding the client with the identifier: {0}", identifier);
            using (var comm = DbUtils.GetConnection().CreateCommand())
            {
                comm.CommandText = "SELECT * FROM clients WHERE client_id = @client_id";
                var paramClientID = comm.CreateParameter();
                paramClientID.ParameterName = "@client_id";
                paramClientID.Value = identifier;
                comm.Parameters.Add(paramClientID);

                var result = DbUtils.FindQueryResults(comm, ExtractClient);
                if (result.Count == 0)
                {
                    Logger.InfoExt(null);
                    return null;
                }
                Logger.InfoExt(result[0].ID);
                return result[0];
            }
        }

        public Client Update(Client entity)
        {
            throw new NotImplementedException();
        }

        public Client Delete(Guid identifier)
        {
            throw new NotImplementedException();
        }

        public Client FindByNameAndPhone(string name, string phoneNumber)
        {
            using (var comm = DbUtils.GetConnection().CreateCommand())
            {
                comm.CommandText = "SELECT * FROM clients WHERE name = @name AND phone_number = @phone_number";
                var paramName = comm.CreateParameter();
                paramName.ParameterName = "@name";
                paramName.Value = name;
                comm.Parameters.Add(paramName);

                var paramPhoneNumber = comm.CreateParameter();
                paramPhoneNumber.ParameterName = "@phone_number";
                paramPhoneNumber.Value = phoneNumber;
                comm.Parameters.Add(paramPhoneNumber);

                var result = DbUtils.FindQueryResults(comm, ExtractClient);
                if (result.Count > 0)
                {
                    Logger.InfoExt(result[0]);
                    return result[0];
                }
                Logger.InfoExt(null);
                return null;
            }
        }
    }
}
