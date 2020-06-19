/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 18:45:38 by hthomas           #+#    #+#             */
/*   Updated: 2020/06/19 08:35:58 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_pixel(char *data, t_2int pixel, int color, t_2int res)
{
	int	(*tab)[res.w][1]; // prepare the cast

	tab = (void *)data; // cast for change 1 dimension array to 2 dimensions
	*tab[pixel.h][pixel.w] = color; // set the pixel at the coord x,y with the color value
}

void	put_texture(char *data, t_2int pixel, char *texdata, t_2int res, int entier)
{
	int	(*tab);
	int	(*tabtexture);

	tab = (void *)data;
	tabtexture = (void *)texdata;
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
	while (length-- > 0)
	{
		int texY = (int)texPos & (texSize.h - 1);
		texPos += step;
		put_texture(data, pos, s->textures[dda->side]->data, s->res, texSize.w * texY + texX); 
		// data[4 * (pos.h * s->res.w + pos.w)] = s->textures[dda->side]->data[4 * (texSize.w * texY + texX)];
		// data[4 * (pos.h * s->res.w + pos.w) + 1] = s->textures[dda->side]->data[4 * (texSize.w * texY + texX) + 1];
		// data[4 * (pos.h * s->res.w + pos.w) + 2] = s->textures[dda->side]->data[4 * (texSize.w * texY + texX) + 2];
		// data[4 * (pos.h * s->res.w + pos.w) + 3] = s->textures[dda->side]->data[4 * (texSize.w * texY + texX) + 3];
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