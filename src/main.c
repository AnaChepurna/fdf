#include "../fdf.h"

static void		process(char *filename)
{
	(void)filename;
	t_mlx		mlx;

	mlx.y_angle = 0;
	mlx.z_angle = 0;
	mlx.zoom = 0;
	map_manager(PARSE, filename);
	mlx.ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.ptr, W_X_SIZE, W_Y_SIZE, W_NAME);
	draw(&mlx);
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