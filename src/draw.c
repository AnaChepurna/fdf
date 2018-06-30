/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 18:44:04 by achepurn          #+#    #+#             */
/*   Updated: 2018/06/27 18:44:20 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int		count_pixels(t_peak *a, t_peak *b)
{
	int	x;
	int	y;
	int	z;
	int	res;

	x = a->x;
	y = a->y;
	res = 0;
	if (ABS(a->x - b->x) > ABS(a->y - b->y))
		z = ABS(a->x - b->x);
	else
		z = -ABS(a->y - b->y) / 2;
	while (y != b->y || x != b->x)
	{
		if (z > -ABS(a->x - b->x))
		{
			z -= ABS(a->y - b->y);
			x += a->x < b->x ? 1 : -1;
		}
		if (z < ABS(a->y - b->y))
		{
			z += ABS(a->x - b->x);
			y += a->y < b->y ? 1 : -1;
		}
		res++;
	}
	return (res);
}

void	draw_line(t_mlx *mlx, t_peak *a, t_peak *b)
{
	int	x;
	int	y;
	int	z;
	int	index;
	int	len;

	x = a->x;
	y = a->y;
	if (ABS(a->x - b->x) > ABS(a->y - b->y))
		z = ABS(a->x - b->x);
	else
		z = -ABS(a->y - b->y) / 2;
	index = 0;
	len = count_pixels(a, b);
	while (y != b->y || x != b->x)
	{
		mlx_pixel_put(mlx->ptr, mlx->win, x, y, get_draw_color(*a, *b, index, len));
		if (z > -ABS(a->x - b->x))
		{
			z -= ABS(a->y - b->y);
			x += a->x < b->x ? 1 : -1;
		}
		if (z < ABS(a->y - b->y))
		{
			z += ABS(a->x - b->x);
			y += a->y < b->y ? 1 : -1;
		}
		index++;
	}
}

void	render(t_mlx *mlx)
{
	t_map	*map;
	int		x;
	int		y;

	map = map_manager(GET, NULL);
	mlx_clear_window(mlx->ptr, mlx->win);
	y = -1;
	while (++y < map->y)
	{
		x = -1;
		while (++x < map->x)
		{
			if (x + 1 < map->x)
				draw_line(mlx, &map->map[y][x], &map->map[y][x + 1]);
			if (y + 1 < map->y)
				draw_line(mlx, &map->map[y][x], &map->map[y + 1][x]);
			mlx_pixel_put(mlx->ptr, mlx->win, map->map[y][x].x, map->map[y][x].y, map->map[y][x].color);
		}
	}
}

int		get_ratio(t_map *map)
{
	int	len;
	int	wlen;
	int	ratio;

	if (map->x > map->y)
	{
		len = map->x;
		wlen = W_X_SIZE;
	}
	else
	{
		len = map->y;
		wlen = W_Y_SIZE;
	}
	ratio = (wlen - (W_FRAME * 2)) / len;
	if (ratio < 1)
		ratio = 1;
	return (ratio);
}
