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

int			key_handler(int keycode, void *param)
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
