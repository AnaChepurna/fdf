#include "../fdf.h"

t_map	*new_map(void)
{
	t_map *map;

	if ((map = (t_map *)malloc(t_map)))
	{
		map->x = 0;
		map->y = 0;
		map->map = NULL;
	}
	return (map);
}

void	clear_map(t_map **map)
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