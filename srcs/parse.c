/* ************************************************************************** */
/*	*/
/*	:::	  ::::::::   */
/*   parse.c	:+:	  :+:	:+:   */
/*	+:+ +:+	 +:+	 */
/*   By: hugothms <hugothms@student.42.fr>	  +#+  +:+	   +#+	*/
/*	+#+#+#+#+#+   +#+	   */
/*   Created: 2020/01/09 12:21:27 by hthomas	   #+#	#+#	 */
/*   Updated: 2020/06/04 16:16:55 by hugothms	 ###   ########.fr	   */
/*	*/
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

void print_map_color(char **map, t_couple couple, t_couple size)
{
	printf("couple%d:%d\n", couple.h, couple.w);
	int i = 0;
	int j;
	while (i < size.h)
	{
		j=0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				printf("\033[48;5;39m");
				printf("%c", map[i][j]);
				printf("\033[m"); 
			}
			else if (map[i][j] == '8')
			{
				printf("\033[48;5;213m");
				printf("%c", map[i][j]);
				printf("\033[m"); 
			}
			else
				printf("%c", map[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}
	sleep(1);
}

int		recurs_map(char **map, t_couple couple, t_couple size)
{
	int ok[4];
	
	ok[0] = 1;
	ok[1] = 1;
	ok[2] = 1;
	ok[3] = 1;
	//print_map_color(map, couple, size);
	map[couple.h][couple.w] = '0';
	if (!couple.h || !couple.w || couple.h == size.h - 1 || couple.w == size.w - 1)
		return (0);
	couple.h -= 1;
	if (map[couple.h][couple.w] == '8')
		ok[0] = recurs_map(map, couple, size);
	couple.h += 1;
	couple.w -= 1;
	if (map[couple.h][couple.w] == '8')
		ok[1] = recurs_map(map, couple, size);
	couple.w += 1;
	couple.h += 1;
	if (map[couple.h][couple.w] == '8')
		ok[2] = recurs_map(map, couple, size);
	couple.h -= 1;
	couple.w += 1;
	if (map[couple.h][couple.w] == '8')
		ok[3] = recurs_map(map, couple, size);
	return (ok[0] && ok[1] && ok[2] && ok[3]);
}

void		check_map(char **map, t_pos pos, t_couple size)
{
	t_couple	couple;
	
	couple.h = (int)pos.x;
	couple.w = (int)pos.y;
	if (!recurs_map(map, couple, size))
		print_err_and_exit("Map not closed", PARSE_ERROR);
}

int			get_map(t_scene *scene, char *join)
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
		if (!(scene->map[line] = malloc((scene->size.w + 1) * sizeof(char))))
			print_err_and_exit("Malloc failed", MALLOC_ERROR);
		ft_memset(scene->map[line], '8', scene->size.w);
		scene->map[line][scene->size.w] = '\0';
		col = 0;
		while (map[line][col])
		{
			if (ft_in_charset(map[line][col], "12"))
				scene->map[line][col] = map[line][col];
			else if (map[line][col] == '0')
				scene->map[line][col] = '8';
			else if (map[line][col] == ' ')
				scene->map[line][col] = '8';
			else if (ft_in_charset(map[line][col], "NSEW") && scene->pos.x == -1)
			{
				scene->map[line][col] = '0';
				scene->pos.x = line + 0.5;
				scene->pos.y = col + 0.5;
				if (map[line][col] == 'E')
				{
					scene->dir.x = 0;
					scene->dir.y = -1;
				}
				else if (map[line][col] == 'W')
				{
					scene->dir.x = 0;
					scene->dir.y = 1;
				}
				else if (map[line][col] == 'S')
				{
					scene->dir.x = 1;
					scene->dir.y = 0;
				}
				else if (map[line][col] == 'N')
				{
					scene->dir.x = -1;
					scene->dir.y = 0;
				}
				scene->plane.x = scene->dir.x * FOV;
				scene->plane.y = scene->dir.y * FOV;
				rotate(&scene->plane, 1.570796);
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
	int		ret;
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
	ret = 1;
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		tmp = join;
		join = ft_strjoin(join, line);
		free(tmp);
		tmp = join;
		join = ft_strjoin(join, "\n");
		free(tmp);
		free(line);
	}
	get_map(scene, join);
	check_map(scene->map, scene->pos, scene->size);
}

void	set_all(t_scene *s, char *line)
{
	char	**data;

	data = ft_split_set((*line ? line : "iamcheating"), WHITE_SPACES);
	if (check_line(line, data, "R", NB_ELEM_RESOLUTION) && s->res.w == -1)
		set_resolution(s, data);
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
		if(!(s->textures[i] = malloc(sizeof(t_texture))))
			print_err_and_exit("Malloc failed", MALLOC_ERROR);
		printf("Z%p\n", s->textures[i]->img_ptr);
		s->textures[i]->img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, s->tex[i], &(s->textures[i]->size.w), &(s->textures[i]->size.h));
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
		if (s->res.w != -1 && s->tex[NORTH] && s->tex[SOUTH] && s->tex[WEST] && s->tex[EAST] && s->tex[SPRITE] && s->floor && s->ceil)
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
