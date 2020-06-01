/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugothms <hugothms@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 12:21:27 by hthomas           #+#    #+#             */
/*   Updated: 2020/06/01 11:39:50 by hugothms         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		*init_scene(t_scene *scene)
{
	scene->resolution.w = -1;
	scene->resolution.h = -1;
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

int			get_map(t_scene *scene, char*join)
{
	int 	line;
	int		col;
	char	**map;
	
	map = ft_split(join, '\n'); //echanger map et scene->map
	free(join);
	line = 0;
	scene->size.h = ft_tab_size(map);
	scene->size.w = max_len_tab(map);
	if (!(scene->map = malloc(scene->size.h * sizeof(char*))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	while (line < scene->size.h)
	{
		if (!(scene->map[line] = malloc((ft_strlen(map[line]) + 1) * sizeof(char))))
			print_err_and_exit("Malloc failed", MALLOC_ERROR);
		scene->map[line][ft_strlen(map[line])] = '\0';
		col = 0;
		while (map[line][col])
		{
			if (ft_in_charset(map[line][col], "012"))
				scene->map[line][col] = map[line][col];
			else if (map[line][col] == ' ')
				scene->map[line][col] = '0';
			else if (ft_in_charset(map[line][col], "NSEW") && scene->pos.x == -1)
			{
				scene->map[line][col] = '0';
				scene->pos.x = line;
				scene->pos.y = col;
				if (map[line][col] == 'N')
				{
					scene->dir.x = 0;
					scene->dir.y = -1;
				}
				else if (map[line][col] == 'S')
				{
					scene->dir.x = 0;
					scene->dir.y = 1;
				}
				else if (map[line][col] == 'E')
				{
					scene->dir.x = 1;
					scene->dir.y = 0;
				}
				else if (map[line][col] == 'W')
				{
					scene->dir.x = -1;
					scene->dir.y = 0;
				}
				scene->plane.x = scene->dir.x * FOV;
				scene->plane.y = scene->dir.y * FOV;
				rotation(&scene->plane, 1.570796);
			}
			else
				print_err_and_exit("Bad map format", PARSE_ERROR);
			col++;
		}
		line++;
	}
	free_tab((void**)map);
}

void		parse_map(t_scene *scene, int fd)
{
	char	*line;
	char	*join;
	char	*tmp;
	int		i;
	int		col;

	while (get_next_line(fd, &line) == 1)
	{
		if (line[0])
			break;
		free(line);
	}
	tmp = line;
	join = ft_strdup(line);
	free(tmp);
	tmp = join;
	join = ft_strjoin(join, "\n");
	free(tmp);
	while (get_next_line(fd, &line) == 1)
	{
		tmp = join;
		join = ft_strjoin(join, line);
		free(tmp);
		tmp = join;
		join = ft_strjoin(join, "\n");
		free(tmp);
		free(line);
	}
	free(line);
	// ft_putstr("join\n");
	// ft_putstr(join);
	get_map(scene, join);
	//check_map(scene->map);
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
		if (check_line(line, data, "R", NB_ELEM_RESOLUTION) && scene->resolution.w == -1)
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
		free_tab((void**)data);
		if (scene->resolution.w && scene->textures[NORTH] && scene->textures[SOUTH] && scene->textures[WEST] && scene->textures[EAST] && scene->textures[SPRITE] && scene->floor_color && scene->ceilling_color)
			break;
	}
	parse_map(scene, fd);
	int i = 0;
	while(i < scene->size.h)
	{
		ft_putstr(scene->map[i++]);
		ft_putchar('\n');
	}
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
