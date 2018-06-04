#include "../fdf.h"

int			get_ratio(t_map *map)
{
	int len;
	int	wlen;
	int	ratio;

	map->x_frame = W_FRAME;
	map->y_frame = W_FRAME;
	if (map->x > map->y)
	{
		len = map->x;
		wlen = W_X_SIZE;
	}
	else
	{
		len = map->y;
		wlen = W_Y_SIZE;
	}
	ratio = (wlen - (W_FRAME * 2)) / len;
	if (map->x > map->y)
		map->y_frame += (W_Y_SIZE - ratio * map->y) / 2;
	else
		map->x_frame += (W_X_SIZE - ratio * map->x) / 2;
	return (ratio);
}

static int	get_axis(int num, int ratio, int frame)
{
	if (num % 2)
		return ((num / 2) * ratio + frame);
	else
		return (((num / 2 - 1) * ratio + frame) + ratio / 2);
}

void		calculate_coords(t_map *map)
{
	int 	i;
	int 	j;

	map->axis_y = get_axis(map->y, map->ratio, map->y_frame);
	map->axis_x = get_axis(map->x, map->ratio, map->x_frame);
	i = -1;
	while (++i < map->y)
	{
		j = -1;
		while (++j < map->x)
		{
			map->map[i][j].y = (i * map->ratio) + map->y_frame;
			map->map[i][j].x = (j * map->ratio) + map->x_frame;
		}
	}
}
