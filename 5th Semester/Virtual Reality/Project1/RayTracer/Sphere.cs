using System;

namespace rt
{
    public class Sphere : Geometry
    {
        private Vector Center { get; set; }
        private double Radius { get; set; }

        public Sphere(Vector center, double radius, Material material, Color color) : base(material, color)
        {
            Center = center;
            Radius = radius;
        }

        public override Intersection GetIntersection(Line line, double minDist, double maxDist)
        {
            // ADD CODE HERE: Calculate the intersection between the given line and this sphere
            double a = line.Dx.Length2();
            double b = line.Dx * (line.X0 - Center) * 2;
            double c = (line.X0 - Center).Length2() - Radius * Radius;
            double delta = b * b - 4 * a * c;

            bool valid = false;
            bool visible = false;
            double t = 0;
            if (Math.Abs(delta) < 1e-2)
            {
                valid = true;
                t = -b / (2 * a);
                visible = t >= minDist && t <= maxDist;
            }
            else if (delta > 0)
            {
                valid = true;
                double sqrtDelta = Math.Sqrt(delta), inverse2a = 1 / (2 * a);
                double t1 = (-b - sqrtDelta) * inverse2a, t2 = (-b + sqrtDelta) * inverse2a;
                if (t1 >= minDist && t1 <= maxDist)
                {
                    visible = true;
                    t = t1;
                }
                else if (t2 >= minDist && t2 <= maxDist)
                {
                    visible = true;
                    t = t2;
                }
            }
            return new(valid, visible, this, line, t);
        }

        public override Vector Normal(Vector v)
        {
            var n = v - Center;
            n.Normalize();
            return n;
        }
    }
}