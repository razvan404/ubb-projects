namespace JrNBALeagueRomania.models
{
    internal class ActivePlayer : Entity<Pair<Guid, Guid>>
    {
        public Player Player { get; set; }
        public Game Game { get; set; }
        public int Points { get; set; }
        public ActivePlayerType Type { get; set; }
        public ActivePlayer(Player player, Game game, int points, ActivePlayerType type) 
            : base(new Pair<Guid, Guid>(player.ID, game.ID), (Entity<Pair<Guid, Guid>> entity) =>
            {
                ActivePlayer activePlayer = (ActivePlayer)entity;
                return activePlayer.Player.ID + ";" + activePlayer.Game.ID + ";" + activePlayer.Points + ";"
                    + ActivePlayerTypeFactory.PlayerTypeToCharacter(activePlayer.Type);
            })
        {
            Player = player;
            Game = game;
            Points = points;
            Type = type;
        }
    }

    internal enum ActivePlayerType
    {
        Reserve,
        Participant
    }

    internal static class ActivePlayerTypeFactory
    {
        public static ActivePlayerType CharacterToPlayerType(char c) => c switch
        {
            'R' => ActivePlayerType.Reserve,
            'P' => ActivePlayerType.Participant,
            _ => throw new ArgumentException("Invalid character given to ActivePlayerTypeFactory.")
        };

        public static char PlayerTypeToCharacter(ActivePlayerType type) => type switch
        {
            ActivePlayerType.Reserve => 'R',
            ActivePlayerType.Participant => 'P',
            _ => throw new ArgumentException("Invalid ActivePlayerType given to ActivePlayerTypeFactory.")
        };

        public static string PlayerTypeToString(ActivePlayerType type) => type switch
        {
            ActivePlayerType.Reserve => "Reserve",
            ActivePlayerType.Participant => "Participant",
            _ => throw new ArgumentException("Invalid ActivePlayerType given to ActivePlayerTypeFactory.")
        };
    }
}
