namespace JrNBALeagueRomania.utils
{
    internal static class Tools
    {
        public static string ToAbsolutePath(string relativePath)
        {
            string currentDirectory = AppDomain.CurrentDomain.BaseDirectory;
            string rootPath = Path.Combine(currentDirectory, @"../../../" + relativePath);
            return Path.GetFullPath(rootPath);
        }
    }
}
