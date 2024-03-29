/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 00:15:27 by hthomas           #+#    #+#             */
/*   Updated: 2022/03/13 19:04:46 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_initial_dir(t_2float *dir, char **map, int line, int col)
{
	if (map[line][col] == 'E')
	{
		dir->x = 0;
		dir->y = -1;
	}
	else if (map[line][col] == 'W')
	{
		dir->x = 0;
		dir->y = 1;
	}
	else if (map[line][col] == 'S')
	{
		dir->x = 1;
		dir->y = 0;
	}
	else if (map[line][col] == 'N')
	{
		dir->x = -1;
		dir->y = 0;
	}
}

void	set_initial_pos(t_scene *scene, char **map, int line, int col)
{
	scene->map[line][col] = '0';
	scene->pos.x = line + 0.5;
	scene->pos.y = col + 0.5;
	set_initial_dir(&scene->dir, map, line, col);
	scene->plane.x = scene->dir.x * FOV;
	scene->plane.y = scene->dir.y * FOV;
	rotate(&scene->plane, 1.570796);
}

int		get_map2(t_scene *scene, char **map, int line)
{
	int	col;

	if (!(scene->map[line] = malloc((scene->size.w + 1) * sizeof(char))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	ft_memset(scene->map[line], '8', scene->size.w);
	scene->map[line][scene->size.w] = '\0';
	col = 0;
	while (map[line][col])
	{
		if (map[line][col] == '1')
			scene->map[line][col] = map[line][col];
		else if (map[line][col] == '2')
			set_sprite(scene, map, line, col);
		else if (map[line][col] == '0')
			scene->map[line][col] = '8';
		else if (map[line][col] == ' ')
			scene->map[line][col] = ' ';
		else if (ft_in_charset(map[line][col], "NSEW") && scene->pos.x == -1)
			set_initial_pos(scene, map, line, col);
		else
			print_err_and_exit("Bad map format", PARSE_ERROR);
		col++;
	}
	return (col == 0);
}

void	get_map(t_scene *scene, char *join)
{
	int		line;
	int		col;
	char	**map;

	map = ft_split(join, '\n');
	free(join);
	scene->size.h = ft_tab_size(map);
	scene->size.w = max_len_tab(map);
	if (!(scene->map = malloc(scene->size.h * sizeof(char*))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	line = 0;
	while (line < scene->size.h)
	{
		if (get_map2(scene, map, line))
			break ;
		line++;
	}
	if (scene->pos.x == -1)
		print_err_and_exit("Initial position missing", PARSE_ERROR);
	free_tab((void**)map);
}

void	parse_map(t_scene *scene, int fd)
{
	char	*line;
	char	*join;
	char	*tmp;
	int		ret;

	skip_empty_lines(fd, &line);
	tmp = line;
	join = ft_strdup(line);
	free(tmp);
	join_clean(&join, "\n");
	ret = 1;
	while (ret == 1)
	{
		ret = get_next_line(&line, fd);
		if (!line[0])
		{
			free(line);
			break ;
		}
		join_clean(&join, line);
		join_clean(&join, "\n");
		free(line);
	}
	get_map(scene, join);
	check_map(scene->map, scene->pos, scene->size);
}
