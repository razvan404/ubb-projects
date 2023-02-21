using JrNBALeagueRomania.models;
using JrNBALeagueRomania.repository;
using JrNBALeagueRomania.repository.file;
using JrNBALeagueRomania.service;
using JrNBALeagueRomania.ui;

namespace JrNBALeagueRomania
{
    class Program
    {
        public static void Main()
        {
            IRepository<Guid, Student> studentRepository = new StudentFileRepository();
            IRepository<Guid, Team> teamRepository = new TeamFileRepository();
            IRepository<Guid, Player> playerRepository = new PlayerFileRepository(studentRepository, teamRepository);
            IRepository<Guid, Game> gameRepository = new GameFileRepository(teamRepository);
            IRepository<Pair<Guid, Guid>, ActivePlayer> activePlayerRepository = new ActivePlayerFileRepository(playerRepository, gameRepository);
            Service service = new(studentRepository, teamRepository, playerRepository, gameRepository, activePlayerRepository);

            new ConsoleInterface(service).Run();
        }
    } 
}