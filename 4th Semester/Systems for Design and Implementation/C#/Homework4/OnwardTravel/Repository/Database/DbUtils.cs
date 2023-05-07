using log4net;
using log4net.Util;
using OnwardTravel.Utils;
using OnwardTravel.Utils.Connection;
using System.Collections.Generic;
using System;
using System.Data;

namespace OnwardTravel.Repository.Database
{
    internal class DbUtils
    {
        private readonly MyProperties DbProps;
        private static readonly ILog Logger = LogManager.GetLogger("DbUtils");
        private IDbConnection Instance;


        public DbUtils(MyProperties props)
        {
            DbProps = props;
        }


        private IDbConnection GetNewConnection()
        {
            Logger.InfoFormat("Connecting to the database: {0}", DbProps["ConnectionString"]);
            IDbConnection connection = ConnectionFactory.GetInstance().CreateConnection(DbProps);
            Logger.InfoExt(connection);
            return connection;
        }

        public IDbConnection GetConnection()
        {
            Logger.InfoFormat("Getting a Connection to the database: {0}", DbProps["ConnectionString"]);
            if (Instance == null || Instance.State == ConnectionState.Closed)
            {
                Instance = GetNewConnection();
                Instance.Open();
            }
            Logger.InfoExt(Instance);
            return Instance;
        }

        public static IList<T> FindQueryResults<T>(IDbCommand command, Func<IDataReader, T> extractEntity)
        {
            IList<T> results = new List<T>();
            using (var dataReader = command.ExecuteReader())
            {
                while (dataReader.Read())
                {
                    results.Add(extractEntity(dataReader));
                }
            }
            return results;
        }

        public static Guid ExtractGuid(IDataReader dataR)
        {
            return dataR.GetGuid(0);
        }
    }
}
