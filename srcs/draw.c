/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 18:45:38 by hthomas           #+#    #+#             */
/*   Updated: 2020/06/18 15:28:05 by hthomas          ###   ########.fr       */
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

void	draw_texture_line(char *data, t_2int pos, t_dda *dda, t_scene *s)
{
	int 	length;
	float	step;
	int		color;
	t_2int	texSize = s->textures[dda->side]->size;

	double	wallX;
	if (dda->side % 2 == 0)
		wallX = s->pos.y + dda->perpWallDist * dda->rayDir.y;
	else
		wallX = s->pos.x + dda->perpWallDist * dda->rayDir.x;
    wallX -= floor(wallX);
	int texX = wallX * (double)texSize.w;
	if(dda->side % 2 == 0 && dda->rayDir.x > 0) texX = texSize.w - texX - 1;
	if(dda->side % 2 == 1 && dda->rayDir.y < 0) texX = texSize.w - texX - 1;



	step = (float)texSize.h / dda->lineHeight;
	float	texPos = (dda->draw.h - s->res.h / 2 + dda->lineHeight / 2) * step;



	length = (dda->lineHeight < s->res.h ? dda->lineHeight : s->res.h);
	// printf("\nlength	:%d\nlineH	:%d\nstep	:%f\n", length, dda->lineHeight, step);
	//  printf("posh:%d\nposw:%d\ntexPos	:%f\n", pos.h, pos.w, texPos);
	//  printf("data[%d][%d]\n", (int)texPos, texX);
	while (length-- > 0)
	{
		int texY = (int)texPos & (texSize.h - 1);
		texPos += step;
		// printf("\ntexX	:%d\ntexY	:%d\ntexpos	:%d\n", texX, texY, (int)texPos);
		color = s->textures[dda->side]->data[(int)(texSize.h * texY + texX)];
		put_pixel(data, pos, color, s->res); // set the pixel at the coord x,y with the color value
		pos.h++;
	}
}

void	draw_wall(char *data, t_dda *dda, t_scene *s)
{
	int			i;
	t_2int	pixel;

	pixel.w = s->res.w - dda->line - 1;
	// printf("draw: %d:%d\nline: %d\n", draw.h, draw.w, line);
	pixel.h = 0;
	draw_v_line(data, pixel, dda->draw.h, CEILING_COLOR, s->res);
	pixel.h += dda->draw.h;
	//draw_v_line(data, pixel, dda->draw.w - dda->draw.h, color, s->res);
	draw_texture_line(data, pixel, dda, s);
		pixel.h += dda->draw.w - dda->draw.h;
	draw_v_line(data, pixel, s->res.h - dda->draw.w - 1, FLOOR_COLOR, s->res);



	// i = 0;
	// while (i < dda->draw.h)
	// {
	// 	pixel.h = i++;
	// 	put_pixel(data, pixel, CEILING_COLOR, res); // set the pixel at the coord x,y with the color value
	// }
	// while (i < dda->draw.w)
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