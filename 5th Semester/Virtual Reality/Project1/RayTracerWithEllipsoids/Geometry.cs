namespace rt
{
    public abstract class Geometry
    {
        public Color Color { get; set; }
        public Material Material { get; set; }

        public Geometry(Material material, Color color) {
            Material = material;
            Color = color;
        }

        public Geometry(Color color) {
            Material = new Material(color*0.1, color*0.3, color*0.5, 100);
            Color = color;
        }

        public abstract Intersection GetIntersection(Line line, double minDist, double maxDist);
    }
}