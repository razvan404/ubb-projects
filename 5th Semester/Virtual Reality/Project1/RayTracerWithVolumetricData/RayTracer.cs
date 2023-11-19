using System;

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
            return -n * viewPlaneSize / imgSize + viewPlaneSize / 2;
        }

        private Intersection FindFirstIntersection(Line ray, double minDist, double maxDist)
        {
            var intersection = Intersection.NONE;

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
            // TODO: ADD CODE HERE
            var line = new Line(point, light.Position);
            const double eps = 1e-10;
            var segmentLength = (point - light.Position).Length();
            foreach (var geometry in geometries)
            {
                if (geometry is RawCtMask)
                {
                    continue;
                }
                var inter = geometry.GetIntersection(line, eps, segmentLength, true);
                if (inter.Visible)
                {
                    return false;
                }
            }
            return true;
        }

        public void Render(Camera camera, int width, int height, string filename)
        {
            var background = new Color(0.2, 0.2, 0.2, 1.0);
            var viewParallel = (camera.Up ^ camera.Direction).Normalize();

            var image = new Image(width, height);
            var vecW = camera.Direction * camera.ViewPlaneDistance;

            for (var i = 0; i < width; i++)
            {
                var kw = ImageToViewPlane(i, width, camera.ViewPlaneWidth);
                for (var j = 0; j < height; j++)
                {
                    var kh = ImageToViewPlane(j, height, camera.ViewPlaneHeight);
                    var rayVector = camera.Position + vecW + viewParallel * kw + camera.Up * kh;
                    var ray = new Line(camera.Position, rayVector);
                    var inter = FindFirstIntersection(ray, camera.FrontPlaneDistance, camera.BackPlaneDistance);
                    if (!inter.Visible)
                    {
                        image.SetPixel(i, j, background);
                        continue;
                    }
                    var material = inter.Material;
                    var globalColor = new Color();
                    var V = inter.Position;
                    var E = (camera.Position - V).Normalize();
                    var N = inter.Normal;
                    foreach (var light in lights)
                    {
                        var color = material.Ambient * light.Ambient;
                        if (IsLit(V, light))
                        {
                            var T = (light.Position - V).Normalize();
                            var R = (N * (N * T) * 2 - T).Normalize();
                            var diffuseFactor = N * T;
                            var specularFactor = E * R;
                            if (diffuseFactor > 0)
                            {
                                color += material.Diffuse * light.Diffuse * diffuseFactor;
                            }
                            if (specularFactor > 0)
                            {
                                color += material.Specular * light.Specular * Math.Pow(specularFactor, material.Shininess);
                            }
                            color *= light.Intensity;
                        }
                        globalColor += color;
                    }

                    image.SetPixel(i, j, globalColor);
                }
            }

            image.Store(filename);
        }
    }
}