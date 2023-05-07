using OnwardTravel.Models;

namespace OnwardTravel.Repository
{
    internal interface IRideRepository
        : ICrudRepository<Guid, Ride>
    {
        IList<Ride> FindAll();
        IList<Ride> FindByDestinationAndDeparture(string destination, DateTime departure);
    }
}
