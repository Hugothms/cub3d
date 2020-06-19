/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 09:33:37 by hthomas           #+#    #+#             */
/*   Updated: 2020/06/19 17:13:50 by hthomas          ###   ########.fr       */
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
# include "get_next_line.h"
# ifdef LINUX
#  include "mlxlinux.h"
# else
#  include "mlx.h"
# endif

# define OPEN_ERROR		-1
# define CLOSE_ERROR	-2
# define PARSE_ERROR	-3
# define MLX_ERROR		-4
# define MALLOC_ERROR	-5

# define THETA			0.05
# define SPEED_MOVE		0.15
# define CEILING_COLOR	6185465
# define FLOOR_COLOR	2105376
# define FOV			0.66
# define SIZE_MINIMAP	5

# define GREY			11184810
# define RED			16711680
# define WHITE			16777215

# define MAX_WIDE		3840
# define NB_TEXTURES 5
# define WHITE_SPACES " \t"
# define NB_ELEM_RES 3
# define NB_ELEM_TEX 2
# define NB_ELEM_COLOR 2

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3
# define SPRITE 4

/*
** Keycodes LINUX and MAC
*/
# ifdef LINUX
#  define AZERTY		1
#  define ESC			65307
#  define ARROW_LEFT	65361
#  define ARROW_RIGHT	65363
#  define ARROW_UP		65362
#  define ARROW_DOWN	65364
#  define KEY_A			97
#  define KEY_D			100
#  define KEY_E			101
#  define KEY_F			102
#  define KEY_Q			113
#  define KEY_S			115
#  define KEY_W			119
#  define KEY_Z			122
# else
#  define AZERTY		0
#  define ESC			53
#  define ARROW_LEFT	123
#  define ARROW_RIGHT	124
#  define ARROW_UP		126
#  define ARROW_DOWN	125
#  define KEY_A			0
#  define KEY_S			1
#  define KEY_D			2
#  define KEY_F			3
#  define KEY_Z			11
#  define KEY_Q			12
#  define KEY_W			13
#  define KEY_E			14
#  define KEY_O			31
#  define KEY_U			32
#  define KEY_I			34
#  define KEY_L			37
#  define KEY_J			38
#  define KEY_K			40
#  define KEY_SPACE		49
#  define KEY_PLUS		69
#  define KEY_MINUS		78
# endif

typedef struct	s_2int
{
	int			w;
	int			h;
}				t_2int;

typedef struct	s_2float
{
	float		x;
	float		y;
}				t_2float;

typedef struct	s_dda
{
	t_2int		coord;
	t_2int		step;
	t_2int		delim;
	t_2int		draw;
	t_2float	sideDist;
	t_2float	deltaDist;
	t_2float	rayDir;
	int			side;
	int			line;
	int			lineHeight;
	double		perpWallDist[MAX_WIDE];
	int			index_sprite;
}				t_dda;

typedef struct	s_rgb
{
	int			r;
	int			g;
	int			b;
}				t_rgb;

typedef struct	s_draw
{
	t_2int		start;
	t_2float	end;
}				t_draw;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
}				t_mlx;

typedef struct	s_img
{
	void		*img_ptr;
	char		*data;
 	int			bits_per_pixel;
	int			size_line;
	int			endian;
	t_2int		size;
}				t_img;

typedef struct	s_move
{
	int			up;
	int			down;
	int			left;
	int			right;
	int			turn_left;
	int			turn_right;
}				t_move;

typedef struct	s_sprite
{
	double		x;
	double		y;
	int			nb;
}				t_sprite;

typedef struct	s_scene
{
	t_2int		res;
	char		**tex;
	t_img		*textures[NB_TEXTURES];
	t_rgb		*floor;
	t_rgb		*ceil;
	char		**map;
	t_2int		size;
	t_2float	pos;
	t_2float	dir;
	t_2float	plane;
	t_move		move;
	int			nb_sprite;
	t_sprite	*sprite;
}				t_scene;

typedef struct	s_window
{
	t_mlx		*mlx;
	t_img		*img;
	t_scene		*s;
}				t_window;

//check_map
void	check_map(char **map, t_2float pos, t_2int size);

//color
t_rgb	*int_to_rgb(int r, int g, int b);
t_rgb	*str_to_rgb(char *str);
int		rgb_to_int(t_rgb rgb);

//dda
void	calcul_dda(t_dda *dda, t_scene *s, int x);
void	set_side_dist(t_dda *dda, t_scene *s);
void	perform_dda(t_scene *s, t_dda *dda);

//draw
void	put_pixel(char *data, t_2int pixel, int color, t_2int res);
void	put_texture(char *data, t_2int pixel, char *texdata, t_2int res, int entier);
void	draw_v_line(char *data, t_2int pos, int len, int color, t_2int res);
void	draw_wall(char *data, t_dda *dda, t_scene *s);

//draw_minimap
void	draw_minimap(t_img *img, t_scene *scene);
void	draw_pos_minimap(t_img *img, t_scene *s);

//error
void	print_err_and_exit(char *str, int err);
int		close_function(const t_window *w);
void	free_scene(t_scene *scene);

//key
int		refresh(const t_window *w);
int		key_release(int keycode, t_move *move);
int		key_push(int keycode, t_move *move);
int		key_function(const int keycode, t_window *w);

//make_img
void	make_img(t_img *img, t_scene *scene);

//move
void	move_up(t_window *w);
void	move_down(t_window *w);
void	move_left(t_window *w);
void	move_right(t_window *w);

//move2
void	check_key_on(t_window *w);
void	turn_left(t_window *w);
void	turn_right(t_window *w);

//parse_map
void	parse_map(t_scene *scene, int fd);

//parse
void	parse_textures(t_mlx *mlx, t_scene *s);
t_scene	*get_scene(const int argc, const char *argv[]);

//set_elements
void	set_res(t_scene *scene, char **data);
void	set_texture(t_scene *scene, char **data, int code);
void	set_color(t_scene *scene, char **data, int code);

//save_bmp
void	save_bmp(const char *filename, const char *data, const t_2int r);

//sprite
void	do_sprite(t_img *img, t_dda *dda, t_scene *s);

//utils
char	*screenshot_datetime(char res[]);
int     ft_tab_size(char **tab);
int     max_len_tab(char **tab);
void	free_tab(void **tab);
void	rotate(t_2float *dir, float angle);

#endif