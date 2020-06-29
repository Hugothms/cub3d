/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 15:20:42 by hthomas           #+#    #+#             */
/*   Updated: 2020/06/29 13:55:10 by hthomas          ###   ########.fr       */
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

void	init_scene(t_scene *scene)
{
	scene->res.w = -1;
	scene->res.h = -1;
	if (!(scene->tex = malloc(sizeof(char*) * NB_TEXTURES)))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	scene->tex[NORTH] = NULL;
	scene->tex[SOUTH] = NULL;
	scene->tex[WEST] = NULL;
	scene->tex[EAST] = NULL;
	scene->tex[SPRITE] = NULL;
	scene->floor = NULL;
	scene->ceil = NULL;
	scene->map = NULL;
	scene->size.w = -1;
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
	scene->nb_sprite = 0;
}
