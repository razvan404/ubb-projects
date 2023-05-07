﻿using Npgsql;
using System.Data;

namespace OnwardTravel.Utils.Connection
{
    internal class PostgresConnectionFactory : ConnectionFactory
    {
        public override IDbConnection CreateConnection(Properties props)
        {
            string connectionString = props["ConnectionString"];
            return new NpgsqlConnection(connectionString);
        }
    }
}