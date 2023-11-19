using System;
using System.IO;
using System.Text.RegularExpressions;
using SixLabors.ImageSharp.ColorSpaces;

namespace rt;

public class RawCtMask: Geometry
{
    private readonly Vector _position;
    private readonly double _scale;
    private readonly ColorMap _colorMap;
    private readonly byte[] _data;

    private readonly int[] _resolution = new int[3];
    private readonly double[] _thickness = new double[3];
    private readonly Vector _v0;
    private readonly Vector _v1;
    private readonly Ellipsoid _boundingEllipsoid;

    public RawCtMask(string datFile, string rawFile, Vector position, double scale, ColorMap colorMap) : base(Color.NONE)
    {
        _position = position;
        _scale = scale;
        _colorMap = colorMap;

        var lines = File.ReadLines(datFile);
        foreach (var line in lines)
        {
            var kv = Regex.Replace(line, "[:\\t ]+", ":").Split(":");
            if (kv[0] == "Resolution")
            {
                _resolution[0] = Convert.ToInt32(kv[1]);
                _resolution[1] = Convert.ToInt32(kv[2]);
                _resolution[2] = Convert.ToInt32(kv[3]);
            } else if (kv[0] == "SliceThickness")
            {
                _thickness[0] = Convert.ToDouble(kv[1]);
                _thickness[1] = Convert.ToDouble(kv[2]);
                _thickness[2] = Convert.ToDouble(kv[3]);
            }
        }

        _v0 = position;
        var diagonal = new Vector
            (
                _resolution[0] * _thickness[0] * scale, 
                _resolution[1] * _thickness[1] * scale,
                _resolution[2] * _thickness[2] * scale
            );
        _v1 = position + diagonal;

        var len = _resolution[0] * _resolution[1] * _resolution[2];
        _data = new byte[len];
        using FileStream f = new FileStream(rawFile, FileMode.Open, FileAccess.Read);
        if (f.Read(_data, 0, len) != len)
        {
            throw new InvalidDataException($"Failed to read the {len}-byte raw data");
        }

        var halfDiagonal = diagonal / 2;

        _boundingEllipsoid = new Ellipsoid
            (position + halfDiagonal, halfDiagonal, 1, Color.NONE);
    }
    
    private ushort Value(int x, int y, int z)
    {
        if (x < 0 || y < 0 || z < 0 || x >= _resolution[0] || y >= _resolution[1] || z >= _resolution[2])
        {
            return 0;
        }

        return _data[z * _resolution[1] * _resolution[0] + y * _resolution[0] + x];
    }

    public override Intersection GetIntersection(Line line, double minDist, double maxDist, bool? onlyFirst)
    {
        var (t1, t2) = _boundingEllipsoid.GetFirstAndLastIntersection(line);
        if (t1 == null || t2 == null)
        {
            return Intersection.NONE;
        }

        var start = Math.Max(t1 ?? 0, minDist);
        var end = Math.Min(t2 ?? 0, maxDist);
        var stepSize = _scale;
        var firstIntersection = 0d;
        var normal = new Vector();
        var globalColor = new Color();
        var lastAlpha = 1d;
        var passedFirst = false;
        for (var t = start; t <= end; t += stepSize)
        {
            var point = line.CoordinateToPosition(t);
            var idx = GetIndexes(point);
            var pointColor = GetColor(idx);
            if (pointColor.Alpha == 0) continue;
            if (!passedFirst)
            {
                firstIntersection = t;
                normal = GetNormal(idx); 
                passedFirst = true;
                if (onlyFirst == true)
                {
                    return new Intersection(true, true, this, line, t, normal, Material, Color.NONE);
                }
            }
            globalColor += pointColor * pointColor.Alpha * lastAlpha;
            lastAlpha *= 1 - pointColor.Alpha;
            if (lastAlpha < 1e-10) break;
        }
        return new Intersection
            (
                true, 
                passedFirst,
                this,
                line,
                firstIntersection,
                normal,
                Material.FromColor(globalColor),
                globalColor
            );
    }
    
    private int[] GetIndexes(Vector v)
    {
        return new []{
            (int)Math.Floor((v.X - _position.X) / _thickness[0] / _scale), 
            (int)Math.Floor((v.Y - _position.Y) / _thickness[1] / _scale),
            (int)Math.Floor((v.Z - _position.Z) / _thickness[2] / _scale)};
    }
    private Color GetColor(int[] idx)
    {
        ushort value = Value(idx[0], idx[1], idx[2]);
        return _colorMap.GetColor(value);
    }

    private Vector GetNormal(int[] idx)
    {
        double x0 = Value(idx[0] - 1, idx[1], idx[2]);
        double x1 = Value(idx[0] + 1, idx[1], idx[2]);
        double y0 = Value(idx[0], idx[1] - 1, idx[2]);
        double y1 = Value(idx[0], idx[1] + 1, idx[2]);
        double z0 = Value(idx[0], idx[1], idx[2] - 1);
        double z1 = Value(idx[0], idx[1], idx[2] + 1);

        return new Vector(x1 - x0, y1 - y0, z1 - z0).Normalize();
    }
}