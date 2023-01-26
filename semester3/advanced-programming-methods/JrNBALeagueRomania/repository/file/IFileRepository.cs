using JrNBALeagueRomania.models;
using JrNBALeagueRomania.repository.memory;
using System.Text;

namespace JrNBALeagueRomania.repository.file
{
    internal abstract class IFileRepository<ID, E> : IMemoRepository<ID, E>
        where ID : notnull
        where E : Entity<ID>
    {

        private readonly string Filename;
        public IFileRepository(string filename)
        {
            Filename = filename;
        }
        protected abstract E ExtractEntity(string[] args);
        protected void LoadData()
        {
            foreach (string line in File.ReadAllLines(Filename))
            {
                base.Save(ExtractEntity(line.Split(';')));
            }
        }
        private void WriteData()
        {
            StringBuilder stringBuilder = new();
            foreach (E entity in FindAll())
            {
                stringBuilder.AppendLine(entity.ToFileString());
            }
            File.WriteAllText(Filename, stringBuilder.ToString());
        }

        public override E? Save(E? entity)
        {
            E? unsavedEntity = base.Save(entity);
            if (unsavedEntity == null)
            {
                WriteData();
            }
            return unsavedEntity;
        }

        public override E? Update(E? entity)
        {
            E? oldEntity = base.Update(entity);
            if (oldEntity == null)
            {
                return null;
            }
            WriteData();
            return oldEntity;
        }

        public override E? Delete(ID? identifier)
        {
            E? deletedEntity = base.Delete(identifier);
            if (deletedEntity == null)
            {
                return null;
            }
            WriteData();
            return deletedEntity;
        }
    }
}
