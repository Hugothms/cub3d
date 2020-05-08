/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugothms <hugothms@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 12:21:27 by hthomas           #+#    #+#             */
/*   Updated: 2020/05/09 00:08:11 by hugothms         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		*init_scene(t_scene *scene)
{
	scene->resolution.w = 0;
	scene->resolution.h = 0;
	if (!(scene->textures = malloc(NB_TEXTURES * sizeof(char*))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	scene->textures[NORTH] = NULL;
	scene->textures[SOUTH] = NULL;
	scene->textures[WEST] = NULL;
	scene->textures[EAST] = NULL;
	scene->textures[SPRITE]= NULL;
	scene->floor_color = NULL;
	scene->ceilling_color = NULL;
	scene->map = NULL;
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

t_scene		*parse(int fd)
{
	t_scene	*scene;
	char	*line;
	int		ret;
	char	**data;

	if (!(scene = malloc(sizeof(*scene))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	if (!(init_scene(scene)))
		return (NULL);
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		ft_putstr(line);
		data = ft_split_set((*line ? line : "iamcheating"), WHITE_SPACES);
		ft_putchar('\n');
		if (check_line(line, data, "R", NB_ELEM_RESOLUTION) && !scene->resolution.w)
			set_resolution(scene, data);
		else if (check_line(line, data, "NO", NB_ELEM_TEXTURE) && !scene->textures[NORTH])
			set_texture(scene, data, NORTH);
		else if (check_line(line, data, "SO", NB_ELEM_TEXTURE) && !scene->textures[SOUTH])
			set_texture(scene, data, SOUTH);
		else if (check_line(line, data, "WE", NB_ELEM_TEXTURE) && !scene->textures[WEST])
			set_texture(scene, data, WEST);
		else if (check_line(line, data, "EA", NB_ELEM_TEXTURE) && !scene->textures[EAST])
			set_texture(scene, data, EAST);
		else if (check_line(line, data, "S", NB_ELEM_TEXTURE) && !scene->textures[SPRITE])
			set_texture(scene, data, SPRITE);
		else if (check_line(line, data, "F", NB_ELEM_COLOR) && !scene->floor_color)
			set_color(scene, data, 0);
		else if (check_line(line, data, "C", NB_ELEM_COLOR) && !scene->ceilling_color)
			set_color(scene, data, 1);
		free(line);
		free_tab(data);
		if (scene->resolution.w && scene->textures[NORTH] && scene->textures[SOUTH] && scene->textures[WEST] && scene->textures[EAST] && scene->textures[SPRITE] && scene->floor_color && scene->ceilling_color)
			break;
	}
	//parse_map(); 
	return (scene);
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
