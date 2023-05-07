using OnwardTravel.Utils;

namespace OnwardTravel.Models
{
    internal class User : Entity<Guid>
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
    }
}
