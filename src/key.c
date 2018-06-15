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
	t_map *map;

	map = map_manager(GET, NULL);
	if (keycode == 91)
		rotate_x(map, 0.03);
	else
		rotate_x(map, -0.03);
	render(mlx);
	return (1);
}

// static int	z_angle(int keycode, t_mlx *mlx)
// {
// 	if (keycode == 88)
// 		mlx->z_angle++;
// 	else
// 		mlx->z_angle--;
// 	if (mlx->z_angle < 0)
// 		mlx->z_angle = 11;
// 	if (mlx->z_angle > 11)
// 		mlx->z_angle = 0;
// 	draw(mlx);
// 	return (1);
// }

// static int	zoom(int keycode, t_mlx *mlx)
// {
// 	t_map	*map;

// 	map = map_manager(GET, NULL);
// 	if (keycode == MINUS)
// 	{
// 		if (map->ratio > -2 * (mlx->zoom - 1))
// 			mlx->zoom--;
// 	}
// 	else
// 	{
// 		if (map->ratio * (mlx->zoom + 1) < W_Y_SIZE / 2)
// 			mlx->zoom++;
// 	}
// 	render_zoom(map, mlx);
// 	draw(mlx);
// 	return (1);
// }

// static int	shift(int keycode, t_mlx *mlx)
// {
	
// }

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
	// if (keycode == 88 || keycode == 86)
	// 	return (z_angle(keycode, mlx));
	return (1);
}