/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 15:20:42 by hthomas           #+#    #+#             */
/*   Updated: 2020/06/24 15:20:57 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_sprite(t_scene *scene, char **map, int line, int col)
{
	scene->map[line][col] = map[line][col];
	scene->nb_sprite++;
}
