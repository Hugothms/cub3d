/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugothms <hugothms@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 20:08:47 by hugothms          #+#    #+#             */
/*   Updated: 2020/05/15 20:18:48 by hugothms         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	make_img(t_img *img, t_scene *scene)
{
	int x;

	x = 0;
	while (x < scene->resolution.w)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)scene->resolution.w - 1; //x-coordinate in camera space
		double rayDirX = scene->dir.x + scene->plane.x * cameraX;
		double rayDirY = scene->dir.y + scene->plane.y * cameraX;



		
		x++;
	}
}