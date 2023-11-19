using System;
using System.Runtime.Intrinsics;

namespace rt
{
    public class Ellipsoid : Geometry
    {
        private Vector Center { get; }
        private Vector SemiAxesLength { get; }
        private Vector SemiAxesLengthSquared { get; }
        private double Radius { get; }
        
        public Ellipsoid(Vector center, Vector semiAxesLength, double radius, Material material, Color color) : base(material, color)
        {
            Center = center;
            SemiAxesLength = semiAxesLength;
            SemiAxesLengthSquared = new Vector(SemiAxesLength.X * SemiAxesLength.X, SemiAxesLength.Y * SemiAxesLength.Y, SemiAxesLength.Z * SemiAxesLength.Z);
            Radius = radius;
        }

        public Ellipsoid(Vector center, Vector semiAxesLength, double radius, Color color) : base(color)
        {
            Center = center;
            SemiAxesLength = semiAxesLength;
            SemiAxesLengthSquared = new Vector(SemiAxesLength.X * SemiAxesLength.X, SemiAxesLength.Y * SemiAxesLength.Y, SemiAxesLength.Z * SemiAxesLength.Z);
            Radius = radius;
        }

        private Vector linify(Vector v)
        {
            return new Vector(v.X / SemiAxesLength.X, v.Y / SemiAxesLength.Y, v.Z / SemiAxesLength.Z);
        }

        private Vector normalLinify(Vector v)
        {
            return new Vector(v.X / SemiAxesLengthSquared.X, v.Y / SemiAxesLengthSquared.Y, v.Z / SemiAxesLengthSquared.Z);
        }

        public Tuple<double?, double?> GetFirstAndLastIntersection(Line line)
        {
            var dtOverE = linify(line.Dx);
            var x0COverE = linify(line.X0 - Center);
            var a = dtOverE.Length2();
            var b = dtOverE * x0COverE * 2;
            var c = x0COverE.Length2() - Radius * Radius;
            var delta = b * b - 4 * a * c;

            if (delta < 1e-10) return new Tuple<double?, double?>(null, null);
            
            if (Math.Abs(delta) < 1e-10)
            {
                return new Tuple<double?, double?>(-b / (2 * a), null);
            }
            
            var sqrtDelta = Math.Sqrt(delta);
            var inverse2A = 1 / (2 * a);
            var t1 = (-b - sqrtDelta) * inverse2A;
            var t2 = (-b + sqrtDelta) * inverse2A;
            return new Tuple<double?, double?>(t1, t2);
        }

        public override Intersection GetIntersection(Line line, double minDist, double maxDist, bool? onlyFirst)
        {
            // TODO: ADD CODE HERE
            var (t1, t2) = GetFirstAndLastIntersection(line);
            if (t1 == null)
            {
                return Intersection.NONE;
            }
            if (t2 == null)
            {
                var t = t1 ?? 0;
                var visible = t >= minDist && t <= maxDist;
                var position = line.CoordinateToPosition(t);
                var normal = normalLinify((position - Center) * 2).Normalize();
                return new Intersection(true, visible, this, line, t, normal, Material, Color);
            }
            else
            {
                var visible = (t1 >= minDist && t1 <= maxDist) || (t2 >= minDist && t2 <= maxDist);
                var t = (t1 >= minDist ? t1 : t2) ?? 0; // closest point
                var position = line.CoordinateToPosition(t);
                var normal = normalLinify((position - Center) * 2).Normalize();
                return new Intersection(true, visible, this, line, t, normal, Material, Color);
            }
        }
    }
}
