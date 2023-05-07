using OnwardTravel.Models;

namespace OnwardTravel.Repository
{
    internal interface IClientRepository
        : ICrudRepository<Guid, Client>
    {
    }
}
