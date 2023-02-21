using JrNBALeagueRomania.utils;

namespace JrNBALeagueRomania.models
{
    internal class Game : Entity<Guid>
    {
        public Team FirstTeam { get; set; }
        public Team SecondTeam { get; set; }
        public DateTime Date { get; set; }

        public Game(Guid id, Team firstTeam, Team secondTeam, DateTime date)
            : base(id, (Entity<Guid> entity) =>
            {
                Game game = (Game)entity;
                return game.ID + ";" + game.FirstTeam.ID + ";" + game.SecondTeam.ID + ";" + game.Date.ToString(Constants.DateTimeFormat);
            })
        {
            FirstTeam = firstTeam;
            SecondTeam = secondTeam;
            Date = date;
        }

        public override string ToString()
        {
            return FirstTeam + " vs " + SecondTeam + ", " + Date.ToString(Constants.DateTimeFormat);
        }
    }
}
