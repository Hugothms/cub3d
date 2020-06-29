/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 18:45:38 by hthomas           #+#    #+#             */
/*   Updated: 2020/06/29 13:45:40 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_v_line(char *data, t_draw draw, t_2int res)
{
	while (draw.length-- > 0)
	{
		put_pixel(data, draw, draw.color, res);
		draw.start.h++;
	}
}

/*
**void	draw_v_line_shadow(char *data, t_draw draw, t_2int res)
**{
**	int i = 0;
**	if (draw.start.h == 0)
**		draw.coef = 1;
**	else
**		i = 1;
**	while (draw.length-- > 0)
**	{
**		put_pixel(data, draw, draw.color, res);
**		t_rgb *tcolor = int_to_rgb((draw.color / 256) % 256, draw.color /
**(256 * 256), draw.color % (256));
**		t_rgb *tmp = tcolor;
**		draw.coef *= (i == 0 ? 0.9999 : 1.0001);
**		tcolor = mult_rgb_float(*tcolor, draw.coef);
**		free(tmp);
**		min_rgb(tcolor);
**		draw.color = rgb_to_int(*tcolor);
**		free(tcolor);
**		draw.start.h++;
**	}
**}
*/

void	draw_texture_line2(t_2int pos, t_dda *dda, t_scene *s, t_flemme *fl)
{
	double	wallx;

	fl->tex_size = s->textures[dda->side]->size;
	if (dda->side % 2 == 0)
		wallx = s->pos.y + dda->perpwalldist[dda->line] * dda->rayDir.y;
	else
		wallx = s->pos.x + dda->perpwalldist[dda->line] * dda->rayDir.x;
	wallx -= floor(wallx);
	fl->texx = wallx * (double)fl->tex_size.w;
	if (dda->side % 2 == 0 && dda->rayDir.x > 0)
		fl->texx = fl->tex_size.w - fl->texx - 1;
	if (dda->side % 2 == 1 && dda->rayDir.y < 0)
		fl->texx = fl->tex_size.w - fl->texx - 1;
	fl->step = (float)fl->tex_size.h / dda->lineHeight;
	fl->texpos = (dda->draw.h - s->res.h / 2 + dda->lineHeight / 2) * fl->step;
	fl->length = (dda->lineHeight < s->res.h ? dda->lineHeight : s->res.h);
}

void	draw_texture_line(char *data, t_2int pos, t_dda *dda, t_scene *s)
{
	t_flemme	fl;
	t_draw		draw;

	draw_texture_line2(pos, dda, s, &fl);
	while (fl.length-- > 0)
	{
		fl.texy = (int)fl.texpos & (fl.tex_size.h - 1);
		fl.texpos += fl.step;
		draw.start = pos;
		draw.length = fl.tex_size.w * fl.texy + fl.texx;
		draw.color = dda->perpwalldist[dda->line];
		put_texture(data, draw, s->textures[dda->side]->data, s->res);
		pos.h++;
	}
}

/*
**data[4 * (pos.h * s->res.w + pos.w)] = s->textures[dda->side]->data[4 *
**(tex_size.w * texy + texx)];
**data[4 * (pos.h * s->res.w + pos.w) + 1] = s->textures[dda->side]->data[4 *
**(tex_size.w * texy + texx) + 1];
**data[4 * (pos.h * s->res.w + pos.w) + 2] = s->textures[dda->side]->data[4 *
**(tex_size.w * texy + texx) + 2];
**data[4 * (pos.h * s->res.w + pos.w) + 3] = s->textures[dda->side]->data[4 *
**(tex_size.w * texy + texx) + 3];
*/

/*
**t_rgb *tcolor;
**tcolor = int_to_rgb((color / 256) % 256, color / (256 * 256),
**color % (256));
**tcolor = mult_rgb_float(*s->ceil, 1/dda->perpwalldist[dda->line]);
**min_rgb(tcolor);
**draw.color = rgb_to_int(*tcolor);
**free(tcolor);
**
**tcolor = mult_rgb_float(*s->floor, 1/dda->perpwalldist[dda->line]);
**min_rgb(tcolor);
**draw.color = rgb_to_int(*tcolor);
**free(tcolor);
*/

void	draw_wall(char *data, t_dda *dda, t_scene *s)
{
	int		i;
	t_2int	pixel;
	t_draw	draw;

	pixel.w = s->res.w - dda->line - 1;
	pixel.h = 0;
	draw.start = pixel;
	draw.length = dda->draw.h;
	draw.color = rgb_to_int(*s->ceil);
	draw_v_line(data, draw, s->res);
	pixel.h += dda->draw.h;
	draw_texture_line(data, pixel, dda, s);
	pixel.h += dda->draw.w - dda->draw.h;
	draw.start = pixel;
	draw.length = s->res.h - dda->draw.w;
	draw.color = rgb_to_int(*s->floor);
	draw_v_line(data, draw, s->res);
}
