/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 15:16:18 by hthomas           #+#    #+#             */
/*   Updated: 2020/06/24 15:16:31 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	sprite1(t_dda *dda, t_scene *s, t_calc_sprite *cs, int sprite_order[])
{
	double sprite_x;
	double sprite_y;
	double invdet;
	double transformx;

	sprite_x = dda->sprite[sprite_order[cs->i]].pos.h + 0.5 - s->pos.x;
	sprite_y = dda->sprite[sprite_order[cs->i]].pos.w + 0.5 - s->pos.y;
	invdet = 1.0 / (s->plane.x * s->dir.y - s->dir.x * s->plane.y);
	transformx = invdet * (s->dir.y * sprite_x - s->dir.x * sprite_y);
	cs->transform_y = invdet * (-s->plane.y * sprite_x + s->plane.x * sprite_y);
	cs->spritescrx = (int)((s->res.w / 2) * (1 + transformx / cs->transform_y));
	cs->spriteHeight = abs((int)(s->res.h / (cs->transform_y)));
	cs->drawStartY = -cs->spriteHeight / 2 + s->res.h / 2;
	if (cs->drawStartY < 0)
		cs->drawStartY = 0;
	cs->drawEndY = cs->spriteHeight / 2 + s->res.h / 2;
	if (cs->drawEndY >= s->res.h)
		cs->drawEndY = s->res.h - 1;
	cs->spriteWidth = abs((int)(s->res.h / (cs->transform_y)));
	cs->drawStartX = -cs->spriteWidth / 2 + cs->spritescrx - 1;
	if (cs->drawStartX < 0)
		cs->drawStartX = 0;
	cs->drawEndX = cs->spriteWidth / 2 + cs->spritescrx;
	if (cs->drawEndX >= s->res.w)
		cs->drawEndX = s->res.w - 1;
}

void	sprite2(t_img *img, t_dda *dda, t_scene *s, t_calc_sprite *cs)
{
	cs->stripe = cs->drawStartX;
	while (cs->stripe <= cs->drawEndX)
	{
		cs->texX = (int)(256 * (cs->stripe - (-cs->spriteWidth / 2 +
		cs->spritescrx)) * s->textures[SPRITE]->size.w / cs->spriteWidth) / 256;
		if (cs->texX < 0)
			cs->texX = 0;
		if (cs->transform_y >= 0 && cs->stripe > 0 && cs->stripe < s->res.w &&
		cs->transform_y < dda->perpwalldist[cs->stripe])
		{
			print_sprite(img, dda, s, cs);
		}
		cs->stripe++;
	}
}

void	do_sprite(t_img *img, t_dda *dda, t_scene *s)
{
	int				sprite_order[dda->index_sprite];
	t_calc_sprite	cs;

	get_sprites(dda, s, sprite_order);
	cs.i = 0;
	while (cs.i < dda->index_sprite)
	{
		sprite1(dda, s, &cs, sprite_order);
		sprite2(img, dda, s, &cs);
		cs.i++;
	}
}
