using Npgsql;
using System.Data;

namespace OnwardTravel.Utils.Connection
{
    public class PostgresConnectionFactory : ConnectionFactory
    {
        public override IDbConnection CreateConnection(MyProperties props)
        {
            string connectionString = props["ConnectionString"];
            return new NpgsqlConnection(connectionString);
        }
    }
}
