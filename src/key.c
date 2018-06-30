/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 18:43:03 by achepurn          #+#    #+#             */
/*   Updated: 2018/06/27 18:43:05 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static int	exit_program(t_mlx *mlx)
{
	mlx_destroy_window(mlx->ptr, mlx->win);
	map_manager(CLEAR, NULL);
	exit(0);
	return (1);
}

static int	y_shift(int keycode, t_mlx *mlx)
{
	t_map *map;

	map = map_manager(GET, NULL);
	if (keycode == 13 && map->map[map->y - 1][0].y - 20 > 0)
		shift_y(map, -20);
	else if (keycode == 1 && map->map[0][map->x - 1].y + 20 < mlx->win_y)
		shift_y(map, 20);
	render(mlx);
	return (1);
}

static int	x_shift(int keycode, t_mlx *mlx)
{
	t_map *map;

	map = map_manager(GET, NULL);
	if (keycode == 2 && map->map[0][0].x + 20 < mlx->win_x)
		shift_x(map, 20);
	else if (keycode == 0 && map->map[map->y - 1][map->x - 1].x - 20 > 0)
		shift_x(map, -20);
	render(mlx);
	return (1);
}

int			key_handler(int keycode, void *param)
{
	t_mlx *mlx;

	mlx = (t_mlx *)param;
	ft_putstr("pressed key ");
	ft_putnbr(keycode);
	ft_putstr("\n");
	if (keycode == 53)
		return (exit_program(mlx));
	if (keycode == 13 || keycode == 1)
		return (y_shift(keycode, mlx));
	if (keycode == 2 || keycode == 0)
		return (x_shift(keycode, mlx));
	return (1);
}
