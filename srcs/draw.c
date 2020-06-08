/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 18:45:38 by hthomas           #+#    #+#             */
/*   Updated: 2020/06/08 18:48:19 by hthomas          ###   ########.fr       */
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
