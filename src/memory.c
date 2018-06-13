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

t_map		*map_manager(int mode, char *filename)
{
	static t_map *map = NULL;

	if (mode == PARSE)
	{
		map = get_map(filename);
		map->ratio = get_ratio(map);
		calculate_coords(map);
		if (map->colors)
			set_colors(map);
	}
	else if (mode == CLEAR)
			clear_map(&map);
	return (map);
}