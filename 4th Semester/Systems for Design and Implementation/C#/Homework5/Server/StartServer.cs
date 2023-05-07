using OnwardTravel.Repository.Database;
using OnwardTravel.Services;
using OnwardTravel.Utils;
using System;
using System.Configuration;
using System.Threading;

namespace OnwardTravel.Server
{
    public class StartServer
    {

        public static void Main(string[] args)
        {
            MyProperties props = new MyProperties();
            props["ConnectionString"] = GetConnectionStringByName("OnwardTravelDB");
            props["ServerIP"] = GetAppSettingsByName("ServerIP");
            props["ServerHost"] = GetAppSettingsByName("ServerHost");

            var service = CreateUserService(props);
            var server = new SerialOnwardServer(props["ServerIP"], int.Parse(props["ServerHost"]), service);
            
            server.Start();
            try
            {
                Thread.Sleep(1000);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            Console.WriteLine("Server started ...");
            Console.WriteLine("Press <enter> to exit...");
            Console.ReadLine();
        }


        public static string GetConnectionStringByName(string name)
        {
            ConnectionStringSettings settings = ConfigurationManager.ConnectionStrings[name];
            return settings?.ConnectionString;
        }

        public static string GetAppSettingsByName(string name)
        {
            return ConfigurationManager.AppSettings[name];
        }

        static IOnwardService CreateUserService(MyProperties props)
        {
            var userRepository = new UserDbRepository(props);
            var clientRepository = new ClientDbRepository(props);
            var rideRepository = new RideDbRepository(props);
            var reservationRepository = new ReservationDbRepository(props);
            return new OnwardServer(userRepository, clientRepository, rideRepository, reservationRepository);
        }
    }
}