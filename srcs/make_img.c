/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 20:08:47 by hthomas           #+#    #+#             */
/*   Updated: 2020/06/07 11:49:30 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_pixel(char *data, t_2int pixel, int color, t_2int res)
{
	int	(*tab)[res.w][1]; // prepare the cast

	tab = (void *)data; // cast for change 1 dimension array to 2 dimensions
	*tab[pixel.h][pixel.w] = color; // set the pixel at the coord x,y with the color value
}

void	draw_v_line(char *data, t_2int pos, int length, int color, t_2int res)
{
	while (length-- > 0)
	{
		put_pixel(data, pos, color, res); // set the pixel at the coord x,y with the color value
		pos.h++;
	}
}

void	draw_line(char *data, t_scene *s, t_draw draw, int color, t_2int res)
{
	int	ymax;	
	int	xmax;
	t_2float	pos;

	ymax = 20 + s->size.h * SIZE_MINIMAP;
	xmax = 20 + ft_strlen(s->map[(int)s->pos.x]) * SIZE_MINIMAP;
	// printf("draw%d:%d\n", draw.start.h,draw.start.w );
	// printf("max%d:%d\n", ymax, xmax );
	pos.x = draw.start.h;
	pos.y = draw.start.w;
	// while (draw.start.h > 20 && draw.start.h < ymax && draw.start.w > 20 && draw.start.w < xmax)
	int	i = 20;
	while (i--)
	{
		//printf("%d:%d\n", draw.start.h, draw.start.w);
		put_pixel(data, draw.start, color, res); // set the pixel at the coord x,y with the color value
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
		draw_v_line(data, pos, length, color, res); // set the pixel at the coord x,y with the color value
		pos.w++;
		i++;
	}
}

void	draw_wall(char *data, int line, t_2int delim, int color, t_2int res)
{
	int			i;
	t_2int	pixel;
	
	pixel.w = line;
	// printf("delim: %d:%d\nline: %d\n", delim.h, delim.w, line);
	// i = 0;
	pixel.h = 0;
	draw_v_line(data, pixel, delim.h, CEILING_COLOR, res);
	pixel.h += delim.h;
	draw_v_line(data, pixel, delim.w - delim.h, color, res);
	pixel.h += delim.w - delim.h;
	draw_v_line(data, pixel, res.h - delim.w - 1, FLOOR_COLOR, res);
	// while (i < delim.h)
	// {
	// 	pixel.h = i++;
	// 	put_pixel(data, pixel, CEILING_COLOR, res); // set the pixel at the coord x,y with the color value
	// }
	// while (i < delim.w)
	// {
	// 	pixel.h = i++;
	// 	put_pixel(data, pixel, wall_color, res); // set the pixel at the coord x,y with the color value
	// }
	// while (i < res.h)
	// {
	// 	pixel.h = i++;
	// 	put_pixel(data, pixel, FLOOR_COLOR, res); // set the pixel at the coord x,y with the color value
	// }
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
			if (scene->map[col][line] != '0')
			{
				pos.w = 20 + line * SIZE_MINIMAP;
				pos.h = 20 + col * SIZE_MINIMAP;
				draw_square(img->data, pos, SIZE_MINIMAP, 16777215, scene->res);
			}
			line++;
		}
		col++;
	}
}

void	calcul_dda(t_dda *dda, t_scene *s, int x)
{
	double	cameraX;

	cameraX = 2 * x / (double)s->res.w - 1; 
	dda->rayDir.x = s->dir.x + s->plane.x * cameraX;
	dda->rayDir.y = s->dir.y + s->plane.y * cameraX;
	dda->coord.h = (int)s->pos.x;
	dda->coord.w = (int)s->pos.y;
	dda->deltaDist.x = fabs(1 / dda->rayDir.x);
	dda->deltaDist.y = fabs(1 / dda->rayDir.y);
}

void	set_side_dist(t_dda *dda, t_scene *s)
{
	if (dda->rayDir.x < 0)
	{
		dda->step.h = -1;
		dda->sideDist.x = (s->pos.x - dda->coord.h) * dda->deltaDist.x;
	}
	else
	{
		dda->step.h = 1;
		dda->sideDist.x = (dda->coord.h + 1.0 - s->pos.x) * dda->deltaDist.x;
	}
	if (dda->rayDir.y < 0)
	{
		dda->step.w = -1;
		dda->sideDist.y = (s->pos.y - dda->coord.w) * dda->deltaDist.y;
	}
	else
	{
		dda->step.w = 1;
		dda->sideDist.y = (dda->coord.w + 1.0 - s->pos.y) * dda->deltaDist.y;
	}
}

void	perform_dda(t_scene *s, t_dda *dda)
{
	int	hit; //was there a wall hit?

	hit = 0;
	while (hit == 0)
	{
		//jump to next map square, OR in x-direction, OR in y-direction
		if (dda->sideDist.x < dda->sideDist.y)
		{
			dda->sideDist.x += dda->deltaDist.x;
			dda->coord.h += dda->step.h;
			dda->side = ((dda->rayDir.x > 0) ? 0 : 2);
		}
		else
		{
			dda->sideDist.y += dda->deltaDist.y;
			dda->coord.w += dda->step.w;
			dda->side = ((dda->rayDir.y > 0) ? 1 : 3);
		}
		//Check if ray has hit a wall
		// printf("map%d:%d\n", dda->coord.h, dda->coord.w);
		if (s->map[dda->coord.h][dda->coord.w] != '0')
			hit = 1;
	}
}

void	set_draw_start_end(t_dda *dda, t_scene *s)
{
	double	perpWallDist;
	int		lineHeight;

	if (dda->side % 2 == 0)
		perpWallDist = (dda->coord.h - s->pos.x +\
		(1 - dda->step.h) / 2.) / dda->rayDir.x;
	else
		perpWallDist = (dda->coord.w - s->pos.y +\
		(1 - dda->step.w) / 2.) / dda->rayDir.y;
	// printf("res.h: %d\tperp:%f\n", scene->res.h, perpWallDist);
	//Calculate height of line to draw on screen
	lineHeight = (s->res.h / perpWallDist);
	// printf("lineHeight: %d\n", lineHeight);
	//calculate lowest and highest pixel to fill in current stripe
	dda->draw.h= -lineHeight / 2 + s->res.h / 2;
	if (dda->draw.h< 0)
		dda->draw.h= 0;
	dda->draw.w = lineHeight / 2 + s->res.h / 2;
	if (dda->draw.w >= s->res.h)
		dda->draw.w = s->res.h - 1;
}

void	set_color_wall(t_dda *dda, t_rgb **color)
{
	if (dda->side == 0)
		*color = int_to_rgb(0,255,255);
	else if (dda->side == 1)
		*color = int_to_rgb(255,0,255);
	else if (dda->side == 2)
		*color = int_to_rgb(255,255,0);
	else if (dda->side == 3)
		*color = int_to_rgb(0,255,0);
	else
		*color = int_to_rgb(255,0,0);
}

void	set_delim(t_dda *dda, t_scene *s)
{
	if (dda->draw.h < s->res.h)
	{
		if (dda->draw.h > 0)
			dda->delim.h = dda->draw.h;
		else 
			dda->delim.h = 0;
	}
	else
		dda->delim.h = 0;
	if (dda->draw.w < s->res.h)
	{
		if (dda->draw.w > 0)
			dda->delim.w = dda->draw.w;
		else 
			dda->delim.w = 0;
	}
	else
		dda->delim.w = 0;
}

void	draw_pos_minimap(t_img *img, t_scene *s)
{
	t_draw draw;
	draw.start.w = 20 + s->pos.y * SIZE_MINIMAP - SIZE_MINIMAP / 2;
	draw.start.h = 20 + s->pos.x * SIZE_MINIMAP - SIZE_MINIMAP / 2;
	draw_square(img->data, draw.start, SIZE_MINIMAP, RED, s->res);
	draw.start.w += SIZE_MINIMAP / 2;
	draw.start.h += SIZE_MINIMAP / 2;
	draw.end.x = s->dir.y;
	draw.end.y = s->dir.x;
	draw_line(img->data, s, draw, RED, s->res);
}

void	make_img(t_img *img, t_scene *s)
{
	int		x;
	t_dda	*dda;
	t_rgb	*color;

	x = 0;
	if(!(dda = malloc(sizeof(*dda))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	while (x < s->res.w)
	{
		calcul_dda(dda, s, x);
		set_side_dist(dda, s);
		perform_dda(s, dda);
		set_draw_start_end(dda, s);
		set_color_wall(dda, &color);
		set_delim(dda, s);
		draw_wall(img->data, s->res.w - x - 1, dda->delim,rgb_to_int(*color),\
		s->res);
		free(color);
		draw_pos_minimap(img, s);
		x++;
	}
	free(dda);
	draw_minimap(img, s);
}