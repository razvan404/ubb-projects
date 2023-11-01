using System;
using System.Runtime.Intrinsics;

namespace rt
{
    public class Ellipsoid : Geometry
    {
        private Vector Center { get; }
        private Vector SemiAxesLength { get; }
        private double Radius { get; }
        
        
        public Ellipsoid(Vector center, Vector semiAxesLength, double radius, Material material, Color color) : base(material, color)
        {
            Center = center;
            SemiAxesLength = semiAxesLength;
            Radius = radius;
        }

        public Ellipsoid(Vector center, Vector semiAxesLength, double radius, Color color) : base(color)
        {
            Center = center;
            SemiAxesLength = semiAxesLength;
            Radius = radius;
        }

        public override Intersection GetIntersection(Line line, double minDist, double maxDist)
        {
            // TODO: ADD CODE HERE
            var dtOverE = line.Dx / SemiAxesLength;
            var x0cOverE = (line.X0 - Center) / SemiAxesLength;
            double a = dtOverE.Length2();
            double b = dtOverE * x0cOverE * 2;
            double c = x0cOverE.Length2() - Radius * Radius;
            double delta = b * b - 4 * a * c;

            bool valid = false;
            bool visible = false;
            double t = 0;
            Vector normal = null;
            if (Math.Abs(delta) < 1e-10)
            {
                valid = true;
                t = -b / (2 * a);
                visible = t >= minDist && t <= maxDist;
                var position = line.CoordinateToPosition(t);
                normal = ((position - Center) * 2 / SemiAxesLength).Normalize();
            }
            else if (delta > 0)
            {
                valid = true;
                double sqrtDelta = Math.Sqrt(delta), inverse2a = 1 / (2 * a);
                double t1 = (-b - sqrtDelta) * inverse2a, t2 = (-b + sqrtDelta) * inverse2a;
                visible = (t1 >= minDist && t1 <= maxDist) || (t2 >= minDist && t2 <= maxDist);
                t = t1 >= minDist ? t1 : t2; // closest point
                var position = line.CoordinateToPosition(t);
                normal = ((position - Center) * 2 / SemiAxesLength).Normalize();
            }
            return new(valid, visible, this, line, t, normal);
        }
    }
}
