/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugothms <hugothms@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 12:20:18 by hthomas           #+#    #+#             */
/*   Updated: 2020/05/08 20:04:09 by hugothms         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_rgb	*int_to_rgb(int r, int g, int b)
{
	t_rgb	*rgb;

	if(!(rgb = malloc(sizeof(*rgb))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	rgb->r = r;
	rgb->g = g;
	rgb->b = b;
	return (rgb);
}

t_rgb		*str_to_rgb(char *str)
{
	char	**tab;

	tab = ft_split(str, ',');
	return (int_to_rgb(ft_atoi(tab[0]), ft_atoi(tab[1]), ft_atoi(tab[2])));
}

int		rgb_to_int(t_rgb rgb)
{
	return(rgb.r << 16 | rgb.g << 8 | rgb.b);
}
