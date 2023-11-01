namespace rt
{
    public class Intersection
    {
        public bool Valid{ get; set; }
        public bool Visible{ get; set; }
        public double T{ get; }
        public Vector Position{ get; }
        public Geometry Geometry{ get; }
        public Line Line{ get; }
        
        public Vector Normal { get; }

        public Intersection() {
            Geometry = null;
            Line = null;
            Valid = false;
            Visible = false;
            T = 0;
            Position = null;
            Normal = null;
        }

        public Intersection(bool valid, bool visible, Geometry geometry, Line line, double t, Vector normal) {
            Geometry = geometry;
            Line = line;
            Valid = valid;
            Visible = visible;
            T = t;
            Normal = normal;
            Position = Line.CoordinateToPosition(t);
        }
    }
}