/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 16:49:23 by hthomas           #+#    #+#             */
/*   Updated: 2020/06/16 17:35:47 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		refresh(const t_window *w)
{
	// printf("pos %.01f:%.01f\torient %.01f:%.01f\tplane %.01f:%.01f\n", w->s->pos.x, w->s->pos.y, w->s->dir.x, w->s->dir.y, w->s->plane.x, w->s->plane.y);
	//check_key_on(w);
	make_img(w->img, w->s);
	mlx_clear_window(w->mlx->mlx_ptr, w->mlx->win_ptr);
	mlx_put_image_to_window(w->mlx->mlx_ptr, w->mlx->win_ptr, w->img->img_ptr, 0, 0);
	//mlx_put_image_to_window(w->mlx->mlx_ptr, w->mlx->win_ptr, w->s->textures[NORTH]->img_ptr, 100, 100);
	return (0);
}

int		key_release(int keycode, t_move *move)
{
	if (keycode == ARROW_UP || keycode == (AZERTY ? KEY_Z : KEY_W))
		move->up = 0;
	else if (keycode == ARROW_DOWN || keycode == KEY_S)
		move->down = 0;
	else if (keycode == (AZERTY ? KEY_A : KEY_Q))
		move->left = 0;
	else if (keycode == KEY_E)
		move->right = 0;
	else if (keycode == ARROW_LEFT || keycode == (AZERTY ? KEY_Q : KEY_A))
		move->turn_left = 0;
	else if (keycode == ARROW_RIGHT || keycode == KEY_D)
		move->turn_right = 0;
	return (0);
}

int		key_push(int keycode, t_move *move)
{
	if (keycode == ARROW_UP || keycode == (AZERTY ? KEY_Z : KEY_W))
		move->up = 1;
	else if (keycode == ARROW_DOWN || keycode == KEY_S)
		move->down = 1;
	else if (keycode == (AZERTY ? KEY_A : KEY_Q))
		move->left = 1;
	else if (keycode == KEY_E)
		move->right = 1;
	else if (keycode == ARROW_LEFT || keycode == (AZERTY ? KEY_Q : KEY_A))
		move->turn_left = 1;
	else if (keycode == ARROW_RIGHT || keycode == KEY_D)
		move->turn_right = 1;
	return (0);
}

int		key_function(const int keycode, t_window *w)
{
	char	filename[35];
	clock_t	start, end;
	float	x;

	printf("%d\n", keycode);
	key_push(keycode, &w->s->move);
	if (keycode == ESC)
		close_function(w);
	if (keycode == KEY_F)
	{
		start = clock();
		save_bmp(screenshot_datetime(filename), w->img->data, w->s->res);
		end = clock();
		printf("save_img:\t%fs\n", ((double)(end - start)) / CLOCKS_PER_SEC);
	}
	if (w->s->move.up)
		move_up(w);
	if (w->s->move.down)
		move_down(w);
	if (w->s->move.left)
		move_left(w);
	if (w->s->move.right)
		move_right(w);
	if (w->s->move.turn_left)
		turn_left(w);
	if (w->s->move.turn_right)
		turn_right(w);
	return (0);
}
