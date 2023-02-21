namespace JrNBALeagueRomania.models
{
    internal class Team : Entity<Guid>
    {
        public string Name { get; set; }

        public Team(Guid id, string name) 
            : base(id, (Entity<Guid> entity) =>
            {
                Team team = (Team)entity;
                return team.ID + ";" + team.Name;
            })
        {
            Name = name;
        }

        public override string ToString()
        {
            return Name;
        }
    }
}
