#include "../fdf.h"

static void		get_real_coords(int *y, int *x, t_mlx *mlx, t_peak peak, t_map *map)
{
	if (peak.y < map->axis_y)
	{
		*y = peak.y + ((map->axis_y - peak.y) / 3 * mlx->y_angle);
	}
	else if (peak.y > map->axis_y)
	{
		*y = peak.y + ((map->axis_y - peak.y) / 3 * mlx->y_angle);
	}
	*x = peak.x;
}

static	void	draw_axises(t_mlx *mlx, t_map *map)
{
	int x;
	int y;

	x = map->axis_x;
	y = 0;
	while (y < W_Y_SIZE)
	{
		mlx_pixel_put(mlx->ptr, mlx->win, x, y, 0xc0c0c0);
		y += 6;
	}
	y = map->axis_y;
	x = 0;
	while (x < W_X_SIZE)
	{
		mlx_pixel_put(mlx->ptr, mlx->win, x, y, 0xc0c0c0);
		x += 6;
	}
}

void			draw(t_mlx *mlx)
{
	int y;
	int x;
	t_map	*map;
	t_peak 	peak;
	int color1;
	int	y_coord;
	int	x_coord;

	printf("y_angle = %i\n", mlx->y_angle);
	mlx_clear_window(mlx->ptr, mlx->win);
	map = map_manager(GET, NULL);
	draw_axises(mlx, map);
	color1 = 0x00ff00;
	int color2 = 0xff33da;
	y = -1;
	while (++y < map->y)
	{
		x = -1;
		while (++x < map->x)
		{
			peak = map->map[y][x];
			get_real_coords(&y_coord, &x_coord, mlx, peak, map);
			mlx_pixel_put(mlx->ptr, mlx->win, x_coord, y_coord, y < map->y / 2 ? color1 : color2);
		}
	}
}