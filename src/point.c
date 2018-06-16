#include "../fdf.h"

void	rotate_x(t_map *map, double angle)
{
	int		x;
	int		y;
	float	copy_y;
	float	copy_z;
	double	rad;

	y = -1;
	while (++y < map->y)
	{
		x = -1;
		while (++x < map->x)
		{
			copy_y = map->map[y][x].y;
			copy_z = map->map[y][x].z;
			rad = atan2(copy_y, copy_z) + angle;
			map->map[y][x].y = hypot(copy_y, copy_z) * sin(rad);
			map->map[y][x].z = hypot(copy_y, copy_z) * cos(rad);
		}
	}
}

void	rotate_z(t_map *map, double angle)
{
	int		x;
	int		y;
	double	copy_x;
	double	copy_y;
	double	rad;

	y = -1;
	while (++y < map->y)
	{
		x = -1;
		while (++x < map->x)
		{
			copy_y = map->map[y][x].y;
			copy_x = map->map[y][x].x;
			rad = atan2(copy_y, copy_x) + angle;
			map->map[y][x].y = hypot(copy_y, copy_x) * sin(rad);
			map->map[y][x].x = hypot(copy_y, copy_x) * cos(rad);
		}
	}
}

void	zoom(t_map *map, int value)
{
	static int n = 0;
	int		x;
	int		y;

	y = -1;
	while (++y < map->y)
	{
		x = -1;
		while (++x < map->x)
		{
			map->map[y][x].x *= value;//map->ratio * 0.7;
			map->map[y][x].y *= value;// map->ratio * 0.7;
			if (!n)
				map->map[y][x].z *= VALUE;
			else
				map->map[y][x].z *= value;
		}
	}
	n++;
}

void	shift(t_map *map, int value)
{
	int		x;
	int		y;

	y = -1;
	while (++y < map->y)
	{
		x = -1;
		while (++x < map->x)
		{
			map->map[y][x].x += value;//map->ratio * 0.7;
			map->map[y][x].y += value;// map->ratio * 0.7;
		}
	}
}
