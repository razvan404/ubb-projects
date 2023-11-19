using System;
using System.IO;
using System.Threading.Tasks;

namespace rt
{
    public class Program
    {
        public static void Main(string[] args)
        {
            // Cleanup
            const string frames = "../../../frames";
            if (Directory.Exists(frames))
            {
                var d = new DirectoryInfo(frames);
                foreach (var file in d.EnumerateFiles("*.png")) {
                    file.Delete();
                }
            }
            Directory.CreateDirectory(frames);

            // Scene
            var geometries = new Geometry[]
            {
                new Ellipsoid(new Vector(  0.0, -25.0, 100.0), new Vector(1.0, 1.0, 1.0), 5.0, Color.WHITE),
                
                new Ellipsoid(new Vector( 15.0, -25.0, 100.0), new Vector(2.0, 0.5, 0.5), 5.0, Color.RED),
                new Ellipsoid(new Vector( 35.0, -25.0, 100.0), new Vector(2.0, 0.5, 0.5), 5.0, Color.RED),
                new Ellipsoid(new Vector( 55.0, -25.0, 100.0), new Vector(2.0, 0.5, 0.5), 5.0, Color.RED),
                
                new Ellipsoid(new Vector(  0.0, -10.0, 100.0), new Vector(0.5, 2.0, 0.5), 5.0, Color.GREEN),
                new Ellipsoid(new Vector(  0.0,  10.0, 100.0), new Vector(0.5, 2.0, 0.5), 5.0, Color.GREEN),
                new Ellipsoid(new Vector(  0.0,  30.0, 100.0), new Vector(0.5, 2.0, 0.5), 5.0, Color.GREEN),
                
                new Ellipsoid(new Vector(  0.0, -25.0, 115.0), new Vector(0.5, 0.5, 2.0), 5.0, Color.BLUE),
                new Ellipsoid(new Vector(  0.0, -25.0, 135.0), new Vector(0.5, 0.5, 2.0), 5.0, Color.BLUE),
                new Ellipsoid(new Vector(  0.0, -25.0, 155.0), new Vector(0.5, 0.5, 2.0), 5.0, Color.BLUE),
                
                new Ellipsoid(new Vector( 35.0,  10.0, 100.0), new Vector(5.0, 5.0, 0.5), 5.0, Color.YELLOW),
                new Ellipsoid(new Vector(  0.0,  10.0, 135.0), new Vector(0.5, 5.0, 5.0), 5.0, Color.CYAN),
                new Ellipsoid(new Vector( 35.0, -25.0, 135.0), new Vector(5.0, 0.5, 5.0), 5.0, Color.MAGENTA),
                
                new Sphere(   new Vector(-25.0, -50.0,  75.0),                           25.0, Color.ORANGE),
                
                new RawCtMask("../../../raw/walnut.dat", "../../../raw/walnut.raw", new Vector(-5.0, -20.0, 105.0), 0.2,
                    new ColorMap()
                        .Add(1, 1, new Color(0.36, 0.26, 0.16, 0.05))
                        .Add(2, 2, new Color(0.87, 0.72, 0.52, 1.0))
                ),  
            };

            var lights = new []
            {
                new Light(new Vector( 65.0,  40.0,  90.0), new Color(0.8, 0.8, 0.8, 1.0), new Color(0.8, 0.8, 0.8, 1.0), new Color(0.8, 0.8, 0.8, 1.0), 1.0),
                new Light(new Vector(-10.0,  40.0, 165.0), new Color(0.8, 0.8, 0.8, 1.0), new Color(0.8, 0.8, 0.8, 1.0), new Color(0.8, 0.8, 0.8, 1.0), 1.0),
                new Light(new Vector( 65.0, -35.0, 165.0), new Color(0.8, 0.8, 0.8, 1.0), new Color(0.8, 0.8, 0.8, 1.0), new Color(0.8, 0.8, 0.8, 1.0), 1.0),
                new Light(new Vector( 65.0,  40.0, 165.0), new Color(0.8, 0.8, 0.8, 1.0), new Color(0.8, 0.8, 0.8, 1.0), new Color(0.8, 0.8, 0.8, 1.0), 1.0)
            };
            var rt = new RayTracer(geometries, lights);

            const int width = 800;
            const int height = 600;

            // Go around an approximate middle of the scene and generate frames
            var middle = new Vector(0.0, -5.0, 100.0);
            var up = new Vector(0, -1, 0).Normalize();
            var first = new Vector(0, 0, 1).Normalize();
            const double dist = 95.0;
            const int n = 90;
            const int tasksCount = 15;
            const double step = 360.0 / n;
            
            var tasks = new Task[tasksCount];
            for (var i = 0; i < tasksCount; i++)
            {
                var ind = new[]{i};
                tasks[i] = Task.Run(() =>
                {
                    var k = ind[0];
                    while (k < n)
                    {
                        var a = (step * k) * Math.PI / 180.0;
                        var ca =  Math.Cos(a);
                        var sa =  Math.Sin(a);
            
                        var dir = first * ca + (up ^ first) * sa + up * (up * first) * (1.0 - ca);
            
                        var camera = new Camera(
                            middle - dir * dist,
                            dir,
                            up,
                            65.0,
                            160.0,
                            120.0,
                            0.0,
                            1000.0
                        );
            
                        var filename = frames+"/" + $"{k + 1:000}" + ".png";
            
                        rt.Render(camera, width, height, filename);
                        Console.WriteLine($"Frame {k+1}/{n} completed");
                        k += tasksCount;
                    }
                });
            }
            
            Task.WaitAll(tasks);
        }
    }
}