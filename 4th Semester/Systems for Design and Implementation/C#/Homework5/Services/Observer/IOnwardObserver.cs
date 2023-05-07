using OnwardTravel.Models;

namespace OnwardTravel.Services.Observer
{
    public interface IOnwardObserver
    {
        void HandleReservationCreated(Reservation reservation);
    }
}
