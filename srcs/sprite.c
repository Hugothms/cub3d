/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 15:52:54 by hthomas           #+#    #+#             */
/*   Updated: 2020/06/24 14:09:16 by hthomas          ###   ########.fr       */
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

void	print_sprite(t_img *img, t_dda *dda, t_scene *s, t_calc_sprite *cs)
{
	int	y;
	int	d;
	int	texy;
	int	color;

	y = cs->drawStartY;
	while (y <= cs->drawEndY)
	{
		d = (y) * 256 - s->res.h * 128 + cs->spriteHeight * 128;
		texy = ((d * s->textures[SPRITE]->size.h) / cs->spriteHeight) / 256;
		color = s->textures[SPRITE]->data[s->textures[SPRITE]->size.w *
		texy + cs->texX];
		t_2int pixel;
		pixel.w = s->res.w - cs->stripe - 1;
		pixel.h = y;
		put_sprite(img->data, pixel, s->textures[SPRITE]->data, s->res,
		s->textures[SPRITE]->size.w * texy + cs->texX);
		y++;
	}
}

void	sort_sprites(int sprite_order[], double sprite_distance[], t_dda *dda)
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
			if (sprite_distance[i] < sprite_distance[i + 1])
			{
				ft_swap_double(&sprite_distance[i], &sprite_distance[i + 1]);
				ft_swap(&sprite_order[i], &sprite_order[i + 1]);
				ft_swap_sprite(&dda->sprite[i], &dda->sprite[i + 1]);
				swap = 1;
			}
			i++;
		}
	}
}

void	get_sprites(t_dda *dda, t_scene *s, int sprite_order[])
{
	double	sprite_distance[dda->index_sprite];
	int		i;

	i = 0;
	while (i < dda->index_sprite)
	{
		sprite_order[i] = i;
		sprite_distance[i] = ((s->pos.x - dda->sprite[i].pos.h) *
		(s->pos.x - dda->sprite[i].pos.h) + (s->pos.y - dda->sprite[i].pos.w) *
		(s->pos.y - dda->sprite[i].pos.w));
		i++;
	}
	sort_sprites(sprite_order, sprite_distance, dda);
}

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
