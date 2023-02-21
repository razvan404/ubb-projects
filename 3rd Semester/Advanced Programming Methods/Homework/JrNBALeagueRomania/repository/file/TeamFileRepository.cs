using JrNBALeagueRomania.models;
using JrNBALeagueRomania.utils;

namespace JrNBALeagueRomania.repository.file
{
    internal class TeamFileRepository : IFileRepository<Guid, Team>
    {
        public TeamFileRepository() 
            : base(Files.TeamsFile)
        {
            LoadData();
        }

        protected override Team ExtractEntity(string[] args)
        {
            Guid id = Guid.Parse(args[0]);
            string name = args[1];
            return new Team(id, name);
        }
    }
}
