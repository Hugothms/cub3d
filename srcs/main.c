/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugothms <hugothms@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 09:32:30 by hugothms          #+#    #+#             */
/*   Updated: 2020/05/30 19:07:09 by hugothms         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_scene(t_scene *scene)
{
	int i;
	
	i = 0;
	while (i < scene->size.h)
		free(scene->map[i++]);
	free(scene->map);
	i = 0;
	while (i < NB_TEXTURES)
		free(scene->textures[i++]);
	free(scene->textures);
	free(scene->ceilling_color);
	free(scene->floor_color);
}

int		close_function(const t_window *w)
{
	mlx_clear_window(w->mlx->mlx_ptr, w->mlx->win_ptr);
	mlx_destroy_window(w->mlx->mlx_ptr, w->mlx->win_ptr);
	//free(mlx);
	free_scene(w->scene);
	exit(0);
}

int	refresh(const t_window *w)
{
	printf("pos %.01f:%.01f\torient %.01f:%.01f\tplane %.01f:%.01f\n", w->scene->pos.x, w->scene->pos.y, w->scene->dir.x, w->scene->dir.y, w->scene->plane.x, w->scene->plane.y);
	check_key_on(w->scene);
	make_img(w->img, w->scene);
	mlx_clear_window(w->mlx->mlx_ptr, w->mlx->win_ptr);
	mlx_put_image_to_window(w->mlx->mlx_ptr, w->mlx->win_ptr, w->img->img_ptr, 0, 0);
	return (0);
}

t_mlx	*malloc_mlx_init(void)
{
	t_mlx		*mlx;

	if (!(mlx = malloc(sizeof(*mlx))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	if (!(mlx->mlx_ptr = mlx_init()))
		print_err_and_exit("Minilibx error", MLX_ERROR);
	return (mlx);
}

t_img	*init_img(t_mlx *mlx, t_couple *resolution)
{
	t_img		*img;
	int			w;
	int			h;

	if (!(img = malloc(sizeof(*img))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	mlx_get_screen_size(mlx->mlx_ptr, &w, &h);
	if (w < resolution->w)
		resolution->w = w;
	if (h < resolution->h)
		resolution->h = h;
	if (!(img->img_ptr = mlx_new_image(mlx->mlx_ptr, resolution->w, resolution->h)))
		print_err_and_exit("Minilibx error", MLX_ERROR);
	if (!(img->data = (unsigned char*)mlx_get_data_addr(img->img_ptr, &(img->bits_per_pixel), &(img->size_line), &(img->endian))))
		print_err_and_exit("Minilibx error", MLX_ERROR);
	return (img);
}

void	get_controls_loop(t_mlx *mlx, t_img *img, t_scene *scene)
{
	t_window	*window;

	if(!(window = malloc(sizeof(*window))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	window->mlx = mlx;
	window->img = img;
	window->scene = scene;
	printf("get_controls_loop\n");
	mlx_hook(mlx->win_ptr, 17, 1L<<17, close_function, window); //linux close	
		mlx_hook(mlx->win_ptr, 3, 1L << 1, key_release, &scene->move);
		mlx_hook(mlx->win_ptr, 2, 1L << 0, key_function, window);
	//mlx_key_hook(mlx->win_ptr, key_function, window);
	ft_putstr("before loop\n");
	// mlx_loop_hook(mlx->mlx_ptr, refresh, window);
	make_img(window->img, window->scene);
	mlx_put_image_to_window(window->mlx->mlx_ptr, window->mlx->win_ptr, window->img->img_ptr, 0, 0);
	mlx_loop(mlx->mlx_ptr);
}

int		main(const int argc, const char *argv[])
{
	t_scene		*scene;
	t_mlx		*mlx;
	t_img		*img;
	
	clock_t start, end;
	start = clock();
	scene = get_scene(argc, argv);
	end = clock();
	printf("\nget_scene:\t%fs\n",((double) (end - start)) / CLOCKS_PER_SEC);
	start = clock();
	mlx = malloc_mlx_init();
	end = clock();
	printf("malloc_mlx_init:%fs\n",((double) (end - start)) / CLOCKS_PER_SEC);
	start = clock();
	img = init_img(mlx, &scene->resolution);
	end = clock();
	printf("init_img:\t%fs\n",((double) (end - start)) / CLOCKS_PER_SEC);
	if (argc == 2)
	{
		char *title = ft_strdup(argv[1]);
		if (!(mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, scene->resolution.w, scene->resolution.h, title)))
			print_err_and_exit("Minilibx error", MLX_ERROR);
		free(title);
		get_controls_loop(mlx, img, scene);
	}
	else if (argc == 3)
	{
		char filename[35];
		make_img(img, scene);
		start = clock();
		save_bmp(screenshot_datetime(filename), img->data, scene->resolution);
		end = clock();
		printf("save_img:\t%fs\n",((double) (end - start)) / CLOCKS_PER_SEC);
		free_scene(scene);
	}
	return (0);
}
