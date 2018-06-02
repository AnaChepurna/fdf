#include "../fdf.h"

t_map		*new_map(void)
{
	t_map *map;

	if ((map = (t_map *)malloc(sizeof(t_map))))
	{
		map->x = 0;
		map->y = 0;
		map->map = NULL;
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
				free((*map)->map[i]);
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
		map = get_map(filename);
	else if (mode == CLEAR)
	{
		if (map)
			clear_map(&map);
	}
	return (map);
}