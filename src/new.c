#include "../fdf.h"
#include "../fdf.h"

int		count_pixels(t_peak *a, t_peak *b)
{
	int	x;
	int	y;
	int	z;
	int res;

	x = a->x;
	y = a->y;
	res = 0;
	if (ABS(a->x - b->x) > ABS(a->y - b->y))
		z = ABS(a->x - b->x);
	else
		z = -ABS(a->y - b->y) / 2;
	while (y != b->y || x != b->x)
	{
		if (z > -ABS(a->x - b->x))
		{
			z -= ABS(a->y - b->y);
			x += a->x < b->x ? 1 : -1;
		}
		if (z < ABS(a->y - b->y))
		{
			z += ABS(a->x - b->x);
			y += a->y < b->y ? 1 : -1;
		}
		res++;
	}
	return (res);
}

void	draw_line(t_mlx *mlx, t_peak *a, t_peak *b)
{
	int	x;
	int	y;
	int	z;
	int	index;
	int	len;

	x = a->x; //+ (W_X_SIZE / 2);
	y = a->y; //+ + (W_Y_SIZE / 2);
	if (ABS(a->x - b->x) > ABS(a->y - b->y))
		z = ABS(a->x - b->x);
	else
		z = -ABS(a->y - b->y) / 2;
	printf("a = %i-%i, b = %i-%i\n", a->y, a->x, b->y, b->x);
	index = 0;
	len = count_pixels(a, b);
	while (y != b->y || x != b->x)
	{
		//printf("%i-%i\n", y, x);
		mlx_pixel_put(mlx->ptr, mlx->win, x, y, get_draw_color(*a, *b, index, len));
		if (z > -ABS(a->x - b->x))
		{
			z -= ABS(a->y - b->y);
			x += a->x < b->x ? 1 : -1;
		}
		if (z < ABS(a->y - b->y))
		{
			z += ABS(a->x - b->x);
			y += a->y < b->y ? 1 : -1;
		}
		index++;
	}
}

void	render(t_mlx *mlx)
{
	t_map	*map;
	int		x;
	int		y;

	printf("rendering\n");
	map = map_manager(GET, NULL);
	mlx_clear_window(mlx->ptr, mlx->win);
	y = -1;
	while (++y < map->y)
	{
		x = -1;
		while (++x < map->x)
		{
			if (x + 1 < map->x)
				draw_line(mlx, &map->map[y][x], &map->map[y][x + 1]);
			if (y + 1 < map->y)
				draw_line(mlx, &map->map[y][x], &map->map[y + 1][x]);
		}
	}
}

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
			//map->map[y][x].y += copy_y - map->map[y][x].y;
		}
	}
}

void	rotate_y(t_map *map, double angle)
{
	int		x;
	int		y;
	double	copy_x;
	double	copy_z;
	double	rad;

	y = -1;
	while (++y < map->y)
	{
		x = -1;
		while (++x < map->x)
		{
			copy_z = map->map[y][x].z;
			copy_x = map->map[y][x].x;
			rad = atan2(copy_z, copy_x) + angle;
			map->map[y][x].x = hypot(copy_z, copy_x) * sin(rad);
			map->map[y][x].z = hypot(copy_z, copy_x) * cos(rad);
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