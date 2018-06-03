#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include <math.h>
# include <fcntl.h>
# include "minilibx_macos/mlx.h"

# define PARSE		1
# define CLEAR		2
# define GET		3
# define PLUS		1
# define MINUS		2
# define W_NAME		"Fdf"
# define W_Y_SIZE	1000
# define W_X_SIZE	1000
# define ABS(x)		((x) > 0 ? (x) : -(x))

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
	void			*img;
}					t_mlx;

typedef	struct s_peak
{
	int			x;
	int			y;
}				t_peak;

/*
**memory.c
*/
t_map				*new_map(void);
t_map				*map_manager(int mode, char *filename);

/*
**parse.c
*/
t_map				*get_map(char *filename);

/*
**key.h
*/
int					key_handler(int keycode, void *param);

/*
**draw.c
*/
void				draw(t_mlx *mlx);

#endif