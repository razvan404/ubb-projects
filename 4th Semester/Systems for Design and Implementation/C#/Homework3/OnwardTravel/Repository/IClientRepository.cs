using OnwardTravel.Models;
using System;

namespace OnwardTravel.Repository
{
    internal interface IClientRepository
        : ICrudRepository<Guid, Client>
    {
        Client FindByNameAndPhone(string name, string phoneNumber);
    }
}
