/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 16:50:32 by hthomas           #+#    #+#             */
/*   Updated: 2020/06/24 15:13:59 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		move_up(t_window *w)
{
	if (w->s->map[(int)(w->s->pos.x + w->s->dir.x * SPEED_MOVE)]\
	[(int)w->s->pos.y] == '0')
		w->s->pos.x += w->s->dir.x * SPEED_MOVE;
	if (w->s->map[(int)w->s->pos.x]\
	[(int)(w->s->pos.y + w->s->dir.y * SPEED_MOVE)] == '0')
		w->s->pos.y += w->s->dir.y * SPEED_MOVE;
	refresh(w);
}

void		move_down(t_window *w)
{
	if (w->s->map[(int)(w->s->pos.x - w->s->dir.x * SPEED_MOVE)]\
	[(int)w->s->pos.y] == '0')
		w->s->pos.x -= w->s->dir.x * SPEED_MOVE;
	if (w->s->map[(int)w->s->pos.x]\
	[(int)(w->s->pos.y - w->s->dir.y * SPEED_MOVE)] == '0')
		w->s->pos.y -= w->s->dir.y * SPEED_MOVE;
	refresh(w);
}

void		move_left(t_window *w)
{
	if (w->s->map[(int)(w->s->pos.x + w->s->plane.x * SPEED_MOVE)]\
	[(int)w->s->pos.y] == '0')
		w->s->pos.x += w->s->plane.x * SPEED_MOVE;
	if (w->s->map[(int)w->s->pos.x]\
	[(int)(w->s->pos.y + w->s->plane.y * SPEED_MOVE)] == '0')
		w->s->pos.y += w->s->plane.y * SPEED_MOVE;
	refresh(w);
}

void		move_right(t_window *w)
{
	if (w->s->map[(int)(w->s->pos.x - w->s->plane.x * SPEED_MOVE)]\
	[(int)w->s->pos.y] == '0')
		w->s->pos.x -= w->s->plane.x * SPEED_MOVE;
	if (w->s->map[(int)w->s->pos.x]\
	[(int)(w->s->pos.y - w->s->plane.y * SPEED_MOVE)] == '0')
		w->s->pos.y -= w->s->plane.y * SPEED_MOVE;
	refresh(w);
}

/*
** void		move_up(t_window * w)
** {
** 	int	i;
** 	int	wall;
** 
** 	i = 0;
** 	wall = 0;
** 	while (i < w->s->dir.x + 1 && i >= 0 && i < w->s->size.h)
** 	{
** 		if (w->s->map[(int)(w->s->pos.x + i * SPEED_MOVE)]\
** 		[(int)w->s->pos.y] != '0')
** 		{
** 			wall = 1;
** 			break;
** 		}
** 		i++;
** 	}
** 	if (!wall)
** 		w->s->pos.x += w->s->dir.x * SPEED_MOVE;
** 	i = 0;
** 	wall = 0;
** 	while (i < w->s->dir.y +1)
** 	{
** 		if (w->s->map[(int)w->s->pos.x]\
** 		[(int)(w->s->pos.y + i * SPEED_MOVE)] != '0')
** 		{
** 			wall = 1;
** 			break;
** 		}
** 		i++;
** 	}
** 	if (!wall)
** 		w->s->pos.y += w->s->dir.y * SPEED_MOVE;
** 	refresh(w);
** }
*/
