using System;

namespace OnwardTravel.Networking.DTO
{
    [Serializable]
    public class UserInfoDTO
    {
        public string Username { get; }
        public string Password { get; }

        public UserInfoDTO(string username, string password)
        {
            Username = username;
            Password = password;
        }
    }
}
