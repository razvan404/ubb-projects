using log4net;
using log4net.Util;
using OnwardTravel.Models;
using OnwardTravel.Utils;
using System.Data;



namespace OnwardTravel.Repository.Database
{
    internal class UserDbRepository
        : IUserRepository
    {
        private readonly DbUtils DbUtils;
        private static readonly ILog Logger = LogManager.GetLogger("UserDbRepository");

        public UserDbRepository(Properties props)
        {
            DbUtils = new(props);
        }

        protected static User ExtractUser(IDataReader dataR)
        {
            Guid guid = dataR.GetGuid(0);
            string username = dataR.GetString(1);
            string password = dataR.GetString(2);
            return new User(guid, username, password);
        }

        public Guid? Save(User entity)
        {
            Logger.InfoFormat("Saving the user: {0}", entity);
            using (var comm = DbUtils.GetConnection().CreateCommand())
            {
                comm.CommandText = "INSERT INTO users(username, password) VALUES (@username, @password)";
                var paramUsername = comm.CreateParameter();
                paramUsername.ParameterName = "@username";
                paramUsername.Value = entity.Username;
                comm.Parameters.Add(paramUsername);

                var paramPassword = comm.CreateParameter();
                paramPassword.ParameterName = "@password";
                paramPassword.Value = entity.Password;
                comm.Parameters.Add(paramPassword);

                var result = comm.ExecuteNonQuery();
                if (result == 0)
                {
                    Logger.InfoExt(null);
                    return null;
                }
            }
            using (var comm = DbUtils.GetConnection().CreateCommand())
            {
                comm.CommandText = "SELECT user_id FROM users WHERE username = @username";
                var paramUsername = comm.CreateParameter();
                paramUsername.ParameterName = "@username";
                paramUsername.Value = entity.Username;
                comm.Parameters.Add(paramUsername);

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

        public User? Find(Guid identifier)
        {
            Logger.InfoFormat("Finding the user with the identifier: {0}", identifier);
            
            using (var comm = DbUtils.GetConnection().CreateCommand())
            {
                comm.CommandText = "SELECT * FROM users WHERE user_id = @user_id";
                var paramID = comm.CreateParameter();
                paramID.ParameterName = "@user_id";
                paramID.Value = identifier;
                comm.Parameters.Add(paramID);

                var results = DbUtils.FindQueryResults(comm, ExtractUser);
                if (results.Count == 0)
                {
                    Logger.InfoExt(null);
                    return null;
                }
                var user = results[0];
                Logger.InfoExt(user);
                return user;
            }
        }

        public User? Update(User entity)
        {
            Logger.InfoFormat("Updating the user with the identifier: {0}", entity.ID);

            User? oldUser = Find(entity.ID);
            if (oldUser == null)
            {
                Logger.InfoExt(null);
                return null;
            }

            using (var comm = DbUtils.GetConnection().CreateCommand())
            {
                comm.CommandText = "UPDATE users SET username = @username, password = @password WHERE user_id = @id";
                var paramUsername = comm.CreateParameter();
                paramUsername.ParameterName = "@username";
                paramUsername.Value = entity.Username;
                comm.Parameters.Add(paramUsername);

                var paramPassword = comm.CreateParameter();
                paramPassword.ParameterName = "@password";
                paramPassword.Value = entity.Password;
                comm.Parameters.Add(paramPassword);

                var paramID = comm.CreateParameter();
                paramID.ParameterName = "@id";
                paramID.Value = entity.ID;
                comm.Parameters.Add(paramID);

                var result = comm.ExecuteNonQuery();
                if (result == 0)
                {
                    Logger.InfoExt(null);
                    return null;
                }
            }

            Logger.InfoExt(oldUser);
            return oldUser;
        }

        public User? Delete(Guid identifier)
        {
            Logger.InfoFormat("Deleting the user with the identifier: {0}", identifier);

            User? oldUser = Find(identifier);
            if (oldUser == null)
            {
                Logger.InfoExt(null);
                return null;
            }

            using (var comm = DbUtils.GetConnection().CreateCommand())
            {
                comm.CommandText = "DELETE FROM users WHERE user_id = @id";
                var paramID = comm.CreateParameter();
                paramID.ParameterName = "@id";
                paramID.Value = identifier;
                comm.Parameters.Add(paramID);

                var result = comm.ExecuteNonQuery();
                if (result == 0)
                {
                    Logger.InfoExt(null);
                    return null;
                }
            }

            Logger.InfoExt(oldUser);
            return oldUser;
        }

        public User? TryLogin(string username, string password)
        {
            Logger.InfoFormat("Trying to login the user with the username: {0}", username);

            using (var comm = DbUtils.GetConnection().CreateCommand())
            {
                comm.CommandText = "SELECT * FROM users WHERE username = @username AND password = @password";
                var paramUsername = comm.CreateParameter();
                paramUsername.ParameterName = "@username";
                paramUsername.Value = username;
                comm.Parameters.Add(paramUsername);

                var paramPassword = comm.CreateParameter();
                paramPassword.ParameterName = "@password";
                paramPassword.Value = password;
                comm.Parameters.Add(paramPassword);

                var results = DbUtils.FindQueryResults(comm, ExtractUser);
                if (results.Count == 0)
                {
                    Logger.InfoExt(null);
                    return null;
                }
                var user = results[0];
                Logger.InfoExt(user);
                return user;
            }
        }
    }
}
