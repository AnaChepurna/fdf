#include "../fdf.h"

static void		vector(int *i, int mode)
{
	if (mode == PLUS)
		(*i)++;
	else if (mode == MINUS)
		(*i)--;
}

void			draw_line(t_mlx *mlx, t_peak *a, t_peak *b)
{
	int 	module_y;
	int 	module_x;
	int		mode_y;
	int		mode_x;

	module_y = a->y - b->y;
	module_x = a->x - b->x;

}

void			draw_pixel(void *ptr, void *win, int x, int y, int color)
{
	static int 	size = 6;

	mlx_pixel_put(ptr, win, (x + 1) * size, (y + 1) * size, color);
}

void			draw(t_mlx *mlx)
{
	int y;
	int x;
	t_map	*map;
	int color;

	map = map_manager(GET, NULL);
	int green = 0x00ff00;
	int pink = 0xf08080;
	y = -1;
	while (++y < map->y)
	{
		x = -1;
		while (++x < map->x)
		{
			color  = map->map[y][x] == 0 ? green : pink;
			draw_pixel(mlx->ptr, mlx->win, x, y, color);
			color += 100;
		}
	}
}