using OnwardTravel.Models;
using System;
using System.Collections.Generic;

namespace OnwardTravel.Repository
{
    public interface IReservationRepository
        : ICrudRepository<Guid, Reservation>
    {
        IList<Reservation> FindReservationsOnRide(Ride ride);
    }
}
