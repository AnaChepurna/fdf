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
		ft_putendl(str);
		free(str);
	}
	close(fd);
	sleep(2);
	return (file);
}

static int		count_numbers(char *str)
{
	int		count;

	ft_putstr("count_numbers - ");
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
	ft_putnbr(count);
	ft_putstr("\n");
	sleep(2);
	return (count);
}

static int		*get_intarr(char *str, int len)
{
	int		*res;
	int		i;

	ft_putstr("get_intarr - ");
	ft_putendl(str);
	ft_putendl(">>>");
	i = 0;
	if ((res = (int *)malloc(sizeof(int) * len)))
	{
		while (i < len)
		{
			res[i] = ft_atoi(str);
			ft_putstr("str = ");
			ft_putendl(str);
			ft_putnbr (res[i]);
			ft_putstr (" ");
			while (ft_isdigit(*str))
				str++;
			while (IS_SPACE(*str))
				str++;
			i++;
		}
	}
	ft_putstr("\n");
	sleep(2);
	return (res);
}

static void		fill_map(t_list *file, t_map *map)
{
	t_list	*lst;
	int 	i;

	ft_putstr("fill_map\n");
	map->y = ft_lstlen(file);
	ft_putnbr (map->y);
	ft_putendl(" <- y");
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
		ft_putstr("map created\n");
		if ((file = get_file(filename)))
		{
			ft_putstr("file was read\n");
			fill_map(file, map);
			ft_putstr("map filled\n");
			int i = 0;
			while (i < map->y)
			{
				int j = 0;
				while (j < map->x)
				{
					ft_putnbr(map->map[i][j]);
					ft_putstr(" ");
					j++;
				}
				ft_putstr("\n");
				i++;
			}
			//ft_lstdel(&file, &ft_memclr);
		}
	}
	return (map);
}
