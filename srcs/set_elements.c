/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugothms <hugothms@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:54:10 by hthomas           #+#    #+#             */
/*   Updated: 2020/06/04 16:22:38 by hugothms         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		check_resolution(char **data)
{
	return (ft_atoi_strict(data[1]) <= 0 || ft_atoi_strict(data[2]) <= 0);
}

void	set_resolution(t_scene *scene, char **data)
{
	t_couple	*resolution;

	if (check_resolution(data))
		print_err_and_exit("resolution (R) must be 2 positive numbers", 20);
	// if (!(resolution = malloc(sizeof(*resolution))))
	// 	print_err_and_exit("Malloc failed", MALLOC_ERROR);
	resolution->w = ft_atoi_strict(data[1]);
	resolution->h = ft_atoi_strict(data[2]);
	scene->res = *resolution;
}

void	set_texture(t_scene *scene, char **data, int code)
{
	if (!(scene->tex[code] = ft_strdup(data[1])))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
}

void 	set_color(t_scene *scene, char **data, int code)
{
	if (code == 0)
		scene->floor = str_to_rgb(data[NB_ELEM_COLOR - 1]);
	else
		scene->ceil = str_to_rgb(data[NB_ELEM_COLOR - 1]);
}
