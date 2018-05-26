#include "../fdf.h"

t_list	*get_file(char *filename)
{
	t_list	*file;
	char	*str;
	int		fd;

	file = NULL;
	fd = open(filename, O_RDONLY);
	while (get_next_line(&str, fd) > 0)
	{
		ft_lstaddend(&lst, ft_lstnew(str, ft_strlen(str) + 1));
		free(str);
	}
	close(fd);
	return (file);
}

t_map	*get_map(char *filename)
{
	t_list	*file;

	file = get_file(filename);
	ft_lstdel(&file, &ft_memclr);
}