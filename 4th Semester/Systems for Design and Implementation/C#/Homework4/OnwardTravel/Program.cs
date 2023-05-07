using OnwardTravel.GUI;
using OnwardTravel.Repository.Database;
using OnwardTravel.Service;
using OnwardTravel.Utils;
using System;
using System.Configuration;
using System.Windows.Forms;

namespace OnwardTravel
{
    internal static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            MyProperties props = new MyProperties();
            props["ConnectionString"] = GetConnectionStringByName("OnwardTravelDB");
            UserService service = CreateUserService(props);

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            LoginForm form = new LoginForm();
            form.SetService(service);
            Application.Run(form);
        }

        static string GetConnectionStringByName(string name)
        {
            ConnectionStringSettings settings = ConfigurationManager.ConnectionStrings[name];
            return settings?.ConnectionString;
        }

        static UserService CreateUserService(MyProperties props)
        {
            var userRepository = new UserDbRepository(props);
            var clientRepository = new ClientDbRepository(props);
            var rideRepository = new RideDbRepository(props);
            var reservationRepository = new ReservationDbRepository(props);
            return new UserService(userRepository, clientRepository, rideRepository, reservationRepository);
        }
    }
}
