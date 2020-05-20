/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugothms <hugothms@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 16:50:32 by hugothms          #+#    #+#             */
/*   Updated: 2020/05/20 16:53:15 by hugothms         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void 		move_up(t_scene *scene)
{
	scene->pos.x += scene->dir.x * SPEED_MOVE;
	scene->pos.y += scene->dir.y * SPEED_MOVE;
	// if (scene->pos.x > scene->size.h)
	// 	scene->pos.x = scene->size.h;
	// if (scene->pos.y > scene->size.w)
	// 	scene->pos.y = scene->size.w;
}

void 		move_down(t_scene *scene)
{
	scene->pos.x -= scene->dir.x * SPEED_MOVE;
	scene->pos.y -= scene->dir.y * SPEED_MOVE;
	// if (scene->pos.x > scene->size.h)
	// 	scene->pos.x = scene->size.h;
	// if (scene->pos.y > scene->size.w)
	// 	scene->pos.y = scene->size.w;
}

void 		move_left(t_scene *scene)
{
	rotation(&scene->dir, THETA);
	rotation(&scene->plane, THETA);
}

void 		move_right(t_scene *scene)
{
	rotation(&scene->dir, -THETA);
	rotation(&scene->plane, -THETA);
}

void		check_key_on(t_scene *scene)
{
	if (scene->move.w_on == 1)
		move_up(scene);
	if (scene->move.s_on == 1)
		move_down(scene);
	if (scene->move.a_on == 1)
		move_left(scene);
	if (scene->move.d_on == 1)
		move_right(scene);
	// if (scene->move.g_on == 1)
	// 	rotate_g_dr(scene, KEY_G);
	// if (scene->move.dr_on == 1)
	// 	rotate_g_dr(scene, KEY_DR);
}
