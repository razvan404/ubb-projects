using OnwardTravel.Models;

namespace OnwardTravel.Repository
{
    internal interface IReservationRepository
        : ICrudRepository<Guid, Reservation>
    {
        IList<Reservation> FindReservationsOnRide(Ride ride);
    }
}
