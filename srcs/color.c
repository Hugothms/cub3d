/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 12:20:18 by hthomas           #+#    #+#             */
/*   Updated: 2020/06/07 11:57:00 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_rgb	*int_to_rgb(int r, int g, int b)
{
	t_rgb	*rgb;

	if (!(rgb = malloc(sizeof(*rgb))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	rgb->r = r;
	rgb->g = g;
	rgb->b = b;
	return (rgb);
}

t_rgb	*str_to_rgb(char *str)
{
	char	**tab;
	t_rgb	*tmp;

	tab = ft_split(str, ',');
	tmp = int_to_rgb(ft_atoi(tab[0]), ft_atoi(tab[1]), ft_atoi(tab[2]));
	free_tab((void**)tab);
	return (tmp);
}

int		rgb_to_int(t_rgb rgb)
{
	return (rgb.r << 16 | rgb.g << 8 | rgb.b);
}
