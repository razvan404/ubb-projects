using OnwardTravel.Models;
using System.Collections.Generic;
using System;

namespace OnwardTravel.Repository
{
    internal interface IReservationRepository
        : ICrudRepository<Guid, Reservation>
    {
        IList<Reservation> FindReservationsOnRide(Ride ride);
    }
}
