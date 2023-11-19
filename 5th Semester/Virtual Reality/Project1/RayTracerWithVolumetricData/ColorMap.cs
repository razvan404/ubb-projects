using System.Collections.Generic;

namespace rt;

public class ColorMap
{
    private List<ushort> _from = new();
    private List<ushort> _to = new();
    private List<Color> _color = new();

    public ColorMap Add(ushort from, ushort to, Color color)
    {
        _from.Add(from);
        _to.Add(to);
        _color.Add(color);
        return this;
    }

    public Color GetColor(ushort value)
    {
        for (int i = 0; i < _from.Count; i++)
        {
            if (_from[i] <= value && _to[i] >= value)
            {
                return _color[i];
            }
        }
        return Color.NONE;
    }
}