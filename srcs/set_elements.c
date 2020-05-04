/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugothms <hugothms@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:54:10 by hthomas           #+#    #+#             */
/*   Updated: 2020/05/04 13:30:36 by hugothms         ###   ########.fr       */
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
	scene->resolution = *resolution;
}

void	set_texture(t_scene *scene, char *data, int code)
{
	if (!(scene->textures[code] = ft_strdup(data)))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
}
