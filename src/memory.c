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

void		map_set(t_map *map)
{
	int	x;
	int	y;

	y = -1;
	printf("%i\n", map->ratio);
	while (++y < map->y)
	{
		x = -1;
		while (++x < map->x)
		{
			map->map[y][x].x *= map->ratio;
			map->map[y][x].x += (W_X_SIZE - map->x * map->ratio) / 2;
			map->map[y][x].y *= map->ratio;
			map->map[y][x].y += (W_Y_SIZE - map->y * map->ratio) / 2;
			map->map[y][x].z *= VALUE;
		}
	}
}

t_map		*map_manager(int mode, char *filename)
{
	static t_map *map = NULL;

	if (mode == PARSE)
	{
		map = get_map(filename);
		map->ratio = get_ratio(map);
		//calculate_coords(map);
		map_set(map);
		if (map->colors)
			set_colors(map);
	}
	else if (mode == CLEAR)
			clear_map(&map);
	return (map);
}