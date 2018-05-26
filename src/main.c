#include "../fdf.h"

static void		process(char *filename)
{
	(void)filename;
	//t_map		*map;
	t_mlx		mlx;

	//map = get_map(filename);
	mlx.ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.ptr, 2000, 2000, "test");
	while (42)
	{}
	//clear_map(&map);
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