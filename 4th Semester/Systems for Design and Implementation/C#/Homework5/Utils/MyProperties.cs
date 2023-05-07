using System.Collections.Generic;

namespace OnwardTravel.Utils
{
    public class MyProperties
    {
        private readonly IDictionary<string, string> _props;

        public MyProperties()
        {
            _props = new SortedList<string, string>();
        }

        public string this[string key]
        {
            get => _props[key];
            set => _props[key] = value;
        }
    }
}
