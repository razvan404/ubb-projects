using OnwardTravel.Networking;
using OnwardTravel.Services;
using OnwardTravel.Utils;
using System;
using System.Configuration;
using System.Windows.Forms;

namespace OnwardTravel.Client
{
    internal static class StartClient
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            MyProperties props = new MyProperties();
            props["ServerIP"] = GetAppSettingsByName("ServerIP");
            props["ServerHost"] = GetAppSettingsByName("ServerHost");

            IOnwardService server = new OnwardServerProxy(props["ServerIP"], int.Parse(props["ServerHost"]));
            ClientController ctrl = new ClientController(server);

            LoginForm form = new LoginForm();
            form.SetController(ctrl);
            Application.Run(form);
        }

        public static string GetAppSettingsByName(string name)
        {
            return ConfigurationManager.AppSettings[name];
        }
    }
}
