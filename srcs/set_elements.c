/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:54:10 by hthomas           #+#    #+#             */
/*   Updated: 2020/07/03 13:20:14 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_res(t_scene *scene, char **data)
{
	int	w;
	int h;

	w = ft_atoi_strict(data[1]);
	h = ft_atoi_strict(data[2]);
	if (w <= 0 || h <= 0)
		print_err_and_exit("res (R) must be 2 positive numbers", 20);
	scene->res.w = w;
	scene->res.h = h;
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
		if (!(scene->floor = str_to_rgb(data[NB_ELEM_COLOR - 1])))
			print_err_and_exit("Color must be 3 values in range 0-255",
			PARSE_ERROR);
	}
	else
	{
		if (!(scene->ceil = str_to_rgb(data[NB_ELEM_COLOR - 1])))
			print_err_and_exit("Color must be 3 values in range 0-255",
			PARSE_ERROR);
	}
}
