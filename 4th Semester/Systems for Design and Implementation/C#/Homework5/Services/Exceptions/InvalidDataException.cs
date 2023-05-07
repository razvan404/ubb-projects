using System;

namespace OnwardTravel.Services.Exceptions
{
    public class InvalidDataException
        : Exception
    {
        public InvalidDataException(string msg)
            : base(msg) { }
    }
}
