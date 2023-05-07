using System;

namespace OnwardTravel.Models
{
    [Serializable]
    public class Client : Entity<Guid>
    {
        public string Name { get; }
        public string PhoneNumber { get; }

        public Client(Guid guid, string name, string phoneNumber)
            : base(guid)
        {
            Name = name;
            PhoneNumber = phoneNumber;
        }

        public Client(string name, string phoneNumber)
        {
            Name = name;
            PhoneNumber = phoneNumber;
        }
    }
}
