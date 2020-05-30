/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugothms <hugothms@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 20:08:47 by hugothms          #+#    #+#             */
/*   Updated: 2020/05/30 19:20:49 by hugothms         ###   ########.fr       */
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
	while (length-- >0)
	{
		printf("pixel\n");
		put_pixel(data, pos, color, resolution); // set the pixel at the coord x,y with the color value
		pos.h++;
	}
}

void		draw_wall(unsigned char *data, int line, t_couple delim, int wall_color, t_couple resolution)
{
	int			i;
	t_couple	pixel;
	
	i = 0;
	// printf("delim: %d:%d\nline: %d\n", delim.h, delim.w, line);
	while (i < delim.h)
	{
		pixel.h = i++;
		pixel.w = line;
		put_pixel(data, pixel, CEILING_COLOR, resolution); // set the pixel at the coord x,y with the color value
	}
	while (i < delim.w)
	{
		pixel.h = i++;
		pixel.w = line;
		put_pixel(data, pixel, wall_color, resolution); // set the pixel at the coord x,y with the color value
	}
	while (i < resolution.h)
	{
		pixel.h = i++;
		pixel.w = line;
		put_pixel(data, pixel, FLOOR_COLOR, resolution); // set the pixel at the coord x,y with the color value
	}
}



void	make_img(t_img *img, t_scene *scene)
{
	int x;

	x = 0;
	double time = 0; //time of current frame
	double oldTime = 0; //time of previous frame

	while (x < scene->resolution.w)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)scene->resolution.w - 1; //x-coordinate in camera space
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
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (scene->pos.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - scene->pos.x) * deltaDistX;
		}
		if(rayDirY < 0)
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
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if(scene->map[mapX][mapY] > 0) hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		// printf("mapX: %d\t\tmapY:%d\n", mapX, mapY);
		// printf("stepX: %d\t\tstepY:%d\n", stepX, stepY);
		// printf("rayDirX: %f\trayDirY:%f\n", rayDirX, rayDirY);
		// printf("scene->pos.x: %f\tscene->pos.y:%f\n", scene->pos.x, scene->pos.y);
		// printf("side:%d\n", side);
		if(side == 0)
			perpWallDist = (mapX - scene->pos.x + (1 - stepX) / 2.) / rayDirX;
		else
			perpWallDist = (mapY - scene->pos.y + (1 - stepY) / 2.) / rayDirY;
		// printf("res.h: %d\tperp:%f\n", scene->resolution.h, perpWallDist);
		
		//Calculate height of line to draw on screen
		int lineHeight = (scene->resolution.h / perpWallDist);
		// printf("lineHeight: %d\n", lineHeight);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + scene->resolution.h / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + scene->resolution.h / 2;
		if(drawEnd >= scene->resolution.h)
			drawEnd = scene->resolution.h - 1;

		//choose wall color
		t_rgb *color;
		switch(scene->map[mapX][mapY])
		{
			case '1':color = int_to_rgb(255,0,0);break; //red
			case '2':color = int_to_rgb(255,255,0);break; //green
			case '3':color = int_to_rgb(255,0,255); break; //blue
			case '4':color = int_to_rgb(0,255,0);break; //white
			default: color = int_to_rgb(0,0,255); break; //yellow
		}
		// //give x and y sides different brightness
		// if(side == 1) {color = color / 2;}

		//draw the pixels of the stripe as a vertical line
//		verLine(x, drawStart, drawEnd, color);
		t_couple delim;
		delim.h = drawStart < scene->resolution.h ? drawStart : 0;
		delim.w = drawEnd < scene->resolution.h ? drawEnd : 0;
		draw_wall(img->data, x, delim, rgb_to_int(*color), scene->resolution);
		free(color);

		x++;
	}
}