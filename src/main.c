#include "../fdf.h"

static void		init_mlx(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, W_X_SIZE, W_Y_SIZE, W_NAME);
}

static void		process(char *filename)
{
	t_mlx		mlx;

	map_manager(PARSE, filename);
	init_mlx(&mlx);
	//draw(&mlx);
	render(&mlx);
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