namespace OnwardTravel.models
{
    internal class User : Entity<Guid>
    {
        public string Username { get; }
        public string Password { get; }

        public User(Guid guid, string username, string password)
            : base(guid)
        {
            Username = username;
            Password = password;
        }
    }
}
