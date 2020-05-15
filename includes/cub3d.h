/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugothms <hugothms@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 09:33:37 by hugothms          #+#    #+#             */
/*   Updated: 2020/05/15 19:50:44 by hugothms         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <time.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <errno.h>

# include <unistd.h>

# include "../libft/libft.h"
# include "mlx.h"
# include "get_next_line.h"

# define OPEN_ERROR -1
# define CLOSE_ERROR -2
# define PARSE_ERROR -3
# define MLX_ERROR -4
# define MALLOC_ERROR -5

# define THETA 0.01745329
/*
** Keycodes and screen size LINUX and MAC
*/
# ifndef LINUX
#  define ESC		65307
#  define LEFT		65361
#  define RIGHT		65363
#  define UP		65362
#  define DOWN		65364
#  define KEY_Q		113
#  define KEY_D		100
#  define KEY_Z		122
#  define KEY_S		115
# else
#  define ESC		53
#  define LEFT		123
#  define RIGHT		124
#  define UP		126
#  define DOWN		125
#  define KEY_A		0
#  define KEY_S		1
#  define KEY_D		2
#  define KEY_W		13
#  define KEY_Q		12
#  define KEY_E		14
#  define KEY_J		38
#  define KEY_K		40
#  define KEY_L		37
#  define KEY_I		34
#  define KEY_U		32
#  define KEY_O		31
#  define KEY_SPACE	49
#  define KEY_PLUS	69
#  define KEY_MINUS	78
# endif

typedef struct		s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
}					t_mlx;

typedef struct		s_img
{
	void			*img_ptr;
 	int				bits_per_pixel;
	int				size_line;
	int				endian;
	unsigned char	*data;
}					t_img;

typedef struct		s_couple
{
	int				w;
	int				h;
}					t_couple;

typedef struct		s_pos
{
	float			x;
	float			y;
}					t_pos;

typedef struct		s_rgb
{
	int				r;
	int				g;
	int				b;
}					t_rgb;

typedef struct		s_scene
{
	t_couple		resolution;
	char			**textures;
	t_rgb			*floor_color;
	t_rgb			*ceilling_color;
	char			**map;
	t_couple 		size;
	t_pos			position;
	t_pos			orientation;
}					t_scene;

typedef struct		s_window
{
	t_mlx			*mlx;
	t_img			*img;
	t_scene			*scene;
}					t_window;

# define NB_TEXTURES 5
# define WHITE_SPACES " \t"
# define NB_ELEM_RESOLUTION 3
# define NB_ELEM_TEXTURE 2
# define NB_ELEM_COLOR 2

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3
# define SPRITE 4
//ft_putchar('e');

t_scene		*get_scene(const int argc, const char *argv[]);

void	set_resolution(t_scene *scene, char **data);
void	set_texture(t_scene *scene, char **data, int code);
void 	set_color(t_scene *scene, char **data, int code);

t_rgb	*int_to_rgb(int r, int g, int b);
t_rgb	*str_to_rgb(char *str);
int		rgb_to_int(t_rgb rgb);

char	*screenshot_datetime(char res[]);
int     ft_tab_size(char **tab);

void	print_err_and_exit(char *str, int err);
void	free_tab(void **tab);

void			save_bmp(const char *filename, const unsigned char *data, const t_couple resolution);

#endif