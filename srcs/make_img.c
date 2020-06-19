/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 20:08:47 by hthomas           #+#    #+#             */
/*   Updated: 2020/06/19 17:14:18 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_draw_start_end(t_dda *dda, t_scene *s)
{
	// double	perpWallDist;
	int		drawHeight;

	if (dda->side % 2 == 0)
		dda->perpWallDist[dda->line] = (dda->coord.h - s->pos.x +\
		(1 - dda->step.h) / 2.) / dda->rayDir.x;
	else
		dda->perpWallDist[dda->line] = (dda->coord.w - s->pos.y +\
		(1 - dda->step.w) / 2.) / dda->rayDir.y;
	dda->lineHeight = (s->res.h / dda->perpWallDist[dda->line]);
	if (dda->lineHeight > s->res.h)
		drawHeight = s->res.h;
	else
		drawHeight = dda->lineHeight;
	dda->draw.h = -drawHeight / 2 + s->res.h / 2;
	if (dda->draw.h < 0)
		dda->draw.h = 0;
	dda->draw.w = drawHeight / 2 + s->res.h / 2;
	if (dda->draw.w >= s->res.h)
		dda->draw.w = s->res.h - 1;
}

void	make_img(t_img *img, t_scene *s)
{
	t_dda	*dda;
	t_rgb	*color;

	if(!(dda = malloc(sizeof(*dda))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	dda->line = 0;
	dda->index_sprite = 0;
	while (dda->line < s->res.w)
	{
		calcul_dda(dda, s, dda->line);
		set_side_dist(dda, s);
		perform_dda(s, dda);
		set_draw_start_end(dda, s);
		draw_wall(img->data, dda, s);
		draw_pos_minimap(img, s);
		dda->line++;
	}
	do_sprite(img, dda, s);
	free(dda);
	draw_minimap(img, s);
}
