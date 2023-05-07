using OnwardTravel.Utils;
using System;

namespace OnwardTravel.Models
{
    [Serializable]
    public class User : Entity<Guid>
    {
        public string Username { get; }

        private string _password;
        public string Password
        {
            get => _password;
            set => _password = PasswordEncryptor.Encrypt(value);
        }

        public User(Guid guid, string username, string password)
            : base(guid)
        {
            Username = username;
            _password = password;
        }

        public User(string username, string password)
        {
            Username = username;
            _password = PasswordEncryptor.Encrypt(password);
        }

        public override bool Equals(object obj)
        {
            if (obj == null || !(obj is User))
            {
                return false;
            }
            User usr = (User)obj;
            return Username == usr.Username;
            
        }

        public override int GetHashCode()
        {
            return Username.GetHashCode();
        }
    }
}
