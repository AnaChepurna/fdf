#include "../fdf.h"

static int	exit_program(t_mlx	*mlx)
{
	mlx_destroy_window(mlx->ptr, mlx->win);
	map_manager(CLEAR, NULL);
	exit(0);
	return (1);
}

static int	y_angle(int keycode, t_mlx *mlx)
{
	if (keycode == 91)
		mlx->y_angle--;
	else
		mlx->y_angle++;
	if (mlx->y_angle < 0)
		mlx->y_angle = 11;
	if (mlx->y_angle > 11)
		mlx->y_angle = 0;
	draw(mlx);
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
	if (keycode == 91 || keycode == 84)
		return (y_angle(keycode, mlx));
	return (1);
}