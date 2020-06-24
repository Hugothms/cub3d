/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 18:45:38 by hthomas           #+#    #+#             */
/*   Updated: 2020/06/24 14:51:30 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_v_line(char *data, t_draw draw, int color, t_2int res)
{
	while (draw.length-- > 0)
	{
		put_pixel(data, draw.start, color, res);
		draw.start.h++;
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
	t_draw	draw;

	pixel.w = s->res.w - dda->line - 1;
	pixel.h = 0;
	draw.start = pixel;
	draw.length = dda->draw.h;
	draw_v_line(data, draw, CEILING_COLOR, s->res);
	pixel.h += dda->draw.h;
	draw_texture_line(data, pixel, dda, s);
		pixel.h += dda->draw.w - dda->draw.h;
	draw.start = pixel;
	draw.length = s->res.h - dda->draw.w;
	draw_v_line(data, draw, FLOOR_COLOR, s->res);
}
