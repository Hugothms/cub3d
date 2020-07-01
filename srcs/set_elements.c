/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:54:10 by hthomas           #+#    #+#             */
/*   Updated: 2020/07/01 12:33:33 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		check_res(char **data)
{
	return (ft_atoi_strict(data[1]) <= 0 || ft_atoi_strict(data[2]) <= 0);
}

void	set_res(t_scene *scene, char **data)
{
	t_2int	*res;

	if (check_res(data))
		print_err_and_exit("res (R) must be 2 positive numbers", 20);
	res->w = ft_atoi_strict(data[1]);
	res->h = ft_atoi_strict(data[2]);
	scene->res = *res;
}

void	set_texture(t_scene *scene, char **data, int code)
{
	if (!(scene->tex[code] = ft_strdup(data[1])))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
}

void	set_color(t_scene *scene, char **data, int code)
{
	if (code == 0)
	{
		scene->floor = str_to_rgb(data[NB_ELEM_COLOR - 1]);
		if (scene->floor->r < 0 || scene->floor->r > 255 ||
		scene->floor->g < 0 || scene->floor->g > 255 ||
		scene->floor->b < 0 || scene->floor->b > 255)
			print_err_and_exit("Floor RGB value out of range", PARSE_ERROR);
	}
	else
	{
		scene->ceil = str_to_rgb(data[NB_ELEM_COLOR - 1]);
		if (scene->floor->r < 0 || scene->floor->r > 255 ||
		scene->floor->g < 0 || scene->floor->g > 255 ||
		scene->floor->b < 0 || scene->floor->b > 255)
			print_err_and_exit("Ceilling RGB value out of range", PARSE_ERROR);
	}
}
