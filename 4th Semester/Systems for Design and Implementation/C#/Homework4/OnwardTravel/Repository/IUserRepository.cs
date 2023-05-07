using OnwardTravel.Models;
using System;

namespace OnwardTravel.Repository
{
    internal interface IUserRepository
        : ICrudRepository<Guid, User>
    {
        /// <summary>
        /// Returns the user with the given username and password
        /// </summary>
        /// <param name="username">The username of the user trying to log in</param>
        /// <param name="password">The password of the user trying to log in, should be encrypted</param>
        /// <returns>The user if the given data is valid, null otherwise</returns>
        User TryLogin(string username, string password);
    }
}
