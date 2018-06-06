#include "../fdf.h"

static t_list	*get_file(char *filename)
{
	t_list	*file;
	char	*str;
	int		fd;

	file = NULL;
	fd = open(filename, O_RDONLY);
	while (get_next_line(fd, &str) > 0)
	{
		ft_lstaddend(&file, ft_lstnew(str, ft_strlen(str) + 1));
		free(str);
	}
	close(fd);
	return (file);
}

static int		count_numbers(char *str)
{
	int		count;

	count = 0;
	while (*str)
	{
		if (ft_isdigit(*str))
		{
			count++;
			if (*str == '-')
				str++;
			while (ft_isdigit(*str))
				str++;
		}
		if (*str)
			str++;
	}
	return (count);
}

static t_peak		*get_intarr(char *str, int len)
{
	t_peak	*res;
	int		i;

	i = 0;
	if ((res = (t_peak *)malloc(sizeof(t_peak) * len)))
	{
		while (i < len)
		{
			res[i].value = ft_atoi(str);
			if (*str == '-')
				str++;
			while (ft_isdigit(*str))
				str++;
			while (IS_SPACE(*str))
				str++;
			i++;
		}
	}
	return (res);
}

static void		fill_map(t_list *file, t_map *map)
{
	t_list	*lst;
	int 	i;

	map->y = ft_lstlen(file);
	map->x = count_numbers((char *)file->content);
	if ((map->map = (t_peak **)malloc(sizeof(t_peak *) * map->y)))
	{
		lst = file;
		i = 0;
		while (lst && i < map->y)
		{
			map->map[i] = get_intarr((char *)lst->content, map->x);
			i++;
			lst = lst->next;
		}
	}
}

t_map			*get_map(char *filename)
{
	t_list	*file;
	t_map	*map;

	if ((map = new_map()))
	{;
		if ((file = get_file(filename)))
		{
			fill_map(file, map);
			ft_lstdel(&file, &ft_memclr);
		}
	}
	return (map);
}
