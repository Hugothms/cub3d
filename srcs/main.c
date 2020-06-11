/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 09:32:30 by hthomas           #+#    #+#             */
/*   Updated: 2020/06/11 17:46:55 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_mlx	*malloc_mlx_init(void)
{
	t_mlx		*mlx;

	if (!(mlx = malloc(sizeof(*mlx))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	if (!(mlx->mlx_ptr = mlx_init()))
		print_err_and_exit("Minilibx error", MLX_ERROR);
	return (mlx);
}

t_img	*init_img(t_mlx *mlx, t_2int *res)
{
	t_img		*img;
	int			w;
	int			h;

	if (!(img = malloc(sizeof(*img))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	mlx_get_screen_size(mlx->mlx_ptr, &w, &h);
	if (w < res->w)
		res->w = w;
	if (h < res->h)
		res->h = h;
	if (!(img->img_ptr = mlx_new_image(mlx->mlx_ptr, res->w, res->h)))
		print_err_and_exit("Minilibx error", MLX_ERROR);
	if (!(img->data = mlx_get_data_addr(img->img_ptr, &(img->bits_per_pixel), &(img->size_line), &(img->endian))))
		print_err_and_exit("Minilibx error", MLX_ERROR);
	return (img);
}

void	get_controls_loop(t_mlx *mlx, t_img *img, t_scene *scene)
{
	t_window	*window;

	if (!(window = malloc(sizeof(*window))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	window->mlx = mlx;
	window->img = img;
	window->s = scene;
	mlx_hook(mlx->win_ptr, 17, 1L << 17, close_function, window); //linux close
	mlx_hook(mlx->win_ptr, 2, 1L << 0, key_function, window);
	mlx_hook(mlx->win_ptr, 3, 1L << 1, key_release, &scene->move);
	//mlx_key_hook(mlx->win_ptr, key_function, window);
	make_img(window->img, window->s);
	mlx_put_image_to_window(window->mlx->mlx_ptr, window->mlx->win_ptr, window->img->img_ptr, 0, 0);
	//mlx_loop_hook(mlx->mlx_ptr, refresh, window);
	mlx_loop(mlx->mlx_ptr);
}

void	start_game_loop(t_scene *scene, t_mlx *mlx, t_img *img, const char *str)
{
	char	*title = ft_strdup(str);

	if (!(mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, scene->res.w, scene->res.h, title)))
		print_err_and_exit("Minilibx error", MLX_ERROR);
	free(title);
	get_controls_loop(mlx, img, scene);
}

void	save(t_scene *scene, t_img *img)
{
	char	filename[35];

	make_img(img, scene);
	save_bmp(screenshot_datetime(filename), img->data, scene->res);
	free_scene(scene);
}

int		main(const int argc, const char *argv[])
{
	t_scene		*scene;
	t_mlx		*mlx;
	t_img		*img;
	clock_t		start, end;

	start = clock();
	scene = get_scene(argc, argv);
	end = clock();
	// printf("\nget_scene:\t%fs\n", ((double)(end - start)) / CLOCKS_PER_SEC);
	start = clock();
	mlx = malloc_mlx_init();
	end = clock();
	// printf("malloc_mlx_init:%fs\n", ((double)(end - start)) / CLOCKS_PER_SEC);
	start = clock();
	img = init_img(mlx, &scene->res);
	end = clock();
	// printf("init_img:\t%fs\n", ((double)(end - start)) / CLOCKS_PER_SEC);
	//parse_textures(mlx, scene);
	if (argc == 2)
		start_game_loop(scene, mlx, img, argv[1]);
	else if (argc == 3)
		save(scene, img);
	return (0);
}
