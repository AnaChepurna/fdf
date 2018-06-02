#include "../fdf.h"

static int	exit_program(t_mlx	*mlx)
{
	mlx_destroy_window(mlx->ptr, mlx->win);
	exit(0);
	return (1);
}

int		key_handler(int keycode, void *param)
{
	t_mlx *mlx;

	mlx = (t_mlx *)param;
	ft_putstr("pressed key ");
	ft_putnbr(keycode);
	ft_putstr("\n");
	if (keycode == 53)
		return (exit_program(mlx));
	return (1);
}