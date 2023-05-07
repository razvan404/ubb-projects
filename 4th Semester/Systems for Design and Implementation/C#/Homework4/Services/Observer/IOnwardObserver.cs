using OnwardTravel.Models;

namespace Onward.Services.Observer
{
    public interface IOnwardObserver
    {
        void HandleReservationCreated(Reservation reservation);
    }
}
