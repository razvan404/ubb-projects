namespace JrNBALeagueRomania.models
{
    internal class Student : Entity<Guid>
    {
        public string Name { get; set; }
        public string School { get; set; }

        public Student(Guid id, string name, string school) 
            : base(id, (Entity<Guid> entity) =>
            {
                Student student = (Student)entity;
                return student.ID + ";" + student.Name + ";" + student.School;
            })
        {
            Name = name;
            School = school;
        }

        public Student(Guid id, string name, string school, ToFileStringMethod method)
            : base(id, method)
        {
            Name = name;
            School = school;
        }

        public override string ToString()
        {
            return Name + " from " + School;
        }
    }
}
