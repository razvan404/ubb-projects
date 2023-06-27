using System.Data;
using System.Data.SqlClient;

namespace Contests.Utils
{
    internal static class DbUtils
    {
        private static readonly string ConnectionString = Program.GetConnectionStringByName("ContestsDB");
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
