/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugothms <hugothms@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 20:08:47 by hugothms          #+#    #+#             */
/*   Updated: 2020/06/04 20:01:45 by hugothms         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		put_pixel(unsigned char *data, t_couple pixel, int color, t_couple resolution)
{
	int	(*tab)[resolution.w][1]; // prepare the cast

	tab = (void *)data; // cast for change 1 dimension array to 2 dimensions
	*tab[pixel.h][pixel.w] = color; // set the pixel at the coord x,y with the color value
}

void		draw_vertical_line(unsigned char *data, t_couple pos, int length, int color, t_couple resolution)
{
	while (length-- > 0)
	{
		put_pixel(data, pos, color, resolution); // set the pixel at the coord x,y with the color value
		pos.h++;
	}
}

void		draw_line(unsigned char *data, t_scene *scene, t_draw draw, int color, t_couple resolution)
{
	int ymax;
	int xmax;
	t_pos	pos;

	ymax = 20 + scene->size.h * SIZE_MINIMAP;
	xmax = 20 + ft_strlen(scene->map[(int)scene->pos.x]) * SIZE_MINIMAP;
	// printf("draw%d:%d\n", draw.start.h,draw.start.w );
	// printf("max%d:%d\n", ymax, xmax );
	pos.x = draw.start.h;
	pos.y = draw.start.w;
	// while (draw.start.h > 20 && draw.start.h < ymax && draw.start.w > 20 && draw.start.w < xmax)
	int i = 20;
	while (i--)
	{
		//printf("%d:%d\n", draw.start.h, draw.start.w);
		put_pixel(data, draw.start, color, resolution); // set the pixel at the coord x,y with the color value
		pos.x += draw.end.y;
		pos.y += draw.end.x;
		draw.start.h = pos.x;
		draw.start.w = pos.y;
	}	
}

void		draw_square(unsigned char *data, t_couple pos, int length, int color, t_couple resolution)
{
	int i;
	
	i = 0;
	while (i < length)
	{
		draw_vertical_line(data, pos, length, color, resolution); // set the pixel at the coord x,y with the color value
		pos.w++;
		i++;
	}
}

void		draw_wall(unsigned char *data, int line, t_couple delim, int color, t_couple resolution)
{
	int			i;
	t_couple	pixel;
	
	pixel.w = line;
	// printf("delim: %d:%d\nline: %d\n", delim.h, delim.w, line);
	// i = 0;
	pixel.h = 0;
	draw_vertical_line(data, pixel, delim.h, CEILING_COLOR, resolution);
	pixel.h += delim.h;
	draw_vertical_line(data, pixel, delim.w - delim.h, color, resolution);
	pixel.h += delim.w - delim.h;
	draw_vertical_line(data, pixel, resolution.h - delim.w - 1, FLOOR_COLOR, resolution);
	// while (i < delim.h)
	// {
	// 	pixel.h = i++;
	// 	put_pixel(data, pixel, CEILING_COLOR, resolution); // set the pixel at the coord x,y with the color value
	// }
	// while (i < delim.w)
	// {
	// 	pixel.h = i++;
	// 	put_pixel(data, pixel, wall_color, resolution); // set the pixel at the coord x,y with the color value
	// }
	// while (i < resolution.h)
	// {
	// 	pixel.h = i++;
	// 	put_pixel(data, pixel, FLOOR_COLOR, resolution); // set the pixel at the coord x,y with the color value
	// }
}

void 	draw_minimap(t_img *img, t_scene *scene)
{
	int col;
	int line;
	int len;
	t_couple pos;

	col = 0;
	while (col < scene->size.h)
	{
		line = 0;
		len = ft_strlen(scene->map[col]);
		while (line < len)
		{
			if (scene->map[col][line] != '0')
			{
				pos.w = 20 + line * SIZE_MINIMAP;
				pos.h = 20 + col * SIZE_MINIMAP;
				draw_square(img->data, pos, SIZE_MINIMAP, 16777215, scene->res);
			}
			line++;
		}
		col++;
	}
}

void	make_img(t_img *img, t_scene *scene)
{
	int x;

	x = 0;
	while (x < scene->res.w)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)scene->res.w - 1; //x-coordinate in camera space
		double rayDirX = scene->dir.x + scene->plane.x * cameraX;
		double rayDirY = scene->dir.y + scene->plane.y * cameraX;
		int mapX = (int)scene->pos.x;
		int mapY = (int)scene->pos.y;
		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;
		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;
		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (scene->pos.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - scene->pos.x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (scene->pos.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - scene->pos.y) * deltaDistY;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				if (rayDirX > 0)
					side = 0;
				else
					side = 2;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				if (rayDirY > 0)
					side = 1;
				else
					side = 3;
			}
			//Check if ray has hit a wall
			// printf("map%d:%d\n", mapX, mapY);
			if (scene->map[mapX][mapY] != '0')
				hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		// printf("mapX: %d\t\tmapY:%d\n", mapX, mapY);
		// printf("stepX: %d\t\tstepY:%d\n", stepX, stepY);
		// printf("rayDirX: %f\trayDirY:%f\n", rayDirX, rayDirY);
		// printf("scene->pos.x: %f\tscene->pos.y:%f\n", scene->pos.x, scene->pos.y);
		// printf("side:%d\n", side);
		if (side % 2 == 0)
			perpWallDist = (mapX - scene->pos.x + (1 - stepX) / 2.) / rayDirX;
		else
			perpWallDist = (mapY - scene->pos.y + (1 - stepY) / 2.) / rayDirY;
		// printf("res.h: %d\tperp:%f\n", scene->resolution.h, perpWallDist);
		
		//Calculate height of line to draw on screen
		int lineHeight = (scene->res.h / perpWallDist);
		// printf("lineHeight: %d\n", lineHeight);
		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + scene->res.h / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + scene->res.h / 2;
		if (drawEnd >= scene->res.h)
			drawEnd = scene->res.h - 1;
		//choose wall color
		t_rgb *color;
		switch (side)
		{
			case 0:color = int_to_rgb(0,255,255);break;
			case 1:color = int_to_rgb(255,0,255);break;
			case 2:color = int_to_rgb(255,255,0);break;
			case 3:color = int_to_rgb(0,255,0);break;
			default: color = int_to_rgb(255,0,0); break;
		}
		// //give x and y sides different brightness
		// if (side == 1) {color = color / 2;}

		//draw the pixels of the stripe as a vertical line
//		verLine(x, drawStart, drawEnd, color);
		t_couple delim;
		delim.h = drawStart < scene->res.h ? drawStart > 0 ? drawStart : 0 : 0;
		delim.w = drawEnd < scene->res.h ? drawEnd > 0 ? drawEnd : 0 : 0;
		draw_wall(img->data, scene->res.w - x - 1, delim, rgb_to_int(*color), scene->res);
		free(color);
		
		t_draw draw;
		draw.start.w = 20 + scene->pos.y * SIZE_MINIMAP - SIZE_MINIMAP / 2;
		draw.start.h = 20 + scene->pos.x * SIZE_MINIMAP - SIZE_MINIMAP / 2;
		draw_square(img->data, draw.start, SIZE_MINIMAP, RED, scene->res);
		draw.start.w += SIZE_MINIMAP / 2;
		draw.start.h += SIZE_MINIMAP / 2;
		draw.end.x = scene->dir.y;
		draw.end.y = scene->dir.x;
		draw_line(img->data, scene, draw, RED, scene->res);
		x++;
	}
	draw_minimap(img, scene);
}