using JrNBALeagueRomania.models;
using JrNBALeagueRomania.repository;

namespace JrNBALeagueRomania.service
{
    internal class Service
    {
        private readonly IRepository<Guid, Student> StudentRepository;
        private readonly IRepository<Guid, Team> TeamRepository;
        private readonly IRepository<Guid, Player> PlayerRepository;
        private readonly IRepository<Guid, Game> GameRepository;
        private readonly IRepository<Pair<Guid, Guid>, ActivePlayer> ActivePlayerRepository;

        public Service(IRepository<Guid, Student> studentRepository, IRepository<Guid, Team> teamRepository, 
            IRepository<Guid, Player> playerRepository, IRepository<Guid, Game> gameRepository,
            IRepository<Pair<Guid, Guid>, ActivePlayer> activePlayerRepository)
        {
            StudentRepository = studentRepository;
            TeamRepository = teamRepository;
            PlayerRepository = playerRepository;
            GameRepository = gameRepository;
            ActivePlayerRepository = activePlayerRepository;
        }

        public List<Player> PlayersFromTeam(Team givenTeam)
        {
            return PlayerRepository.FindAll()
                .Where(player => player.Team == givenTeam)
                .ToList();
        }

        public List<ActivePlayer> ActivePlayersFromGame(Team givenTeam, Game givenGame)
        {
            return (from activePlayer in ActivePlayerRepository.FindAll()
                    where activePlayer.Game == givenGame && activePlayer.Player.Team == givenTeam
                    select activePlayer).ToList();
        }

        public List<Game> GamesBetween(DateTime firstDateTime, DateTime lastDateTime)
        {
            return GameRepository.FindAll()
                .Where(game => game.Date >= firstDateTime && game.Date <= lastDateTime)
                .ToList();
        }

        public Pair<int, int> ScoreAtTheGame(Game givenGame)
        {
            return new(
                (from activePlayer in ActivePlayerRepository.FindAll()
                    where activePlayer.Game == givenGame && activePlayer.Player.Team == givenGame.FirstTeam
                    select activePlayer.Points).Sum(),
                (from activePlayer in ActivePlayerRepository.FindAll()
                    where activePlayer.Game == givenGame && activePlayer.Player.Team == givenGame.SecondTeam
                    select activePlayer.Points).Sum());
        }

        public List<Team> FindTeamsByName(string? substring)
        {
            if (substring == null)
            {
                throw new ArgumentException("Can't find a team without an input!");
            }
            return TeamRepository.FindAll()
                .Where(team => team.Name.ToLower().Contains(substring.ToLower()))
                .ToList();
        }

        public List<Game> FindGamesByTeam(Team team)
        {
            return (from game in GameRepository.FindAll()
                    where game.FirstTeam == team || game.SecondTeam == team
                    select game).ToList();
        }
        public List<Game> FindGamesByTeam(Team firstTeam, Team? secondTeam)
        {
            if (secondTeam == null)
            {
                return FindGamesByTeam(firstTeam);
            }

            return GameRepository.FindAll()
                .Where(game => (game.FirstTeam == firstTeam && game.SecondTeam == secondTeam)
                        || (game.FirstTeam == secondTeam && game.SecondTeam == firstTeam))
                .ToList();
        }
    }
}
