using System;
using System.Net.Http;
using System.Threading.Tasks;
using System.Threading;
using Newtonsoft.Json;

namespace OnwardTravel
{
    public class CSharpRestClient
    {
        static HttpClient client = new HttpClient(new LoggingHandler(new HttpClientHandler()));
        private static string URLbase = "http://localhost:8080/api/rides";
        static void Main(string[] args)
        {
            RunAsync().Wait();
        }

        static async Task RunAsync()
        {
            Console.WriteLine("Random Ride");
            Console.WriteLine(GetRideAsync(URLbase + "/7d7128f9-e01e-40e8-bc49-fb315509000a"));

            Console.WriteLine("Creating a Ride");
            Ride ride = await CreateRideAsync(URLbase, new Ride("Galati", "2023-03-30T10:30"));

            Console.WriteLine("Created Ride");
            Console.WriteLine(await GetRideAsync(URLbase + "/" + ride.ID));

            Console.WriteLine("Deleting Ride");
            await DeleteRideAsync(URLbase + "/" + ride.ID);

            Console.WriteLine("Deleted Ride");
            Console.WriteLine(await GetRideAsync(URLbase + "/" + ride.ID));
        }

        static async Task<Ride> GetRideAsync(string path)
        {
            Ride ride = null;
            HttpResponseMessage response = await client.GetAsync(path);
            if (response.IsSuccessStatusCode)
            {
                ride = await response.Content.ReadAsAsync<Ride>();
            }
            return ride;
        }


        static async Task<Ride> CreateRideAsync(string path, Ride ride)
        {
            Ride result = null;
            HttpResponseMessage response = await client.PostAsJsonAsync(path, ride);
            if (response.IsSuccessStatusCode)
            {
                result = await response.Content.ReadAsAsync<Ride>();
            }
            return result;
        }

        static async Task DeleteRideAsync(string path)
        {
            HttpResponseMessage response = await client.DeleteAsync(path);
        }

        public class Ride
        {
            [JsonProperty("id")]
            public string ID { get; set; }

            [JsonProperty("destination")]
            public string Destination { get; set; }

            [JsonProperty("departure")]
            public string Departure { get; set; }

            public Ride(string id, string destination, string departure)
            {
                ID = id;
                Destination = destination;
                Departure = departure;
            }

            public Ride(string destination, string departure)
            {
                Destination = destination;
                Departure = departure;
            }

            public Ride() { }

            public override string ToString()
            {
                return "ID: " + ID + " Destination: " + Destination + " Departure: " + Departure;
            }
        }
        
        public class LoggingHandler : DelegatingHandler
        {
            public LoggingHandler(HttpMessageHandler innerHandler)
                : base(innerHandler)
            {
            }

            protected override async Task<HttpResponseMessage> SendAsync(HttpRequestMessage request, CancellationToken cancellationToken)
            {
                Console.WriteLine("Request:");
                Console.WriteLine(request.ToString());
                if (request.Content != null)
                {
                    Console.WriteLine(await request.Content.ReadAsStringAsync());
                }
                Console.WriteLine();

                HttpResponseMessage response = await base.SendAsync(request, cancellationToken);

                Console.WriteLine("Response:");
                Console.WriteLine(response.ToString());
                if (response.Content != null)
                {
                    Console.WriteLine(await response.Content.ReadAsStringAsync());
                }
                Console.WriteLine();

                return response;
            }
        }
    }
}
