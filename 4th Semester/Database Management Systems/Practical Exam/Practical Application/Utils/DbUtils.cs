using System.Data;
using System.Data.SqlClient;

namespace Practical.Utils
{
    internal static class ConnectionFactory
    {
        private static readonly string ConnectionString = Program.GetConnectionStringByName("PracticalDB");
        private static SqlConnection _instance = null;
        public static SqlConnection Connection
        {
            get
            {
                if (_instance == null || _instance.State == ConnectionState.Closed)
                {
                    _instance = new SqlConnection(ConnectionString);
                    _instance.Open();
                }
                return _instance;
            }
        }
    }
}
