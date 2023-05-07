using OnwardTravel.Models;
using System;
using System.Collections.Generic;

namespace OnwardTravel.Repository
{
    public interface IRideRepository
        : ICrudRepository<Guid, Ride>
    {
        IList<Ride> FindAll();
        IList<Ride> FindByDestinationAndDeparture(string destination, DateTime departure);
    }
}
