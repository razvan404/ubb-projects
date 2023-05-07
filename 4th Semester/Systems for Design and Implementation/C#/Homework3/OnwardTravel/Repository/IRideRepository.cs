using OnwardTravel.Models;
using System.Collections.Generic;
using System;

namespace OnwardTravel.Repository
{
    internal interface IRideRepository
        : ICrudRepository<Guid, Ride>
    {
        IList<Ride> FindAll();
        IList<Ride> FindByDestinationAndDeparture(string destination, DateTime departure);
    }
}
