/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugothms <hugothms@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 16:49:23 by hugothms          #+#    #+#             */
/*   Updated: 2020/05/20 16:53:13 by hugothms         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		key_release(int keycode, t_move *move)
{
	printf("key_release\n");
	if (keycode == (AZERTY ? KEY_Z : KEY_W))
		move->w_on = 0;
	if (keycode == (AZERTY ? KEY_S : KEY_S))
		move->s_on = 0;
	if (keycode == (AZERTY ? KEY_Q : KEY_A))
		move->a_on = 0;
	if (keycode == (AZERTY ? KEY_D : KEY_D))
		move->d_on = 0;
	// if (keycode == G)
	// 	move->g_on = 0;
	// if (keycode == DR)
	// 	move->dr_on = 0;
	return (0);
}

int		key_push(int keycode, t_move *move)
{
	printf("key_push\n");
	if (keycode == (AZERTY ? KEY_Z : KEY_W))
		move->w_on = 1;
	if (keycode == (AZERTY ? KEY_S : KEY_S))
		move->s_on = 1;
	if (keycode == (AZERTY ? KEY_Q : KEY_A))
		move->a_on = 1;
	if (keycode == (AZERTY ? KEY_D : KEY_D))
		move->d_on = 1;
	// if (keycode == G)
	// 	move->g_on = 1;
	// if (keycode == DR)
	// 	move->dr_on = 1;
	// if (keycode == 17 && move->dm == 0)
	// 	move->dm = 1;
	// else if (keycode == 17 && move->dm == 1)
	// 	move->dm = 0;
	return (0);
}

// void		key_hook(int keycode, t_scene *scene)
// {
// 	if (keycode == 53)
// 		close_prog(scene);
// 	if (keycode == 78 && scene->spe.rot_spe + RS > 0.0051)
// 		scene->spe.rot_spe -= 0.005;
// 	if (keycode == 69 && scene->spe.rot_spe + RS < 0.25)
// 		scene->spe.rot_spe += 0.005;
// 	if (keycode == 125 && scene->spe.mov_spe + MS > 0.05)
// 		scene->spe.mov_spe -= 0.01;
// 	if (keycode == 126 && scene->spe.mov_spe + MS < 0.5)
// 		scene->spe.mov_spe += 0.01;
// 	if (keycode == KEY_S)
// 		save(cub);
// }

int		key_function(const int keycode, const t_window *w)
{
	char	filename[35];
	clock_t	start, end;
	float x;

	printf("key_function\n");
	printf("%i\n", keycode);
	key_push(keycode, &w->scene->move);
	if (keycode == ESC)
		close_function(w);
	else if (keycode == UP)
	{
		w->scene->pos.x += w->scene->dir.x * SPEED_MOVE;
		w->scene->pos.y += w->scene->dir.y * SPEED_MOVE;
		// if (w->scene->pos.x > w->scene->size.h)
		// 	w->scene->pos.x = w->scene->size.h;
		// if (w->scene->pos.y > w->scene->size.w)
		// 	w->scene->pos.y = w->scene->size.w;
		refresh(w);
	}
	else if (keycode == DOWN)
	{
		w->scene->pos.x -= w->scene->dir.x * SPEED_MOVE;
		w->scene->pos.y -= w->scene->dir.y * SPEED_MOVE;
		// if (w->scene->pos.x > w->scene->size.h)
		// 	w->scene->pos.x = w->scene->size.h;
		// if (w->scene->pos.y > w->scene->size.w)
		// 	w->scene->pos.y = w->scene->size.w;
		refresh(w);
	}
	else if (keycode == LEFT)
	{
		rotation(&w->scene->dir, THETA);
		rotation(&w->scene->plane, THETA);
		refresh(w);
	}
	else if (keycode == RIGHT)
	{
		rotation(&w->scene->dir, -THETA);
		rotation(&w->scene->plane, -THETA);
		refresh(w);
	}
	else if (keycode == (AZERTY ? KEY_S : KEY_S))
	{
		start = clock();
		save_bmp(screenshot_datetime(filename), w->img->data, w->scene->resolution);
		end = clock();
		printf("save_img:\t%fs\n",((double) (end - start)) / CLOCKS_PER_SEC);
	}
	return (0);
}