using JrNBALeagueRomania.models;
using JrNBALeagueRomania.utils;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace JrNBALeagueRomania.repository.file
{
    internal class PlayerFileRepository : IFileRepository<Guid, Player>
    {
        private readonly IRepository<Guid, Student> StudentRepository;
        private readonly IRepository<Guid, Team> TeamRepository;

        public PlayerFileRepository(IRepository<Guid, Student> studentRepository, IRepository<Guid, Team> teamRepository)
            : base(Files.PlayersFile)
        {
            StudentRepository = studentRepository;
            TeamRepository = teamRepository;
            LoadData();
        }

        protected override Player ExtractEntity(string[] args)
        {
            #pragma warning disable CS8600 // Converting null literal or possible null value to non-nullable type.
            Student student = StudentRepository.Find(Guid.Parse(args[0]));
            Team team = TeamRepository.Find(Guid.Parse(args[1]));
            #pragma warning restore CS8600 // Converting null literal or possible null value to non-nullable type.
            if (student is null || team is null)
            {
                throw new IOException("There is a problem with the players file!");
            }
            return new Player(student, team);
        }
    }
}
