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

        public Geometry(Color color)
        {
            Material = Material.FromColor(color);
            Color = color;
        }

        public abstract Intersection GetIntersection(Line line, double minDist, double maxDist, bool? onlyFirst = false);
    }
}