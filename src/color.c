#include "../fdf.h"

// static int		get_color(int value, int base, int setter)
// {
// 	static int	step = 0;
// 	int			i;

// 	if (!step)
// 		step = 0x0000ff * 2 / COLOR_VAL;
// 	i = -1;
// 	while (++i < value)
// 	{
// 		if (base <= 0xfff0f0)
// 			base += setter * step;
// 	}
// 	while (--i >= value)
// 		base -= setter * step;
// 	return (base);
// }

static int		point_color(int	value)
{
	if (value < 0)
		return (0x00ffff);
	if (value < COLOR_VAL)
		return (0x00ff00);
	else if (value < COLOR_VAL / 2)
		return (0xffff00);
	return (0xff0000);
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
			map->map[j][i].color = point_color(map->map[j][i].value);
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