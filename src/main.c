#include "../fdf.h"

static void		process(char *filename)
{
	(void)filename;
	t_mlx		mlx;

	map_manager(PARSE, filename);
	mlx.ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.ptr, 1000, 1000, "test");
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