/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 19:20:51 by hthomas           #+#    #+#             */
/*   Updated: 2020/06/20 15:28:01 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	calcul_dda(t_dda *dda, t_scene *s, int x)
{
	double	cameraX;

	cameraX = 2 * x / (double)s->res.w - 1;
	dda->rayDir.x = s->dir.x + s->plane.x * cameraX;
	dda->rayDir.y = s->dir.y + s->plane.y * cameraX;
	dda->coord.h = (int)s->pos.x;
	dda->coord.w = (int)s->pos.y;
	dda->deltaDist.x = fabs(1 / dda->rayDir.x);
	dda->deltaDist.y = fabs(1 / dda->rayDir.y);
}

void	set_side_dist(t_dda *dda, t_scene *s)
{
	if (dda->rayDir.x < 0)
	{
		dda->step.h = -1;
		dda->sideDist.x = (s->pos.x - dda->coord.h) * dda->deltaDist.x;
	}
	else
	{
		dda->step.h = 1;
		dda->sideDist.x = (dda->coord.h + 1.0 - s->pos.x) * dda->deltaDist.x;
	}
	if (dda->rayDir.y < 0)
	{
		dda->step.w = -1;
		dda->sideDist.y = (s->pos.y - dda->coord.w) * dda->deltaDist.y;
	}
	else
	{
		dda->step.w = 1;
		dda->sideDist.y = (dda->coord.w + 1.0 - s->pos.y) * dda->deltaDist.y;
	}
}

int		deja_vu(t_dda *dda)
{
	int i;

	i = 0;
	while (i < dda->index_sprite)
	{
		// printf("same sprite ? %d:%d\n", dda->coord.h, dda->coord.w);
		// printf("than sprite%d %d:%d\n\n", i, dda->sprite[i].pos.h, dda->sprite[i].pos.w);
		if (dda->sprite[i].pos.h == dda->coord.h &&	dda->sprite[i].pos.w == dda->coord.w)
			return (1);
		i++;
	}
	return (0);
}

int		set_sprites_dda(t_scene *s, t_dda *dda)
{
	if (s->map[dda->coord.h][dda->coord.w] == '1')
		return (1);
	else if (!deja_vu(dda))
	{
		// printf("dda->index_sprite:%d\n", dda->index_sprite);
		dda->sprite[dda->index_sprite].pos.h = dda->coord.h;
		dda->sprite[dda->index_sprite].pos.w = dda->coord.w;
		printf("sprite trouve:%d:%d\n", dda->coord.h, dda->coord.w);
		dda->index_sprite++;
		printf("index_sprite = %d\n", dda->index_sprite);
		return (0);
	}
	return (0);
}

void	perform_dda(t_scene *s, t_dda *dda)
{
	int	hit; //was there a wall hit?

	hit = 0;
	while (hit == 0)
	{
		//jump to next map square, OR in x-direction, OR in y-direction
		if (dda->sideDist.x < dda->sideDist.y)
		{
			dda->sideDist.x += dda->deltaDist.x;
			dda->coord.h += dda->step.h;
			dda->side = ((dda->rayDir.x > 0) ? 0 : 2);
		}
		else
		{
			dda->sideDist.y += dda->deltaDist.y;
			dda->coord.w += dda->step.w;
			dda->side = ((dda->rayDir.y > 0) ? 1 : 3);
		}
		//printf("map%d:%d\n", dda->coord.h, dda->coord.w);
		if (s->map[dda->coord.h][dda->coord.w] != '0')
			hit = set_sprites_dda(s, dda);
	}
}