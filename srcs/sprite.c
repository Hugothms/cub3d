/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 15:52:54 by hthomas           #+#    #+#             */
/*   Updated: 2020/06/24 13:14:14 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_swap_double(double *a, double *b)
{
	double c;

	c = *a;
	*a = *b;
	*b = c;
}

void	ft_swap_sprite(t_sprite *a, t_sprite *b)
{
	t_sprite c;

	c = *a;
	*a = *b;
	*b = c;
}

void	sort_sprites(int spriteOrder[], double spriteDistance[], t_dda *dda)
{
	int swap;
	int i;

	i = 0;
	swap = 1;
	while (swap)
	{
		i = 0;
		swap = 0;
		while (i < dda->index_sprite - 1)
		{
			if (spriteDistance[i] < spriteDistance[i + 1])
			{
				ft_swap_double(&spriteDistance[i], &spriteDistance[i + 1]);
				ft_swap(&spriteOrder[i], &spriteOrder[i + 1]);
				ft_swap_sprite(&dda->sprite[i], &dda->sprite[i + 1]);
				swap = 1;
			}
			i++;
		}
	}
}

void	sprite1(t_dda *dda, t_scene *s, t_calc_sprite* cs, int spriteOrder[])
{
	double spriteX;
	double spriteY;
	double invDet;
	double transformX;

	spriteX = dda->sprite[spriteOrder[cs->i]].pos.h + 0.5 - s->pos.x;
	spriteY = dda->sprite[spriteOrder[cs->i]].pos.w + 0.5 - s->pos.y;
	invDet = 1.0 / (s->plane.x * s->dir.y - s->dir.x * s->plane.y);
	transformX = invDet * (s->dir.y * spriteX - s->dir.x * spriteY);
	cs->transformY = invDet * (-s->plane.y * spriteX + s->plane.x * spriteY);
	cs->spriteScrX = (int)((s->res.w / 2) * (1 + transformX / cs->transformY));
	cs->spriteHeight = abs((int)(s->res.h / (cs->transformY)));
	cs->drawStartY = -cs->spriteHeight / 2 + s->res.h / 2;
	if (cs->drawStartY < 0)
		cs->drawStartY = 0;
	cs->drawEndY = cs->spriteHeight / 2 + s->res.h / 2;
	if (cs->drawEndY >= s->res.h)
		cs->drawEndY = s->res.h - 1;
	cs->spriteWidth = abs((int)(s->res.h / (cs->transformY)));
	cs->drawStartX = -cs->spriteWidth / 2 + cs->spriteScrX - 1;
	if (cs->drawStartX < 0)
		cs->drawStartX = 0;
	cs->drawEndX = cs->spriteWidth / 2 + cs->spriteScrX;
	if (cs->drawEndX >= s->res.w)
		cs->drawEndX = s->res.w - 1;		
}

void get_sprites(t_dda *dda, t_scene *s, int spriteOrder[])
{
	double			spriteDistance[dda->index_sprite];

	for(int i = 0; i < dda->index_sprite; i++)
	{
		spriteOrder[i] = i;
		spriteDistance[i] = ((s->pos.x - dda->sprite[i].pos.h) * 
		(s->pos.x - dda->sprite[i].pos.h) + (s->pos.y - dda->sprite[i].pos.w) *
		(s->pos.y - dda->sprite[i].pos.w));
	}
	sort_sprites(spriteOrder, spriteDistance, dda);
}

void	do_sprite(t_img *img, t_dda *dda, t_scene *s)
{
	int				spriteOrder[dda->index_sprite];
	t_calc_sprite	cs;
	
	get_sprites(dda, s, spriteOrder);
	cs.i = 0;
	while (cs.i < dda->index_sprite)
	{
		sprite1(dda, s, &cs, spriteOrder);
		for (int stripe = cs.drawStartX; stripe <= cs.drawEndX; stripe++)
		{
			int texX = (int)(256 * (stripe - (-cs.spriteWidth / 2 + cs.spriteScrX)) * s->textures[SPRITE]->size.w / cs.spriteWidth) / 256;
			if (texX < 0)
				texX = 0;
			if (cs.transformY >= 0 && stripe > 0 && stripe < s->res.w && cs.transformY < dda->perpWallDist[stripe])
			{
				for (int y = cs.drawStartY; y <= cs.drawEndY; y++)
				{
					int d = (y)*256 - s->res.h * 128 + cs.spriteHeight * 128;
					int texY = ((d * s->textures[SPRITE]->size.h) / cs.spriteHeight) / 256;
					int color = s->textures[SPRITE]->data[s->textures[SPRITE]->size.w * texY + texX];
					t_2int pixel;
					pixel.w = s->res.w - stripe - 1;
					pixel.h = y;
					put_sprite(img->data, pixel, s->textures[SPRITE]->data, s->res, s->textures[SPRITE]->size.w * texY + texX);
				}
			}
		}
		cs.i++;
	}
}
