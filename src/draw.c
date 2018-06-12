#include "../fdf.h"

void			draw_line(t_mlx *mlx, t_peak a, t_peak b)
{
	int		i;
	int		x;
	int		y;
	int		del;
	int		module_x;
	int		module_y;

	i = 0;
	module_y = b.real_y - a.real_y;
	module_x = b.real_x - a.real_x;
	//printf("a: %i-%i; b: %i-%i\n", a.real_y, a.real_x, b.real_y, b.real_x);
	//printf("module_x = %i, module_y = %i\n", module_x, module_y);
	del = ABS(module_x) > ABS(module_y) ? ABS(module_x) : ABS(module_y);
	while (i < del)
	{
		x = a.real_x + module_x * i / del;
		y = a.real_y + module_y * i / del;
		mlx_pixel_put(mlx->ptr, mlx->win, x, y, a.color);//0x00ff00);
		i++;
	}
}

static void		get_real_coords(t_mlx *mlx, t_peak *peak, t_map *map)
{
	static int	hight[24] = {0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1, 0,
		-1, -2, -3, -4, -5, -6, -5, -4, -3, -2, -1};
	static int	angle[24] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ,11, 12,
		11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

	peak->real_y = peak->y;
	peak->real_x = peak->x;
	peak->real_y += ((map->axis_y - peak->y) * angle[mlx->y_angle] / 6);
	peak->real_y -= VALUE * peak->value * hight[mlx->y_angle] / 6;
	// peak->real_y += (map->axis_y - peak->y) * angle[mlx->z_angle] / 6;
	// peak->real_y += (map->axis_x - peak->x) * angle[mlx->z_angle] * 2 / 12;
	// peak->real_x -= (map->axis_y - peak->y) * angle[mlx->z_angle] * 2 / 12;
	// peak->real_x += (map->axis_x - peak->x) * angle[mlx->z_angle] / 6;
}

static	void	draw_axises(t_mlx *mlx, t_map *map)
{ 
	int x;
	int y;

	x = map->axis_x;
	y = 0;
	while (y < W_Y_SIZE)
	{
		mlx_pixel_put(mlx->ptr, mlx->win, x, y, 0x633D5C);
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

	//printf("y_angle = %i\n", mlx->y_angle);
	mlx_clear_window(mlx->ptr, mlx->win);
	map = map_manager(GET, NULL);
	draw_axises(mlx, map);

	y = -1;
	while (++y < map->y)
	{
		x = -1;
		while (++x < map->x)
		{
			peak = map->map[y][x];
			get_real_coords(mlx, &peak, map);
			//printf("value of %i-%i = %i\n", y, x, peak.value);
			if (x < map->x - 1)
			{
				get_real_coords(mlx, &(map->map[y][x + 1]), map);
				draw_line(mlx, peak, map->map[y][x + 1]);
			}
			if (y < map->y - 1)
			{
				get_real_coords(mlx, &(map->map[y + 1][x]), map);
				draw_line(mlx, peak, map->map[y + 1][x]);
			}
			// if (x > 0)
			// 	draw_line(mlx, peak, map->map[y][x - 1]);
		}
	}
}