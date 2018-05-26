#include "../fdf.h"

static void		process(char *filename)
{
	t_map		*map;

	map = get_map(filename);
	clear_map(&map);
}

int				main(int argc, char const *argv[])
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