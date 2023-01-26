namespace JrNBALeagueRomania.utils
{
    internal static class Utils
    {
        public static string PadCenter(this string input, int totalWidth)
        {
            int spaces = totalWidth - input.Length;
            int padLeft = spaces / 2 + input.Length;
            return input.PadLeft(padLeft).PadRight(totalWidth);

        }

        public static string Times(this char input, int multiplier)
        {
            return new string(input, multiplier);
        }
    }
}
