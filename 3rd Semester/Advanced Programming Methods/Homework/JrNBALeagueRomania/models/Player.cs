namespace JrNBALeagueRomania.models
{
    internal class Player : Student
    {
        public Team Team { get; set; }

        public Player(Guid id, string name, string school, Team team) 
            : base(id, name, school, (Entity<Guid> entity) =>
            {

                Player player = (Player)entity;
                return player.ID + ";" + player.Team.ID;
            })
        {
            Team = team;
        }

        public Player(Student student, Team team)
            : this(student.ID, student.Name, student.School, team) {}
    }
}
