#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include <math.h>
# include <fcntl.h>
# include "minilibx_macos/mlx.h"

typedef struct		s_map
{
	int				x;
	int				y;
	int				**map;
}					t_map;

typedef struct		s_mlx
{
	void			*ptr;
	void			*win;
}					t_mlx;

/*
**memory.c
*/
t_map				*new_map(void);
void				clear_map(t_map **map);

/*
**parse.c
*/
t_map				*get_map(char *filename);

/*
**key.h
*/
int					key_handler(int keycode, void *param);

#endif