#include "../fdf.h"



// void			draw_line(t_mlx *mlx, t_peak a, t_peak b)
// {
// 	int		i;
// 	int		x;
// 	int		y;
// 	int		del;
// 	int		module_x;
// 	int		module_y;

// 	i = 0;
// 	module_y = b.real_y - a.real_y;
// 	module_x = b.real_x - a.real_x;
// 	//printf("a: %i-%i; b: %i-%i\n", a.real_y, a.real_x, b.real_y, b.real_x);
// 	//printf("module_x = %i, module_y = %i\n", module_x, module_y);
// 	del = ABS(module_x) > ABS(module_y) ? ABS(module_x) : ABS(module_y);
// 	while (i < del)
// 	{
// 		x = a.real_x + module_x * i / del;
// 		y = a.real_y + module_y * i / del;
// 		mlx_pixel_put(mlx->ptr, mlx->win, x, y, get_draw_color(a, b, i, del));
// 		i++;
// 	}
// }

// static void		get_z_angle(t_mlx *mlx, t_peak *peak, t_map *map)
// {
// 	double		radius;
// 	double		y;
// 	double		x;
// 	double		angle;

// 	printf("axis y = %i, axis x = %i\n", map->axis_y, map->axis_x);
// 	printf("prev y = %i, real x = %i\n", peak->real_y, peak->real_x);
// 	y = ABS(map->axis_y - peak->real_y);
// 	x = ABS(map->axis_x - peak->real_x);
// 	printf("y = %f, x = %f\n", y, x);
// 	radius = hypot(y, x);
// 	printf("radius = %f\n", radius);
// 	if (y)
// 	{
// 		printf("1 = %f\n", atan(1.0));
// 		angle = atan(x / y);
// 	}
// 	else
// 		angle = 1.5708;
// 	printf("angle was %f\n", angle);
// 	angle += 0.261799 * mlx->z_angle;
// 	printf("angle become %f\n", angle);
// 	if (angle < 1.5708)
// 	{
// 		y = radius * cos(angle);
// 		x = radius * sin(angle);
// 	}
// 	else
// 	{
// 		angle -= 1.5708;
// 		x = radius * cos(angle);
// 		y = radius * sin(angle);
// 	}
// 	printf(" NEW!! y = %f, x = %f\n", y, x);
// 	if (peak->real_y < map->axis_y && peak->real_x <= map->axis_x)
// 	{
// 		peak->real_x = map->axis_x - x;
// 		peak->real_y = map->axis_y - y;
// 	}
// 	else if (peak->real_y == map->axis_y && peak->real_x <= map->axis_x)
// 	{
// 		peak->real_x = map->axis_x - x;
// 		peak->real_y = map->axis_y + y;
// 	}
// 	else if (peak->real_y > map->axis_y && peak->real_x >= map->axis_x)
// 	{
// 		peak->real_x = map->axis_x + x;
// 		peak->real_y = map->axis_y + y;
// 	}
// 	else if (peak->real_y == map->axis_y && peak->real_x > map->axis_x)
// 	{
// 		peak->real_x = map->axis_x + x;
// 		peak->real_y = map->axis_y - y;
// 	}
// 	else if (peak->real_y == map->axis_y && peak->real_x > map->axis_x)
// 	{
// 		peak->real_x = map->axis_x - x;
// 		peak->real_y = map->axis_y + y;
// 	}
// 		printf("real y = %i, real x = %i\n", peak->real_y, peak->real_x);
// 		mlx_pixel_put(mlx->ptr, mlx->win, 100, 864, 0xffffff);
// }

// static void		get_real_coords(t_mlx *mlx, t_peak *peak, t_map *map)
// {
// 	static int	hight[24] = {0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1, 0,
// 		-1, -2, -3, -4, -5, -6, -5, -4, -3, -2, -1};
// 	static int	angle[24] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ,11, 12,
// 		11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

// 	peak->real_y = peak->y;
// 	peak->real_x = peak->x;
// 	peak->real_y += ((map->axis_y - peak->y) * angle[mlx->y_angle] / 6);
// 	peak->real_y -= VALUE * peak->value * hight[mlx->y_angle] / 6;
// 	if (mlx->z_angle)
// 		get_z_angle(mlx, peak, map);
// 		printf("---------------------------------------\n");
// }

// static	void	draw_axises(t_mlx *mlx, t_map *map)
// { 
// 	int x;
// 	int y;

// 	x = map->axis_x;
// 	y = 0;
// 	while (y < W_Y_SIZE)
// 	{
// 		mlx_pixel_put(mlx->ptr, mlx->win, x, y, 0x633D5C);
// 		y += 6;
// 	}
// 	y = map->axis_y;
// 	x = 0;
// 	while (x < W_X_SIZE)
// 	{
// 		mlx_pixel_put(mlx->ptr, mlx->win, x, y, 0xc0c0c0);
// 		x += 6;
// 	}
// }

// void			draw(t_mlx *mlx)
// {
// 	int y;
// 	int x;
// 	t_map	*map;
// 	t_peak 	peak;

// 	//printf("y_angle = %i\n", mlx->y_angle);
// 	mlx_clear_window(mlx->ptr, mlx->win);
// 	map = map_manager(GET, NULL);
// 	draw_axises(mlx, map);

// 	y = -1;
// 	while (++y < map->y)
// 	{
// 		x = -1;
// 		while (++x < map->x)
// 		{
// 			peak = map->map[y][x];
// 			printf("%s\n", RED);
// 			get_real_coords(mlx, &peak, map);
// 			printf("%s\n", RESET);
// 			if (x < map->x - 1)
// 			{
// 				get_real_coords(mlx, &(map->map[y][x + 1]), map);
// 				draw_line(mlx, peak, map->map[y][x + 1]);
// 			}
// 			if (y < map->y - 1)
// 			{
// 				get_real_coords(mlx, &(map->map[y + 1][x]), map);
// 				draw_line(mlx, peak, map->map[y + 1][x]);
// 			}
// 		}
// 	}
// }