using System;
using System.Drawing;
using System.Runtime.InteropServices;
using static System.Net.Mime.MediaTypeNames;

namespace rt
{
    class RayTracer
    {
        private Geometry[] geometries;
        private Light[] lights;

        public RayTracer(Geometry[] geometries, Light[] lights)
        {
            this.geometries = geometries;
            this.lights = lights;
        }

        private double ImageToViewPlane(int n, int imgSize, double viewPlaneSize)
        {
            var u = n * viewPlaneSize / imgSize;
            u -= viewPlaneSize / 2;
            return u;
        }

        private Intersection FindFirstIntersection(Line ray, double minDist, double maxDist)
        {
            var intersection = new Intersection();

            foreach (var geometry in geometries)
            {
                var intr = geometry.GetIntersection(ray, minDist, maxDist);

                if (!intr.Valid || !intr.Visible) continue;

                if (!intersection.Valid || !intersection.Visible)
                {
                    intersection = intr;
                }
                else if (intr.T < intersection.T)
                {
                    intersection = intr;
                }
            }

            return intersection;
        }

        private bool IsLit(Vector point, Light light)
        {
            // ADD CODE HERE: Detect whether the given point has a clear line of sight to the given light
            var line = new Line(light.Position, point);
            double segmentLength = (point - light.Position).Length();
            foreach (var geometry in geometries)
            {
                Intersection inter = geometry.GetIntersection(line, 0, segmentLength);
                if (inter.Visible && segmentLength - inter.T > 1e-2)
                {
                    return false;
                }
            }
            return true;
        }

        public void Render(Camera camera, int width, int height, string filename)
        {
            var background = new Color(1, 1, 1, 1);
            var viewParallel = (camera.Up ^ camera.Direction).Normalize();

            var image = new Image(width, height);

            var vecW = camera.Direction * camera.ViewPlaneDistance;
            for (var i = 0; i < width; i++)
            {
                double kw = ImageToViewPlane(i, width, camera.ViewPlaneWidth);
                for (var j = 0; j < height; j++)
                {
                    // ADD CODE HERE: Implement pixel color calculation
                    double kh = ImageToViewPlane(j, height, camera.ViewPlaneHeight);
                    Vector rayVector = camera.Position + camera.Direction * camera.ViewPlaneDistance + viewParallel * kw + camera.Up * kh;
                    Line ray = new Line(camera.Position, rayVector);
                    var inter = FindFirstIntersection(ray, camera.FrontPlaneDistance, camera.BackPlaneDistance);
                    if (!inter.Valid)
                    {
                        image.SetPixel(i, j, background);
                        continue;
                    }
                    var geometry = inter.Geometry;
                    var material = geometry.Material;
                    var colors = new List<Color>();
                    var V = inter.Position;
                    foreach (var light in lights)
                    {
                        var Color = material.Ambient * light.Ambient;
                        if (IsLit(V, light))
                        {
                            var E = (camera.Position - V).Normalize();
                            var N = geometry.Normal(V);
                            var T = (light.Position - V).Normalize();
                            var R = N * (N * T) * 2 - T;

                            var diffuseFactor = N * T;
                            if (diffuseFactor > 0)
                            {
                                Color += material.Diffuse * light.Diffuse * (diffuseFactor);
                            }

                            var specularFactor = E * R;
                            if (specularFactor > 0)
                            {
                                Color += material.Specular * light.Specular * Math.Pow(specularFactor, material.Shininess);
                            }

                            Color *= light.Intensity;
                        }
                        colors.Add(Color);
                    }
                    var globalColor = colors.Aggregate((acc, color) => acc + color);
                    image.SetPixel(i, j, globalColor);
                }
            }
            image.Store(filename);
        }
    }
}