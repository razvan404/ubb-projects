using SixLabors.ImageSharp;
using SixLabors.ImageSharp.PixelFormats;

namespace rt
{
    public class Image
    {
        private readonly Image<Rgba32> _image;

        public Image(int width, int height)
        {
            _image = new Image<Rgba32>(width, height);
        }

        public void SetPixel(int x, int y, Color c)
        {
            var systemColor = c.ToSystemColor();
            _image[x, y] = new Rgba32(systemColor.R, systemColor.G, systemColor.B, systemColor.A);
        }

        public void Store(string filename)
        {
            _image.Save(filename);
        }
    }
}