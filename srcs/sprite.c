/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 15:52:54 by hthomas           #+#    #+#             */
/*   Updated: 2020/06/24 00:44:01 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
				ft_swap(&spriteDistance[i], &spriteDistance[i + 1]);
				ft_swap(&spriteOrder[i], &spriteOrder[i + 1]);
				ft_swap(&dda->sprite[i], &dda->sprite[i + 1]);
				swap = 1;
			}
			i++;
		}
	}
}

void	do_sprite(t_img *img, t_dda *dda, t_scene *s)
{
	int spriteOrder[dda->index_sprite];
	double spriteDistance[dda->index_sprite];

	for(int i = 0; i < dda->index_sprite; i++)
	{
		spriteOrder[i] = i;
		spriteDistance[i] = ((s->pos.x - dda->sprite[i].pos.h) * (s->pos.x - dda->sprite[i].pos.h) + (s->pos.y - dda->sprite[i].pos.w) * (s->pos.y - dda->sprite[i].pos.w));
	}
	sort_sprites(spriteOrder, spriteDistance, dda);
	for (int i = 0; i < dda->index_sprite; i++)
	{
		double spriteX = dda->sprite[spriteOrder[i]].pos.h + 0.5 - s->pos.x;
		double spriteY = dda->sprite[spriteOrder[i]].pos.w + 0.5 - s->pos.y;
		double invDet = 1.0 / (s->plane.x * s->dir.y - s->dir.x * s->plane.y);
		double transformX = invDet * (s->dir.y * spriteX - s->dir.x * spriteY);
		double transformY = invDet * (-s->plane.y * spriteX + s->plane.x * spriteY);
		int spriteScreenX = (int)((s->res.w / 2) * (1 + transformX / transformY));
		int spriteHeight = abs((int)(s->res.h / (transformY)));
		int drawStartY = -spriteHeight / 2 + s->res.h / 2;
		if (drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + s->res.h / 2;
		if (drawEndY >= s->res.h)
			drawEndY = s->res.h - 1;
			int spriteWidth = abs((int)(s->res.h / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX - 1;
		if (drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= s->res.w)
			drawEndX = s->res.w - 1;
		for (int stripe = drawStartX; stripe <= drawEndX; stripe++)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * s->textures[SPRITE]->size.w / spriteWidth) / 256;
			if (texX < 0)
				texX = 0;
			if (transformY >= 0 && stripe > 0 && stripe < s->res.w && transformY < dda->perpWallDist[stripe])
			{
				for (int y = drawStartY; y <= drawEndY; y++)
				{
					int d = (y)*256 - s->res.h * 128 + spriteHeight * 128;
					int texY = ((d * s->textures[SPRITE]->size.h) / spriteHeight) / 256;
					int color = s->textures[SPRITE]->data[s->textures[SPRITE]->size.w * texY + texX];
					t_2int pixel;
					pixel.w = s->res.w - stripe - 1;
					pixel.h = y;
					put_sprite(img->data, pixel, s->textures[SPRITE]->data, s->res, s->textures[SPRITE]->size.w * texY + texX);
				}
			}
		}
	}
}
