/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 18:54:35 by hthomas           #+#    #+#             */
/*   Updated: 2020/06/07 10:03:38 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_err_and_exit(char *str, int err)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(" (exit code: ", STDERR_FILENO);
	ft_putnbr_fd(err, STDERR_FILENO);
	ft_putstr_fd(")\n", STDERR_FILENO);
	exit(err);
}

void	free_scene(t_scene *scene)
{
	int	i;
	
	i = 0;
	while (i < scene->size.h)
		free(scene->map[i++]);
	free(scene->map);
	i = 0;
	while (i < NB_TEXTURES)
	{
		free(scene->tex[i]);
		//free(scene->textures[i]);
		i++;
	}
	free(scene->tex);
	free(scene->ceil);
	free(scene->floor);
	free(scene);
}

int		close_function(const t_window *w)
{
	mlx_clear_window(w->mlx->mlx_ptr, w->mlx->win_ptr);
	mlx_destroy_image(w->mlx->mlx_ptr, w->img->img_ptr);
	mlx_destroy_window(w->mlx->mlx_ptr, w->mlx->win_ptr);
	free(w->mlx);
	free(w->img);
	free_scene(w->s);
	exit(0);
}