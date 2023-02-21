using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace JrNBALeagueRomania.utils
{
    internal static class Files
    {
        public static string StudentsFile = Tools.ToAbsolutePath("data/students.txt");
        public static string TeamsFile = Tools.ToAbsolutePath("data/teams.txt");
        public static string PlayersFile = Tools.ToAbsolutePath("data/players.txt");
        public static string GamesFile = Tools.ToAbsolutePath("data/games.txt");
        public static string ActivePlayersFile = Tools.ToAbsolutePath("data/active-players.txt");
    }
}
