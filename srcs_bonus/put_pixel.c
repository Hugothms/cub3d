/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 14:24:32 by hthomas           #+#    #+#             */
/*   Updated: 2020/06/28 19:29:34 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_pixel(char *data, t_draw draw, int color, t_2int res)
{
	int	(*tab)[res.w][1];

	tab = (void *)data;
		// printf("\n%d:%d:%d\n", (color / 256) % 256, color / (256 * 256), color % (256));
	draw.color = draw.color / (float)((draw.color + 1) * 100);
	*tab[draw.start.h][draw.start.w] = draw.color;
	*tab[draw.start.h][draw.start.w] = color;
}

void	put_texture(char *data, t_draw draw, char *texdata, t_2int res)
{
	int		(*tab);
	int		(*tabtexture);
	float	color;

	tab = (void *)data;
	tabtexture = (void *)texdata;
	color = tabtexture[draw.length] / (float)(draw.color + 1);
	tab[draw.start.h * res.w + draw.start.w] = color;;
}

void	put_sprite(char *data, t_draw draw, char *texdata, t_2int res)
{
	int	(*tab);
	int	(*tabtexture);

	tab = (void *)data;
	tabtexture = (void *)texdata;
	if ((tabtexture[draw.length] & 0x00FFFFFF) != 0)
		tab[draw.start.h * res.w + draw.start.w] = tabtexture[draw.length];
}
