using JrNBALeagueRomania.models;
using JrNBALeagueRomania.utils;

namespace JrNBALeagueRomania.repository.file
{
    internal class ActivePlayerFileRepository : IFileRepository<Pair<Guid, Guid>, ActivePlayer>
    {
        private readonly IRepository<Guid, Player> PlayerRepository;
        private readonly IRepository<Guid, Game> GameRepository;
        public ActivePlayerFileRepository(IRepository<Guid, Player> playerRepository, IRepository<Guid, Game> gameRepository) 
            : base(Files.ActivePlayersFile)
        {
            PlayerRepository = playerRepository;
            GameRepository = gameRepository;
            LoadData();
        }

        protected override ActivePlayer ExtractEntity(string[] args)
        {
            #pragma warning disable CS8600 // Converting null literal or possible null value to non-nullable type.
            Player player = PlayerRepository.Find(Guid.Parse(args[0]));
            Game game = GameRepository.Find(Guid.Parse(args[1]));
            #pragma warning restore CS8600 // Converting null literal or possible null value to non-nullable type.
            int points = int.Parse(args[2]);
            ActivePlayerType playerType = ActivePlayerTypeFactory.CharacterToPlayerType(char.Parse(args[3]));
            if (player is null || game is null)
            {
                throw new IOException("There is a problem with the players file or the games file!");
            }

            return new ActivePlayer(player, game, points, playerType);
        }
    }
}
