/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 18:48:31 by hthomas           #+#    #+#             */
/*   Updated: 2020/06/24 14:12:31 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_line(char *data, t_scene *s, t_draw draw, int color, t_2int res)
{
	int			ymax;
	int			xmax;
	t_2float	pos;
	int			i;

	ymax = 20 + s->size.h * s->res.w / 100;
	xmax = 20 + ft_strlen(s->map[(int)s->pos.x]) * s->res.w / 100;
	pos.x = draw.start.h;
	pos.y = draw.start.w;
	i = 4 * s->res.w / 100;
	while (i--)
	{
		put_pixel(data, draw.start, color, res);
		pos.x += draw.end.y;
		pos.y += draw.end.x;
		draw.start.h = pos.x;
		draw.start.w = pos.y;
	}
}

void	draw_square(char *data, t_2int pos, int length, int color, t_2int res)
{
	int	i;

	i = 0;
	while (i < length)
	{
		draw_v_line(data, pos, length, color, res);
		pos.w++;
		i++;
	}
}

void	draw_minimap(t_img *img, t_scene *scene)
{
	int	col;
	int	line;
	int	len;
	t_2int pos;

	col = 0;
	while (col < scene->size.h)
	{
		line = 0;
		len = ft_strlen(scene->map[col]);
		while (line < len)
		{
			if (scene->map[col][line] == '1' || scene->map[col][line] == '8')
			{
				pos.w = 20 + line * scene->res.w / 200;
				pos.h = 20 + col * scene->res.w / 200;
				draw_square(img->data, pos, scene->res.w / 200, WHITE,
				scene->res);
			}
			if (scene->map[col][line] == '2')
			{
				pos.w = 20 + line * scene->res.w / 200;
				pos.h = 20 + col * scene->res.w / 200;
				draw_square(img->data, pos, scene->res.w / 200, PINK,
				scene->res);
			}
			line++;
		}
		col++;
	}
}

void	draw_pos_minimap(t_img *img, t_scene *s)
{
	t_draw draw;

	draw.start.w = 20 + s->pos.y * s->res.w / 200 - s->res.w / 200 / 2;
	draw.start.h = 20 + s->pos.x * s->res.w / 200 - s->res.w / 200 / 2;
	draw_square(img->data, draw.start, s->res.w  / 200, RED, s->res);
	draw.start.w += s->res.w / 200 / 2;
	draw.start.h += s->res.w / 200 / 2;
	draw.end.x = s->dir.y / 2;
	draw.end.y = s->dir.x / 2;
	draw_line(img->data, s, draw, RED, s->res);
}
