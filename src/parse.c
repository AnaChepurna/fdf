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

static void			parse_color(char **str, t_peak *peak, t_map *map)
{
	if (map)
		map->colors = 0;
	(*str)++;
	if (ft_strnequ("0x", *str, 2) || ft_strnequ("0X", *str, 2))
	{
		*str += 2;
		if (peak)
			peak->color = ft_atoi_base(*str, 16);
	}
	else
	{
		if (peak)
			peak->color = ft_atoi_base(*str, 16);
	}
	while (ft_isdigit(**str) || (**str >= 'a' && **str <= 'f')
		|| (**str >= 'A' && **str <= 'F'))
		(*str)++;
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
			if (*str == ',')
				parse_color(&str, NULL, NULL);
		}
		if (*str)
			str++;
	}
	return (count);
}

static t_peak		*get_intarr(char *str, int len, t_map *map)
{
	t_peak	*res;
	int		i;

	i = 0;
	if ((res = (t_peak *)malloc(sizeof(t_peak) * len)))
	{
		while (i < len)
		{
			while (IS_SPACE(*str))
				str++;
			res[i].value = ft_atoi(str);
			if (*str == '-')
				str++;
			while (ft_isdigit(*str))
				str++;
			if (*str == ',')
				parse_color(&str, &res[i], map);
			else
				res[i].color = 0xffffff;
			i++;
		}
	}
	return (res);
}

t_map			*get_map(char *filename)
{
	t_list	*file;
	t_list	*lst;
	t_map	*map;
	int 	i;

	if ((map = new_map()))
	{
		if ((file = get_file(filename)))
		{
			map->y = ft_lstlen(file);
			map->x = count_numbers((char *)file->content);
			if ((map->map = (t_peak **)malloc(sizeof(t_peak *) * map->y)))
			{
				lst = file;
				i = -1;
				while (lst && ++i < map->y)
				{
					map->map[i] = get_intarr((char *)lst->content, map->x, map);
					lst = lst->next;
				}
			}
			ft_lstdel(&file, &ft_memclr);
			printf("len = %i\n", map->x);
		}
	}
	return (map);
}
