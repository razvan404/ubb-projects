using System;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Threading.Tasks;

namespace OnwardTravel.Networking
{
    public abstract class AbstractServer
    {
        private TcpListener server;
        private string host;
        private int port;
        public AbstractServer(string host, int port)
        {
            this.host = host;
            this.port = port;
        }
        public void Start()
        {
            IPAddress adr = IPAddress.Parse(host);
            IPEndPoint ep = new IPEndPoint(adr, port);
            server = new TcpListener(ep);
            server.Start();

            Task.Run(() =>
            {
                while (true)
                {
                    Console.WriteLine("Waiting for clients ...");
                    TcpClient client = server.AcceptTcpClient();
                    Console.WriteLine("Client connected ...");
                    ProcessRequest(client);
                }
            });
        }

        public abstract void ProcessRequest(TcpClient client);
    }

    public abstract class ConcurrentServer 
        : AbstractServer
    {
        public ConcurrentServer(string host, int port)
            : base(host, port) { }

        public override void ProcessRequest(TcpClient client)
        {
            Thread thr = CreateWorker(client);
            thr.Start();
        }

        protected abstract Thread CreateWorker(TcpClient client);
    }
}
