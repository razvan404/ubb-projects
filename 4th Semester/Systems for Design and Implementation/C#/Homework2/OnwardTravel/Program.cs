using OnwardTravel.Models;
using OnwardTravel.Repository;
using OnwardTravel.Repository.Database;
using OnwardTravel.Utils;
using OnwardTravel.Utils.Connection;
using System.Configuration;
using System.Data;
using System.Runtime.InteropServices;

namespace OnwardTravel
{
    internal static class Program
    {
        private static readonly log4net.ILog log = log4net.LogManager.GetLogger(System.Reflection.MethodBase.GetCurrentMethod().DeclaringType);

        [STAThread]
        static void Main()
        {
            Properties props = new();
            props["ConnectionString"] = GetConnectionStringByName("onwardTravelDB");

            log.Info("Hello logging world!");
            Console.WriteLine("Hit enter");

            IUserRepository userRepository = new UserDbRepository(props);
            Console.WriteLine(userRepository.Find(Guid.Parse("39630fbb-2caa-49b8-8f48-bab8435a2781")).Username);

            //ApplicationConfiguration.Initialize();
            //Application.Run(new Interface());
        }

        static string? GetConnectionStringByName(string name)
        {
            string? returnValue = null;
            ConnectionStringSettings settings = ConfigurationManager.ConnectionStrings[name];
            if (settings != null)
                returnValue = settings.ConnectionString;
            return returnValue;
        }
    }
}