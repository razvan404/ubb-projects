using JrNBALeagueRomania.models;
using JrNBALeagueRomania.service;
using JrNBALeagueRomania.utils;
using System.Numerics;
using System.Xml.Schema;

namespace JrNBALeagueRomania.ui
{
    internal class ConsoleInterface
    {
        private readonly Service Service;

        public ConsoleInterface(Service service)
        {
            Service = service;
        }

        public void Run()
        {
            while (true)
            {
                try
                {
                    PrintGlobalMenu();
                    switch (GetInput("> "))
                    {
                        case "1":
                            PlayersFromTeam();
                            break;

                        case "2":
                            ActivePlayersFromGame();
                            break;

                        case "3":
                            GamesBetween();
                            break;

                        case "4":
                            ScoreAtGame();
                            break;

                        case "0":
                            Console.WriteLine("Have a great day!");
                            return;

                        default:
                            throw new ArgumentException("Invalid input!");
                    }
                }
                catch (Exception except)
                {
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.WriteLine(except.Message);
                    Console.ResetColor();
                }
            }
        }

        public void PrintGlobalMenu()
        {
            Console.WriteLine("+-------------------------------------------------+");
            Console.WriteLine("|              Jr NBA League Romania              |");
            Console.WriteLine("+-------------------------------------------------+");
            Console.WriteLine("| 1. Players in a given team                      |");
            Console.WriteLine("| 2. Active players who played in a given game    |");
            Console.WriteLine("| 3. Games in a given period                      |");
            Console.WriteLine("| 4. Score in a given game                        |");
            Console.WriteLine("+-------------------------------------------------+");
            Console.WriteLine("| 0. Exit the application                         |");
            Console.WriteLine("+-------------------------------------------------+");
        }

        

        public void PlayersFromTeam()
        {
            Team team = GetTeamInput("Give a team: ");

            Console.WriteLine();
            Console.WriteLine("+" + '-'.Times(81) + "+");
            Console.WriteLine("|" + ("Players from " + team).PadCenter(81) + "|");
            Console.WriteLine("+" + '-'.Times(30) + "+" + '-'.Times(50) + "+");
            Console.WriteLine("|" + "Name".PadCenter(30) + "|" + "School".PadCenter(50) + "|");
            Console.WriteLine("+" + '-'.Times(30) + "+" + '-'.Times(50) + "+");
            foreach (Player player in Service.PlayersFromTeam(team))
            {
                Console.WriteLine("|" + player.Name.PadCenter(30) + "|" + player.School.PadCenter(50) + "|");
            }
            Console.WriteLine("+" + '-'.Times(30) + "+" + '-'.Times(50) + "+");
            Console.WriteLine();
        }

        public void ActivePlayersFromGame()
        {
            Team team = GetTeamInput("Give a team: ");
            Game game = GetGameFromTeamInput(team);

            Console.WriteLine();
            Console.WriteLine("+" + '-'.Times(112) + "+");
            Console.WriteLine("|" + ("Active players from " + team + " (" + game + ")").PadCenter(112) + "|");
            Console.WriteLine("+" + '-'.Times(30) + "+" + '-'.Times(50) + "+" + '-'.Times(8) + "+" + '-'.Times(21) + "+");
            Console.WriteLine("|" + "Name".PadCenter(30) + "|" + "School".PadCenter(50) + "|" + "Points".PadCenter(8) + "|" + "Type".PadCenter(21) + "|");
            Console.WriteLine("+" + '-'.Times(30) + "+" + '-'.Times(50) + "+" + '-'.Times(8) + "+" + '-'.Times(21) + "+");
            foreach (ActivePlayer player in Service.ActivePlayersFromGame(team, game))
            {
                Console.WriteLine("|" + player.Player.Name.PadCenter(30) + "|" + player.Player.School.PadCenter(50) + "|" 
                    + player.Points.ToString().PadCenter(8) + "|" + ActivePlayerTypeFactory.PlayerTypeToString(player.Type).PadCenter(21) + "|");
            }
            Console.WriteLine("+" + '-'.Times(30) + "+" + '-'.Times(50) + "+" + '-'.Times(8) + "+" + '-'.Times(21) + "+");
            Console.WriteLine();
        }

        public void GamesBetween()
        {
            Console.WriteLine("The format used for the dates is DD Month YYYY, HH:MM (for example, 01 January 1987, 06:00)");
            DateTime firstDateTime = DateTime.ParseExact(GetInput("Give the first date & time: "),
                Constants.DateTimeFormat, null);
            DateTime lastDateTime = DateTime.ParseExact(GetInput("Give the last date & time: "),
                Constants.DateTimeFormat, null);

            Console.WriteLine();
            Console.WriteLine("+" + '-'.Times(69) + "+");
            Console.WriteLine("|" + "Games in the given period".PadCenter(69) + "|");
            Console.WriteLine("+" + '-'.Times(69) + "+");
            foreach (Game game in Service.GamesBetween(firstDateTime, lastDateTime))
            {
                Console.WriteLine("|" + game.ToString().PadCenter(69) + "|");
            }
            Console.WriteLine("+" + '-'.Times(69) + "+");
            Console.WriteLine();
        }

        public void ScoreAtGame()
        {
            Team firstTeam = GetTeamInput("Give the first team: ");
            Team secondTeam = GetTeamInput("Give the second team: ");

            Game game = GetGameFromTeamInput(firstTeam, secondTeam);
            Pair<int, int> scores = Service.ScoreAtTheGame(game);

            Console.WriteLine();
            Console.WriteLine(game.FirstTeam + " scored " + scores.First + " points.");
            Console.WriteLine(game.SecondTeam + " scored " + scores.Second + " points.");
            Console.WriteLine();
        }

        public string GetInput(string text)
        {
            Console.Write(text);
            Console.ForegroundColor = ConsoleColor.DarkGreen;
            string? input = Console.ReadLine();
            Console.ResetColor();
            if (input == null)
            {
                throw new ArgumentException("Cannot give an empty input!");
            }
            return input;
        }

        public Team GetTeamInput(string text)
        {
            List<Team> teams = Service.FindTeamsByName(GetInput(text));
            if (teams.Count == 0)
            {
                throw new ArgumentException("There is no team containing the given input!");
            }

            if (teams.Count == 1)
            {
                return teams[0];
            }
            Console.WriteLine();
            for (int i = 0; i < teams.Count; i++)
            {
                Console.WriteLine(i + 1 + ") " + teams[i]);
            }
            Console.WriteLine();
            return teams[int.Parse(GetInput("Choose the index of the team you want: ")) - 1];

        }

        public Game GetGameFromTeamInput(Team team, Team? secondTeam = null)
        {
            List<Game> games = Service.FindGamesByTeam(team, secondTeam);

            if (games.Count == 0)
            {
                throw new ArgumentException("There is no game played by " + team.Name + (secondTeam == null ? "!" : " and " + secondTeam.Name + "!"));
            }
            Console.WriteLine();
            for (int i = 0; i < games.Count; i++)
            {
                Console.WriteLine(i + 1 + ") " + games[i]);
            }
            Console.WriteLine();
            return games[int.Parse(GetInput("Choose the index of the game you want: ")) - 1];
        }
    }
}
