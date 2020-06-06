/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 16:03:24 by hthomas           #+#    #+#             */
/*   Updated: 2020/06/06 17:58:02 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void 		turn_left(t_window *w)
{
	rotate(&w->s->dir, THETA);
	rotate(&w->s->plane, THETA);
	refresh(w);
}

void 		turn_right(t_window *w)
{
	rotate(&w->s->dir, -THETA);
	rotate(&w->s->plane, -THETA);
	refresh(w);
}

void		check_key_on(t_window *w)
{
	if (w->s->move.up == 1)
		move_up(w);
	if (w->s->move.down == 1)
		move_down(w);
	if (w->s->move.left == 1)
		move_left(w);
	if (w->s->move.right == 1)
		move_right(w);
	if (w->s->move.turn_left == 1)
		turn_left(w);
	if (w->s->move.turn_right == 1)
		turn_right(w);
}
