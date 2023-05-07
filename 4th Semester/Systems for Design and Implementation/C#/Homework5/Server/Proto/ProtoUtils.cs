using OnwardTravel.Models;
using System;
using System.Linq;

namespace OnwardTravel.Server
{
    public static class ProtoUtils
    {
        public static object ModelToMessage(object obj)
        {
            if (obj is User user)
            {
                return new UserMessage
                {
                    Id = user.ID.ToString(),
                    Username = user.Username,
                    Password = user.Password,
                };
            }
            else if (obj is DateTime dateTime)
            {
                return new DateTimeMessage
                {
                    Year = dateTime.Year,
                    Month = dateTime.Month,
                    Day = dateTime.Day,
                    Hour = dateTime.Hour,
                    Minute = dateTime.Minute,
                };
            }
            else if (obj is Ride ride)
            {
                return new RideMessage
                {
                    Id = ride.ID.ToString(),
                    Destination = ride.Destination,
                    Departure = ModelToMessage(ride.Departure) as DateTimeMessage,
                };
            }
            else if (obj is Client client)
            {
                return new ClientMessage
                {
                    Id = client.ID.ToString(),
                    Name = client.Name,
                    PhoneNumber = client.PhoneNumber,
                };
            }
            else if (obj is ReservedSeat seat)
            {
                return new ReservedSeatMessage
                {
                    Id = seat.ID.ToString(),
                    SeatNumber = seat.SeatNumber,
                };
            }
            else if (obj is Reservation reservation)
            {
                var reservationMessage = new ReservationMessage
                {
                    Id = reservation.ID.ToString(),
                    Client = ModelToMessage(reservation.Client) as ClientMessage,
                    Ride = ModelToMessage(reservation.Ride) as RideMessage,
                };
                reservationMessage.Seats.AddRange(reservation.Seats.Select(s => ModelToMessage(s) as ReservedSeatMessage).ToList());
                return reservationMessage;
            }
            else if (obj is ClientSeat clientSeat)
            {
                return new ClientSeatMessage
                {
                    Client = ModelToMessage(clientSeat.Client) as ClientMessage,
                    Reservation = ModelToMessage(clientSeat.Reservation) as ReservationMessage,
                    ReservedSeat = ModelToMessage(clientSeat.ReservedSeat) as ReservedSeatMessage,
                };
            }
            else
            {
                return null;
            }
        }

        public static object MessageToModel(object msg)
        {
            if (msg is UserMessage userMessage)
            {
                return new User(Guid.Parse(userMessage.Id), userMessage.Username, userMessage.Password);
            }
            else if (msg is DateTimeMessage dateTimeMessage)
            {
                return new DateTime(dateTimeMessage.Year, dateTimeMessage.Month, dateTimeMessage.Day, dateTimeMessage.Hour, dateTimeMessage.Minute, 0);
            }
            else if (msg is RideMessage rideMessage)
            {
                return new Ride(
                    Guid.Parse(rideMessage.Id),
                    rideMessage.Destination,
                    (DateTime)MessageToModel(msg: rideMessage.Departure));
            }
            else if (msg is ClientMessage clientMessage)
            {
                return new Client(Guid.Parse(clientMessage.Id), clientMessage.Name, clientMessage.PhoneNumber);
            }
            else if (msg is ReservedSeatMessage seatMessage)
            {
                return new ReservedSeat(Guid.Parse(seatMessage.Id), seatMessage.SeatNumber);
            }
            else if (msg is ReservationMessage reservationMessage)
            {
                var reservation = new Reservation(
                    Guid.Parse(reservationMessage.Id), MessageToModel(reservationMessage.Client) as Client,
                    MessageToModel(reservationMessage.Ride) as Ride,
                    reservationMessage.Seats.Select(s => MessageToModel(s) as ReservedSeat).ToList());
                return reservation;
            }
            else if (msg is ClientSeatMessage clientSeatMessage)
            {
                return new ClientSeat(
                    MessageToModel(clientSeatMessage.Client) as Client,
                    MessageToModel(clientSeatMessage.Reservation) as Reservation,
                    MessageToModel(clientSeatMessage.ReservedSeat) as ReservedSeat);
            }
            else
            {
                return null;
            }
        }
    }
}
