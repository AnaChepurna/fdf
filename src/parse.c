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
			while (ft_isdigit(*str))
				str++;
		}
		str++;
	}
	return (count);
}

static int		*get_intarr(char *str, int len)
{
	int		*res;
	int		i;

	i = 0;
	if ((res = (int *)malloc(sizeof(int) * len)))
	{
		while (i < len)
		{
			res[i] = ft_atoi(str);
			while (ft_isdigit(*str))
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
	if ((map->map = (int **)malloc(sizeof(int *))))
	{
		lst = file;
		i = 0;
		while (lst && i < map->x)
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
	{
		if ((file = get_file(filename)))
		{
			fill_map(file, map);
			ft_lstdel(&file, &ft_memclr);
		}
	}
	return (map);
}
