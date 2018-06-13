#include "../fdf.h"

static int		get_color(int	value)
{
	static int	step = 0xff / COLOR_VAL;
	int			rgb[3];

	if (value >= COLOR_VAL * 2)
		return (0xff0000);
	if (value < COLOR_VAL * -2)
		return (0x0000ff);
	rgb[0] = 0;
	rgb[1] = 0xff;
	rgb[2] = 0;
	if (value >= COLOR_VAL)
	{
		rgb[0] = 0xff;
		rgb[1] = 0xff - step * (COLOR_VAL - value);
	}
	else if (value >= 0)
		rgb[0] = step * value;
	else if (value >= -COLOR_VAL)
		rgb[2] = 0xff + step * value;
	else
	{
		rgb[2] = 0xff;
		rgb[1] = 0xff + step * (value - COLOR_VAL);
	}
	return ((rgb[0] << 16) + (rgb[1] << 8) + rgb[2]);
}

void			set_colors(t_map *map)
{
	int		j;
	int		i;

	j = -1;
	while (++j < map->y)
	{
		i = -1;
		while (++i < map->x)
		{
			map->map[j][i].color = get_color(map->map[j][i].value);
			printf("%i = %#x; ", map->map[j][i].value, map->map[j][i].color);
		}
		printf("\n");
	}
}

int				get_draw_color(t_peak a, t_peak b, int index, int max)
{
	int		red;
	int		green;
	int		blue;

	red = (a.color & 0xff0000) >> 16;
	green = (a.color & 0x00ff00) >> 8;
	blue = a.color & 0x0000ff;
	if ((b.color & 0xff0000 >> 16) >= red)
		red += (((b.color & 0xff0000) >> 16) - red) / max * index;
	else
		red -= (red - ((b.color & 0xff0000) >> 16)) / max * index;
	if (((b.color & 0x00ff00) >> 8) >= green)
		green += (((b.color & 0x00ff00) >> 8) - green) / max * index;
	else
		green -= (green - ((b.color & 0x00ff00) >> 8)) / max * index;
	if ((b.color & 0x0000ff) >= blue)
		blue += (b.color & 0x0000ff - blue) / max * index;
	else
		blue -= (blue - b.color & 0x0000ff) / max * index;
	return ((red << 16) + (green << 8) + blue);
}