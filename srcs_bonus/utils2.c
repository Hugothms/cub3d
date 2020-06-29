/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 15:20:42 by hthomas           #+#    #+#             */
/*   Updated: 2020/06/29 11:45:57 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_sprite(t_scene *scene, char **map, int line, int col)
{
	scene->map[line][col] = map[line][col];
	scene->nb_sprite++;
}

t_rgb	*mult_rgb_float(t_rgb rgb, float mult)
{
	return (int_to_rgb(rgb.r * mult, rgb.g * mult, rgb.b * mult));
}

void	min_rgb(t_rgb *color)
{
	color->r = ft_min_int(color->r, 255);
	color->g = ft_min_int(color->g, 255);
	color->b = ft_min_int(color->b, 255);
}
