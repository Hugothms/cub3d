/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 16:03:24 by hthomas           #+#    #+#             */
/*   Updated: 2020/06/06 17:44:54 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void 		turn_left(t_window *w)
{
	rotate(&w->scene->dir, THETA);
	rotate(&w->scene->plane, THETA);
	refresh(w);
}

void 		turn_right(t_window *w)
{
	rotate(&w->scene->dir, -THETA);
	rotate(&w->scene->plane, -THETA);
	refresh(w);
}

void		check_key_on(t_scene *scene)
{
	if (scene->move.up == 1)
		move_up(scene);
	if (scene->move.down == 1)
		move_down(scene);
	if (scene->move.left == 1)
		move_left(scene);
	if (scene->move.right == 1)
		move_right(scene);
	if (scene->move.turn_left == 1)
		turn_left(scene);
	if (scene->move.turn_right == 1)
		turn_right(scene);
}
