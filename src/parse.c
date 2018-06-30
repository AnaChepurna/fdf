/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 18:44:41 by achepurn          #+#    #+#             */
/*   Updated: 2018/06/27 18:44:42 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static t_list		*get_file(char *filename)
{
	t_list	*file;
	char	*str;
	int		fd;

	file = NULL;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error("Error: file is unavailable\n");
	while (get_next_line(fd, &str) > 0)
	{
		ft_lstaddend(&file, ft_lstnew(str, ft_strlen(str) + 1));
		free(str);
	}
	close(fd);
	return (file);
}

static int			parse_color(char **str, t_map *map)
{
	int ret;

	if (map)
		map->colors = 0;
	(*str)++;
	if (ft_strnequ("0x", *str, 2) || ft_strnequ("0X", *str, 2))
	{
		*str += 2;
		ret = ft_atoi_base(*str, 16);
	}
	else
		ret = ft_atoi_base(*str, 16);
	while (ft_isdigit(**str) || (**str >= 'a' && **str <= 'f')
		|| (**str >= 'A' && **str <= 'F'))
		(*str)++;
	return (ret);
}

static int			count_numbers(char *str)
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
				parse_color(&str, NULL);
		}
		if (*str)
			str++;
	}
	return (count);
}

static t_peak		*get_intarr(char *str, int len, t_map *map, int y)
{
	t_peak	*res;
	int		i;

	i = -1;
	if (!(res = (t_peak *)malloc(sizeof(t_peak) * len)))
		return (NULL);
	while (++i < len)
	{
		res[i].y = y;
		res[i].x = i;
		while (IS_SPACE(*str))
			str++;
		if (!*str)
			error("Error: error in input file\n");
		res[i].z = ft_atoi(str);
		res[i].value = res[i].z;
		while (*str == '-' || ft_isdigit(*str))
			str++;
		res[i].color = *str == ',' ? parse_color(&str, map) : 0xffffff;
	}
	while (IS_SPACE(*str))
		str++;
	if (*str)
		error("Error: error in input file\n");
	return (res);
}

t_map				*get_map(char *filename)
{
	t_list	*file;
	t_list	*lst;
	t_map	*map;
	int		i;

	if (!(map = new_map()))
		return (NULL);
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
				map->map[i] = get_intarr((char *)lst->content,
					map->x, map, i);
				lst = lst->next;
			}
		}
		ft_lstdel(&file, &ft_memclr);
	}
	return (map);
}
