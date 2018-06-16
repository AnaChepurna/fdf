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
# define W_Y_SIZE	1200
# define W_X_SIZE	1200
# define W_FRAME	100
# define VALUE 		10
# define COLOR_VAL	10
# define ABS(n)		((n) >= 0 ? (n) : -(n))

typedef	struct 		s_peak
{
	int				x;
	int				y;
	int				z;
	int 			value;
	int				color;
}					t_peak;

typedef struct		s_map
{
	int				x;
	int				y;
	t_peak			**map;
	int				ratio;
	int				colors;
}					t_map;

typedef struct		s_mlx
{
	void			*ptr;
	void			*win;
	void			*img;
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
**axises.c
*/
int					get_ratio(t_map *map);
void				calculate_coords(t_map *map);

/*
**color.c
*/
void				set_colors(t_map *map);
int					get_draw_color(t_peak a, t_peak b, int index, int max);

void	rotate_z(t_map *map, double angle);
void	rotate_x(t_map *map, double angle);
void	shift(t_map *map, int value);
void	zoom(t_map *map, int value);
void	render(t_mlx *mlx);



#endif