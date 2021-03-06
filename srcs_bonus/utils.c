/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 10:24:22 by hthomas           #+#    #+#             */
/*   Updated: 2020/07/01 11:54:52 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		ft_tab_size(char **tab)
{
	int i;

	if (!tab)
		return (0);
	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int		max_len_tab(char **tab)
{
	int	i;
	int	len;
	int	max;

	if (!tab)
		return (0);
	i = 0;
	max = 0;
	while (tab[i])
	{
		len = ft_strlen(tab[i]);
		max = (len > max ? len : max);
		i++;
	}
	return (max);
}

void	rotate(t_2float *dir, float angle)
{
	float	x;

	x = dir->x;
	dir->x = x * cos(angle) - dir->y * sin(angle);
	dir->y = x * sin(angle) + dir->y * cos(angle);
}

void	join_clean(char **s1, char *s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = ft_strjoin(*s1, s2);
	free(tmp);
}

void	save(t_scene *scene, t_img *img, t_mlx *mlx)
{
	t_window	*w;
	char		filename[35];

	if (!(w = malloc(sizeof(*w))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	w->s = scene;
	w->img = img;
	w->mlx = mlx;
	make_img(img, scene);
	save_bmp(screenshot_datetime(filename), img->data, scene->res);
	close_function(w, 1);
}
