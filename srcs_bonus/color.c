/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 12:20:18 by hthomas           #+#    #+#             */
/*   Updated: 2020/07/03 13:19:30 by hthomas          ###   ########.fr       */
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
	t_rgb	*res;
	int		r;
	int		g;
	int		b;

	if (str[ft_strlen(str) - 1] == ',')
		return (NULL);
	tab = ft_split(str, ',');
	if (ft_tab_size(tab) != 3)
	{
		free_tab((void**)tab);
		return (NULL);
	}
	r = ft_atoi_strict(tab[0]);
	g = ft_atoi_strict(tab[1]);
	b = ft_atoi_strict(tab[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		print_err_and_exit("Floor RGB value out of range", PARSE_ERROR);
	res = int_to_rgb(r, g, b);
	free_tab((void**)tab);
	return (res);
}

int		rgb_to_int(t_rgb rgb)
{
	return (rgb.r << 16 | rgb.g << 8 | rgb.b);
}

int		str_to_int(char *str)
{
	int		color;
	t_rgb	*rgb;

	rgb = str_to_rgb(str);
	color = rgb_to_int(*rgb);
	free(rgb);
	return (color);
}
