/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 15:52:54 by hthomas           #+#    #+#             */
/*   Updated: 2020/06/24 15:16:08 by hthomas          ###   ########.fr       */
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
