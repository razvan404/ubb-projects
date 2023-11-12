using SixLabors.ImageSharp;
using SixLabors.ImageSharp.PixelFormats;

namespace rt
{
    public class Image
    {
        private Image<Rgba32> image;

        public Image(int width, int height)
        {
            image = new Image<Rgba32>(width, height);
        }

        public void SetPixel(int x, int y, Color c)
        {
            image[x, y] = new Rgba32((float)c.Red, (float)c.Green, (float)c.Blue, (float)c.Alpha);
        }

        public void Store(string filename)
        {
            image.Save(filename);
        }
    }
}