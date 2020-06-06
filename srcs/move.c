/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 16:50:32 by hthomas           #+#    #+#             */
/*   Updated: 2020/06/06 23:23:56 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void 		move_up(t_window *w)
{
	if (w->s->map[(int)(w->s->pos.x + w->s->dir.x * SPEED_MOVE)]\
	[(int)w->s->pos.y] == '0')
		w->s->pos.x += w->s->dir.x * SPEED_MOVE;
	if (w->s->map[(int)w->s->pos.x]\
	[(int)(w->s->pos.y + w->s->dir.y * SPEED_MOVE)] == '0')
		w->s->pos.y += w->s->dir.y * SPEED_MOVE;
	refresh(w);
}

void 		move_down(t_window *w)
{
	if (w->s->map[(int)(w->s->pos.x - w->s->dir.x * SPEED_MOVE)]\
	[(int)w->s->pos.y] == '0')
		w->s->pos.x -= w->s->dir.x * SPEED_MOVE;
	if (w->s->map[(int)w->s->pos.x]\
	[(int)(w->s->pos.y - w->s->dir.y * SPEED_MOVE)] == '0')
		w->s->pos.y -= w->s->dir.y * SPEED_MOVE;
	refresh(w);
}

void 		move_left(t_window *w)
{
	if (w->s->map[(int)(w->s->pos.x + w->s->plane.x * SPEED_MOVE)]\
	[(int)w->s->pos.y] == '0')
		w->s->pos.x += w->s->plane.x * SPEED_MOVE;
	if (w->s->map[(int)w->s->pos.x]\
	[(int)(w->s->pos.y + w->s->plane.y * SPEED_MOVE)] == '0')
		w->s->pos.y += w->s->plane.y * SPEED_MOVE;
	refresh(w);
}

void 		move_right(t_window *w)
{
	if (w->s->map[(int)(w->s->pos.x - w->s->plane.x * SPEED_MOVE)]\
	[(int)w->s->pos.y] == '0')
		w->s->pos.x -= w->s->plane.x * SPEED_MOVE;
	if (w->s->map[(int)w->s->pos.x]\
	[(int)(w->s->pos.y - w->s->plane.y * SPEED_MOVE)] == '0')
		w->s->pos.y -= w->s->plane.y * SPEED_MOVE;
	refresh(w);
}
