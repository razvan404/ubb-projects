using JrNBALeagueRomania.models;
using JrNBALeagueRomania.utils;

namespace JrNBALeagueRomania.repository.file
{
    internal class GameFileRepository : IFileRepository<Guid, Game>
    {
        private readonly IRepository<Guid, Team> TeamRepository;
        public GameFileRepository(IRepository<Guid, Team> teamRepository)
            : base(Files.GamesFile)
        {
            TeamRepository = teamRepository;
            LoadData();
        }

        protected override Game ExtractEntity(string[] args)
        {
            Guid id = Guid.Parse(args[0]);
            #pragma warning disable CS8600 // Converting null literal or possible null value to non-nullable type.
            Team firstTeam = TeamRepository.Find(Guid.Parse(args[1]));
            Team secondTeam = TeamRepository.Find(Guid.Parse(args[2]));
            #pragma warning restore CS8600 // Converting null literal or possible null value to non-nullable type.
            DateTime date = DateTime.ParseExact(args[3], Constants.DateTimeFormat, null);
            if (firstTeam is null || secondTeam is null)
            {
                throw new IOException("There is a problem with the games file!");
            }
            return new Game(id, firstTeam, secondTeam, date);
        }
    }
}
