﻿namespace OnwardTravel.models
{
    internal class ReservedSeat : Entity<Guid>
    {
        public int SeatNumber { get; }

        public ReservedSeat(Guid guid, int seatNumber)
            : base(guid)
        {
            SeatNumber = seatNumber;
        }

        public ReservedSeat(int seatNumber)
        {
            SeatNumber = seatNumber;
        }
    }
}
