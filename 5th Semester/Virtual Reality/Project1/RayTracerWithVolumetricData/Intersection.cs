namespace rt
{
    public class Intersection
    {
        public static readonly Intersection NONE = new();
            
        public bool Valid{ get; set; }
        public bool Visible{ get; set; }
        public double T{ get; }
        public Vector Position{ get; }
        public Geometry Geometry{ get; }
        public Line Line{ get; }
        public Vector Normal { get; }
        public Material Material { get; set; }
        public Color Color { get; set; }

        public Intersection() {
            Geometry = null;
            Line = null;
            Valid = false;
            Visible = false;
            T = 0;
            Position = null;
            Normal = null;
            Material = new();
            Color = new();
        }

        public Intersection(bool valid, bool visible, Geometry geometry, Line line, double t, Vector normal, Material material, Color color) {
            Geometry = geometry;
            Line = line;
            Valid = valid;
            Visible = visible;
            T = t;
            Normal = normal;
            Position = Line.CoordinateToPosition(t);
            Material = material;
            Color = color;
        }
    }
}