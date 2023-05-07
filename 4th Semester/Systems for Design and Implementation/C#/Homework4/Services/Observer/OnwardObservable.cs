using Onward.Services.Observer;
using OnwardTravel.Models;
using OnwardTravel.Services.Exceptions;
using System;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace OnwardTravel.Services.Observer
{
    public class OnwardObservable
    {
        private readonly IDictionary<User, IOnwardObserver> _observers;
        public OnwardObservable()
        {
            _observers = new Dictionary<User, IOnwardObserver>();
        }
        public void AddObserver(User user, IOnwardObserver observer)
        {
            if (_observers.ContainsKey(user))
            {
                throw new InvalidDataException("User already logged in!");
            }
            _observers.Add(user, observer);
        }

        public void RemoveObserver(User user, IOnwardObserver observer)
        {
            if (!_observers.ContainsKey(user))
            {
                throw new InvalidDataException("User is not logged in!");
            }
            _observers.Remove(user);
        }

        public void NotifyReservationCreated(Reservation reservation)
        {
            foreach (var obs in _observers.Values)
            {
                Task.Run(() => obs.HandleReservationCreated(reservation));
            }
        }
    }
}
