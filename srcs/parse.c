/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 12:21:27 by hthomas           #+#    #+#             */
/*   Updated: 2020/06/11 14:54:35 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		*init_scene(t_scene *scene)
{
	scene->res.w = -1;
	scene->res.h = -1;
	if (!(scene->tex = malloc(NB_TEXTURES * sizeof(char*))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	scene->tex[NORTH] = NULL;
	scene->tex[SOUTH] = NULL;
	scene->tex[WEST] = NULL;
	scene->tex[EAST] = NULL;
	scene->tex[SPRITE]= NULL;
	scene->floor = NULL;
	scene->ceil = NULL;
	scene->map = NULL;
	scene->size.w = -1;
	scene->size.h = -1;
	scene->pos.x = -1;
	scene->pos.y = -1;
	scene->dir.x = -1;
	scene->dir.y = -1;
	scene->move.left = 0;
	scene->move.right = 0;
	scene->move.down = 0;
	scene->move.up = 0;
	scene->move.turn_left = 0;
	scene->move.turn_right = 0;
	return (scene);
}

int			check_line(char *line, char **data, char *type, int nb_elements)
{
	if (!ft_strcmp(data[0], type))
	{
		if (ft_in_charset(line[ft_strlen(type)], WHITE_SPACES))
			return (ft_tab_size(data) == nb_elements);
	}
	return (0);
}

void	set_all(t_scene *s, char *line)
{
	char	**data;

	data = ft_split_set((*line ? line : "iamcheating"), WHITE_SPACES);
	if (check_line(line, data, "R", NB_ELEM_res) && s->res.w == -1)
		set_res(s, data);
	else if (check_line(line, data, "NO", NB_ELEM_TEX) && !s->tex[NORTH])
		set_texture(s, data, NORTH);
	else if (check_line(line, data, "SO", NB_ELEM_TEX) && !s->tex[SOUTH])
		set_texture(s, data, SOUTH);
	else if (check_line(line, data, "WE", NB_ELEM_TEX) && !s->tex[WEST])
		set_texture(s, data, WEST);
	else if (check_line(line, data, "EA", NB_ELEM_TEX) && !s->tex[EAST])
		set_texture(s, data, EAST);
	else if (check_line(line, data, "S", NB_ELEM_TEX) && !s->tex[SPRITE])
		set_texture(s, data, SPRITE);
	else if (check_line(line, data, "F", NB_ELEM_COLOR) && !s->floor)
		set_color(s, data, 0);
	else if (check_line(line, data, "C", NB_ELEM_COLOR) && !s->ceil)
		set_color(s, data, 1);
	else if (ft_strcmp(data[0], "iamcheating"))
		print_err_and_exit("Parsing invalid line", PARSE_ERROR);
	free(line);
	free_tab((void**)data);
}

void		parse_textures(t_mlx *mlx, t_scene *s)
{
	int	i;

	i = 0;
	while (i < NB_TEXTURES)
	{
		//printf("A%p\n", s->textures[i]->img_ptr);
		if(!(s->textures[i] = malloc(sizeof(t_img))))
			print_err_and_exit("Malloc failed", MALLOC_ERROR);
		s->textures[i]->size.w = 64;
		s->textures[i]->size.h = 64;
		// printf("img: %p\n", s->textures[i]->img_ptr);
		// printf("mlx: %p\n", mlx->mlx_ptr);
		// printf("tex: %s\n", s->tex[i]);
		// printf("siz: %d\n\n", s->textures[i]->size.w);
		printf("\npourquoi la ligne suivante affiche un pointeur null ?\n");
		printf("mlx_xpm_file_to_image(%p, %s, %d, %d) = %p\n", mlx->mlx_ptr,\
		s->tex[i], s->textures[i]->size.w, s->textures[i]->size.h, mlx_xpm_file_to_image(mlx->mlx_ptr, s->tex[i],\
		&(s->textures[i]->size.w), &(s->textures[i]->size.h)));
		if(!(s->textures[i]->img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr,\
		s->tex[i], &(s->textures[i]->size.w), &(s->textures[i]->size.h))))
			print_err_and_exit("Minilibx error", MLX_ERROR);
		if(!(s->textures[i]->data = mlx_get_data_addr(s->textures[i]->img_ptr,\
		&s->textures[i]->bits_per_pixel, &s->textures[i]->size_line,\
		&s->textures[i]->endian)))
			print_err_and_exit("Minilibx error", MLX_ERROR);
		printf("E%p\n", s->textures[i]->img_ptr);
		i++;
	}
}

t_scene		*parse(int fd)
{
	t_scene	*s;
	char	*line;
	int		ret;

	if (!(s = malloc(sizeof(*s))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	if (!(init_scene(s)))
		return (NULL);
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		// ft_putstr(line);
		// ft_putchar('\n');
		set_all(s, line);
		if (s->res.w != -1 && s->tex[NORTH] && s->tex[SOUTH] && s->tex[WEST]\
		&& s->tex[EAST] && s->tex[SPRITE] && s->floor && s->ceil)
			break;
	}
	parse_map(s, fd);
	// int i = 0;
	// while (i < scene->size.h)
	// {
	// 	ft_putstr(scene->map[i++]);
	// 	ft_putchar('\n');
	// }
	return (s);
}

t_scene		*get_scene(const int argc, const char *argv[])
{
	int			fd;
	t_scene		*scene;

	if (argc < 2 || argc > 3)
		print_err_and_exit("Wrong number of argument", 1);
	if (argc == 2 && ft_strncmp_rev(argv[1], ".cub", 4))
		print_err_and_exit("First argument must be a '.cub' file", 1);
	if (argc == 3 && ft_strcmp(argv[2], "-save"))
		print_err_and_exit("Second argument must be '-save'", 1);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		print_err_and_exit(strerror(errno), errno);
	if (!(scene = parse(fd)))
		print_err_and_exit("Parsing error", PARSE_ERROR);
	if (close(fd) == -1)
		print_err_and_exit(strerror(errno), errno);
	return (scene);
}
