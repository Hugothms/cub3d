/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 14:24:32 by hthomas           #+#    #+#             */
/*   Updated: 2020/06/24 14:26:28 by hthomas          ###   ########.fr       */
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
