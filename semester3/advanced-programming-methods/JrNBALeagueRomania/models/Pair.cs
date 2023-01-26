namespace JrNBALeagueRomania.models
{
    internal class Pair<T1, T2>
    {
        public T1 First { get; set; }
        public T2 Second { get; set; }

        public Pair(T1 first, T2 second)
        {
            First = first;
            Second = second;
        }

        public override bool Equals(object? obj)
        {
            if (obj == null || obj.GetType() == GetType())
            {
                return false;
            }
            Pair<T1, T2> o = (Pair<T1, T2>) obj;
            if (First == null)
            {
                if (Second == null)
                {
                    return o.First == null && o.Second == null;
                }
                return o.First == null && Second.Equals(o.Second);
            }
            if (Second == null)
            {
                return o.Second == null && First.Equals(o.First);
            }
            return First.Equals(o.First) && Second.Equals(o.Second);
        }

        public override int GetHashCode()
        {
            return HashCode.Combine(First, Second);
        }
    }
}
