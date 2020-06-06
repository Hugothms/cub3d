/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 16:50:32 by hthomas           #+#    #+#             */
/*   Updated: 2020/06/06 17:44:54 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void 		move_up(t_window *w)
{
	if (w->scene->map[(int)(w->scene->pos.x + w->scene->dir.x * SPEED_MOVE)][(int)w->scene->pos.y] == '0')
		w->scene->pos.x += w->scene->dir.x * SPEED_MOVE;
	if (w->scene->map[(int)w->scene->pos.x][(int)(w->scene->pos.y + w->scene->dir.y * SPEED_MOVE)] == '0')
		w->scene->pos.y += w->scene->dir.y * SPEED_MOVE;
	refresh(w);
}

void 		move_down(t_window *w)
{
	if (w->scene->map[(int)(w->scene->pos.x - w->scene->dir.x * SPEED_MOVE)][(int)w->scene->pos.y] == '0')
		w->scene->pos.x -= w->scene->dir.x * SPEED_MOVE;
	if (w->scene->map[(int)w->scene->pos.x][(int)(w->scene->pos.y - w->scene->dir.y * SPEED_MOVE)] == '0')
		w->scene->pos.y -= w->scene->dir.y * SPEED_MOVE;
	refresh(w);
}

void 		move_left(t_window *w)
{
	if (w->scene->map[(int)(w->scene->pos.x + w->scene->plane.x * SPEED_MOVE)][(int)w->scene->pos.y] == '0')
		w->scene->pos.x += w->scene->plane.x * SPEED_MOVE;
	if (w->scene->map[(int)w->scene->pos.x][(int)(w->scene->pos.y + w->scene->plane.y * SPEED_MOVE)] == '0')
		w->scene->pos.y += w->scene->plane.y * SPEED_MOVE;
	refresh(w);
}

void 		move_right(t_window *w)
{
	if (w->scene->map[(int)(w->scene->pos.x - w->scene->plane.x * SPEED_MOVE)][(int)w->scene->pos.y] == '0')
		w->scene->pos.x -= w->scene->plane.x * SPEED_MOVE;
	if (w->scene->map[(int)w->scene->pos.x][(int)(w->scene->pos.y - w->scene->plane.y * SPEED_MOVE)] == '0')
		w->scene->pos.y -= w->scene->plane.y * SPEED_MOVE;
	refresh(w);
}
