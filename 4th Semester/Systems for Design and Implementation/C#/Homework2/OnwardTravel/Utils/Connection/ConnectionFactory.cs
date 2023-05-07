using System.Data;
using System.Reflection;

namespace OnwardTravel.Utils.Connection
{
    internal abstract class ConnectionFactory
    {
        protected ConnectionFactory() {}

        private static ConnectionFactory Instance;

        public static ConnectionFactory GetInstance()
        {
            if (Instance == null)
            {

                Assembly assem = Assembly.GetExecutingAssembly();
                Type[] types = assem.GetTypes();
                foreach (var type in types)
                {
                    if (type.IsSubclassOf(typeof(ConnectionFactory)))
                        Instance = (ConnectionFactory)Activator.CreateInstance(type);
                }
            }
            return Instance;
        }

        public abstract IDbConnection CreateConnection(Properties props);
    }
}
