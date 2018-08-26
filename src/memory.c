/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 18:44:33 by achepurn          #+#    #+#             */
/*   Updated: 2018/06/27 18:44:35 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

t_map		*new_map(void)
{
	t_map *map;

	if ((map = (t_map *)malloc(sizeof(t_map))))
	{
		map->x = 0;
		map->y = 0;
		map->map = NULL;
		map->colors = 1;
	}
	return (map);
}

static void	clear_map(t_map **map)
{
	int		i;

	if (map && *map)
	{
		if ((*map)->map)
		{
			i = -1;
			while (++i < (*map)->y)
			{
				if ((*map)->map[i])
					free((*map)->map[i]);
			}
			free((*map)->map);
		}
		free(*map);
		*map = NULL;
	}
}

static int	get_highest(t_map *map)
{
	int		res;
	int		i;
	int		j;

	res = 0;
	i = -1;
	while (++i < map->x)
	{
		j = -1;
		while (++j < map->y)
		{
			if (map->map[j][i].y < res)
				res = map->map[j][i].y;
			printf("%i ", map->map[j][i].y);
		}
		printf("\n");
	}
	ft_putnbr(res);
	return (-res);
}

void		map_set(t_map *map)
{
	zoom(map, map->ratio);
	rotate_z(map, -0.6);
	rotate_x(map, -0.6);
	shift_x(map, W_FRAME);
	shift_y(map, get_highest(map) + W_FRAME);
}

t_map		*map_manager(int mode, char *filename)
{
	static t_map *map = NULL;

	if (mode == PARSE)
	{
		map = get_map(filename);
		map->ratio = get_ratio(map);
		map_set(map);
		if (map->colors)
			set_colors(map);
	}
	else if (mode == CLEAR)
		clear_map(&map);
	return (map);
}
