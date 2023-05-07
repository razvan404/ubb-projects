using OnwardTravel.Networking;
using OnwardTravel.Services;
using System;
using System.Net.Sockets;
using System.Threading;

namespace OnwardTravel.Server
{
    public class SerialOnwardServer : ConcurrentServer
    {
        private IOnwardService Server;
        private ProtoClientWorker worker;

        public SerialOnwardServer(string host, int port, IOnwardService server)
            : base(host, port)
        {
            Server = server;
            Console.WriteLine("Serial User Server ...");
        }

        protected override Thread CreateWorker(TcpClient client)
        {
            worker = new ProtoClientWorker(Server, client);
            return new Thread(new ThreadStart(worker.Run));
        }
    }
}
