/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 18:44:26 by achepurn          #+#    #+#             */
/*   Updated: 2018/06/27 18:44:28 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void			error(char *massage)
{
	ft_putstr_fd(massage, 2);
	exit(1);
}

static void		init_mlx(t_mlx *mlx)
{
	t_map *map;
	map = map_manager(GET, NULL);
	mlx->win_x = map->map[map->y - 1][map->x - 1].x + W_FRAME;
	mlx->win_y = map->map[map->y - 1][0].y + W_FRAME;
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, mlx->win_x, mlx->win_y, W_NAME);
}

static void		process(char *filename)
{
	t_mlx		mlx;

	map_manager(PARSE, filename);
	init_mlx(&mlx);
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
		ft_putstr(" filename\n");
	}
	else
		process(argv[1]);
	return (0);
}
