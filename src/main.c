#include "../fdf.h"

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
			drow_pixel(mlx->ptr, mlx->win, x, y, color);
			color += 100;
		}
	}
}

static void		process(char *filename)
{
	(void)filename;
	t_mlx		mlx;

	map_manager(PARSE, filename);
	mlx.ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.ptr, W_X_SIZE, W_Y_SIZE, W_NAME);
	drow(&mlx);
	mlx_key_hook(mlx.win, key_handler, &mlx);
	mlx_loop(mlx.ptr);
}

int				main(int argc, char *argv[])
{
	if (argc != 2)
	{
		ft_putstr("usage : ");
		ft_putstr(argv[0]);
		ft_putstr( " filename\n");
	}
	else
		process(argv[1]);
	return (0);
}