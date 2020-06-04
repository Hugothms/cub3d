/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugothms <hugothms@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 16:50:32 by hugothms          #+#    #+#             */
/*   Updated: 2020/06/04 11:14:50 by hugothms         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void 		move_up(t_scene *scene)
{
	if (scene->map[(int)(scene->pos.x + scene->dir.x * SPEED_MOVE)][(int)scene->pos.y] == '0')
		scene->pos.x += scene->dir.x * SPEED_MOVE;
	if (scene->map[(int)scene->pos.x][(int)(scene->pos.y + scene->dir.y * SPEED_MOVE)] == '0')
		scene->pos.y += scene->dir.y * SPEED_MOVE;
}

void 		move_down(t_scene *scene)
{
	if (scene->map[(int)(scene->pos.x - scene->dir.x * SPEED_MOVE)][(int)scene->pos.y] == '0')
		scene->pos.x -= scene->dir.x * SPEED_MOVE;
	if (scene->map[(int)scene->pos.x][(int)(scene->pos.y - scene->dir.y * SPEED_MOVE)] == '0')
		scene->pos.y -= scene->dir.y * SPEED_MOVE;
}

void 		move_left(t_scene *scene)
{
	if (scene->map[(int)(scene->pos.x + scene->plane.x * SPEED_MOVE)][(int)scene->pos.y] == '0')
		scene->pos.x += scene->plane.x * SPEED_MOVE;
	if (scene->map[(int)scene->pos.x][(int)(scene->pos.y + scene->plane.y * SPEED_MOVE)] == '0')
		scene->pos.y += scene->plane.y * SPEED_MOVE;
}

void 		move_right(t_scene *scene)
{
	if (scene->map[(int)(scene->pos.x - scene->plane.x * SPEED_MOVE)][(int)scene->pos.y] == '0')
		scene->pos.x -= scene->plane.x * SPEED_MOVE;
	if (scene->map[(int)scene->pos.x][(int)(scene->pos.y - scene->plane.y * SPEED_MOVE)] == '0')
		scene->pos.y -= scene->plane.y * SPEED_MOVE;
}

void 		turn_left(t_scene *scene)
{
	rotate(&scene->dir, THETA);
	rotate(&scene->plane, THETA);
}

void 		turn_right(t_scene *scene)
{
	rotate(&scene->dir, -THETA);
	rotate(&scene->plane, -THETA);
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
