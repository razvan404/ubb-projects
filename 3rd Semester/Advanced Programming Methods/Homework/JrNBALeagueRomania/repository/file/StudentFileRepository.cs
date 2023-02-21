using JrNBALeagueRomania.models;
using JrNBALeagueRomania.utils;

namespace JrNBALeagueRomania.repository.file
{
    internal class StudentFileRepository : IFileRepository<Guid, Student>
    {
        public StudentFileRepository()
            : base(Files.StudentsFile)
        {
            LoadData();
        }
        protected override Student ExtractEntity(string[] args)
        {
            Guid id = Guid.Parse(args[0]);
            string name = args[1];
            string school = args[2];
            return new Student(id, name, school);
        }
    }
}
