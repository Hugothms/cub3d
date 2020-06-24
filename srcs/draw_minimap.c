/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 18:48:31 by hthomas           #+#    #+#             */
/*   Updated: 2020/06/24 14:52:27 by hthomas          ###   ########.fr       */
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

void	draw_square(char *data, t_draw draw, int color, t_2int res)
{
	int		i;

	i = 0;
	while (i < draw.length)
	{
		draw_v_line(data, draw, color, res);
		draw.start.w++;
		i++;
	}
}

void	square(t_img *img, t_scene *scene, t_2int index, int color)
{
	t_2int	pos;

	t_draw	draw;
	
	pos.w = 20 + index.w * scene->res.w / 200;
	pos.h = 20 + index.h * scene->res.w / 200;
	draw.start = pos;
	draw.length = scene->res.w / 200;
	draw_square(img->data, draw, color,	scene->res);
}

void	draw_minimap(t_img *img, t_scene *scene)
{
	t_2int	index;
	int		len;
	
	index.h = 0;
	while (index.h < scene->size.h)
	{
		index.w = 0;
		len = ft_strlen(scene->map[index.h]);
		while (index.w < len)
		{
			if (scene->map[index.h][index.w] == '1' || scene->map[index.h][index.w] == '8')
				square(img, scene, index, WHITE);
			if (scene->map[index.h][index.w] == '2')
				square(img, scene, index, PINK);
			index.w++;
		}
		index.h++;
	}
}

void	draw_pos_minimap(t_img *img, t_scene *s)
{
	t_draw	draw;

	draw.start.w = 20 + s->pos.y * s->res.w / 200 - s->res.w / 200 / 2;
	draw.start.h = 20 + s->pos.x * s->res.w / 200 - s->res.w / 200 / 2;
	draw.length = s->res.w / 200;
	draw_square(img->data, draw, RED, s->res);
	draw.start.w += s->res.w / 200 / 2;
	draw.start.h += s->res.w / 200 / 2;
	draw.end.x = s->dir.y / 2;
	draw.end.y = s->dir.x / 2;
	draw_line(img->data, s, draw, RED, s->res);
}
