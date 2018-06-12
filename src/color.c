#include "../fdf.h"

int		get_color(int value, int base, int setter)
{
	static int	step = 0;
	int			i;

	if (!step)
		step = 0x0000ff / COLOR_VAL;
	i = -1;
	while (++i < value)
		base += setter * step;
	while (--i >= value)
		base -= setter * step;
	return (base);
}

void	set_colors(t_map *map)
{
	int		j;
	int		i;

	j = -1;
	while (++j < map->y)
	{
		i = -1;
		while (++i < map->x)
		{
			if (map->map[j][i].value > COLOR_VAL)
				map->map[j][i].color = get_color(COLOR_VAL - map->map[j][i].value, 0xff0000, 0x000101);
			if (map->map[j][i].value > COLOR_VAL / 2)
				map->map[j][i].color = get_color(COLOR_VAL - map->map[j][i].value, 0xffff00, 0x000100);
			else
				map->map[j][i].color = 0x00ff00;
		}
	}
}