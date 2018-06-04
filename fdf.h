#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include <math.h>
# include <fcntl.h>
# include "minilibx_macos/mlx.h"

#include <stdio.h>

# define PARSE		1
# define CLEAR		2
# define GET		3
# define W_NAME		"Fdf"
# define W_Y_SIZE	1000
# define W_X_SIZE	1000
# define W_FRAME	40
# define VALUE 		5

typedef	struct 		s_peak
{
	int				x;
	int				y;
	int 			value;
	int				color;
}					t_peak;

typedef struct		s_map
{
	int				x;
	int				y;
	t_peak			**map;
	int				ratio;
	int				axis_x;
	int				axis_y;
	int				x_frame;
	int				y_frame;
}					t_map;

typedef struct		s_mlx
{
	void			*ptr;
	void			*win;
	void			*img;
	int				y_angle;
	int				z_angle;
}					t_mlx;

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

/*
**axises.c
*/
int					get_ratio(t_map *map);
void				calculate_coords(t_map *map);

#endif