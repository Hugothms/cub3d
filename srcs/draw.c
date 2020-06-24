/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 18:45:38 by hthomas           #+#    #+#             */
/*   Updated: 2020/06/24 14:10:06 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_pixel(char *data, t_2int pixel, int color, t_2int res)
{
	int	(*tab)[res.w][1];

	tab = (void *)data;
	*tab[pixel.h][pixel.w] = color;
}

void	put_texture(char *data, t_2int pixel, char *texdata, t_2int res, 
int entier)
{
	int	(*tab);
	int	(*tabtexture);

	tab = (void *)data;
	tabtexture = (void *)texdata;
	tab[pixel.h * res.w + pixel.w] = tabtexture[entier];
}

void	put_sprite(char *data, t_2int pixel, char *texdata, t_2int res,
int entier)
{
	int	(*tab);
	int	(*tabtexture);

	tab = (void *)data;
	tabtexture = (void *)texdata;
	if ((tabtexture[entier] & 0x00FFFFFF) != 0)
		tab[pixel.h * res.w + pixel.w] = tabtexture[entier];
}

void	draw_v_line(char *data, t_2int pos, int length, int color, t_2int res)
{
	while (length-- > 0)
	{
		put_pixel(data, pos, color, res);
		pos.h++;
	}
}

void	draw_texture_line(char *data, t_2int pos, t_dda *dda, t_scene *s)
{
	int		length;
	float	step;
	t_2int	tex_size = s->textures[dda->side]->size;
	double	wallx;
	int		texx;
	float	texpos;
	int		texy;

	if (dda->side % 2 == 0)
		wallx = s->pos.y + dda->perpwalldist[dda->line] * dda->rayDir.y;
	else
		wallx = s->pos.x + dda->perpwalldist[dda->line] * dda->rayDir.x;
	wallx -= floor(wallx);
	texx = wallx * (double)tex_size.w;
	if (dda->side % 2 == 0 && dda->rayDir.x > 0)
		texx = tex_size.w - texx - 1;
	if (dda->side % 2 == 1 && dda->rayDir.y < 0)
		texx = tex_size.w - texx - 1;
	step = (float)tex_size.h / dda->lineHeight;
	texpos = (dda->draw.h - s->res.h / 2 + dda->lineHeight / 2) * step;
	length = (dda->lineHeight < s->res.h ? dda->lineHeight : s->res.h);
	while (length-- > 0)
	{
		texy = (int)texpos & (tex_size.h - 1);
		texpos += step;
		put_texture(data, pos, s->textures[dda->side]->data, s->res,
		tex_size.w * texy + texx);
		// data[4 * (pos.h * s->res.w + pos.w)] = s->textures[dda->side]->data[4 * (tex_size.w * texy + texx)];
		// data[4 * (pos.h * s->res.w + pos.w) + 1] = s->textures[dda->side]->data[4 * (tex_size.w * texy + texx) + 1];
		// data[4 * (pos.h * s->res.w + pos.w) + 2] = s->textures[dda->side]->data[4 * (tex_size.w * texy + texx) + 2];
		// data[4 * (pos.h * s->res.w + pos.w) + 3] = s->textures[dda->side]->data[4 * (tex_size.w * texy + texx) + 3];
		pos.h++;
	}
}

void	draw_wall(char *data, t_dda *dda, t_scene *s)
{
	int		i;
	t_2int	pixel;

	pixel.w = s->res.w - dda->line - 1;
	pixel.h = 0;
	draw_v_line(data, pixel, dda->draw.h, CEILING_COLOR, s->res);
	pixel.h += dda->draw.h;
	draw_texture_line(data, pixel, dda, s);
		pixel.h += dda->draw.w - dda->draw.h;
	draw_v_line(data, pixel, s->res.h - dda->draw.w, FLOOR_COLOR, s->res);
}
