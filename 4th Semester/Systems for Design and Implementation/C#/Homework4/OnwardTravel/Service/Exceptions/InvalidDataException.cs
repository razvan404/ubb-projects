using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OnwardTravel.Service.Exceptions
{
    internal class InvalidDataException
        : Exception
    {
        public InvalidDataException(string msg)
            : base(msg) { }
    }
}
