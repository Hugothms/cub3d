/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 15:52:54 by hthomas           #+#    #+#             */
/*   Updated: 2020/06/19 17:29:17 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_swap_double(double *a, double *b)
{
	double c;

	c = *a;
	*a = *b;
	*b = c;
}

void	sortSprites(int spriteOrder[], double spriteDistance[], int size)
{
	int swap;
	int i;

	i = 0;
	swap = 1;
	while (swap)
	{
		i = 0;
		swap = 0;
		while (i < size - 1)
		{
			if (spriteDistance[i] > spriteDistance[i + 1])
			{
				ft_swap_double(&spriteDistance[i], &spriteDistance[i + 1]);
				ft_swap(&spriteOrder[i], &spriteOrder[i + 1]);
				swap = 1;
			}
			i++;
		}
	}
}

void	do_sprite(t_img *img, t_dda *dda, t_scene *s)
{
	//SPRITE CASTING
	//sort sprites from far to close
	//arrays used to sort the sprites
	int spriteOrder[s->nb_sprite];
	double spriteDistance[s->nb_sprite];
	printf("s->nb_sprite%d\n", s->nb_sprite);
	for(int i = 0; i < s->nb_sprite; i++)
	{
		printf("i:%d\n", i);
		spriteOrder[i] = i;
		spriteDistance[i] = ((s->pos.x - s->sprite[i].x) * (s->pos.x - s->sprite[i].x) + (s->pos.y - s->sprite[i].y) * (s->pos.y - s->sprite[i].y)); //sqrt not taken, unneeded
	}
	sortSprites(spriteOrder, spriteDistance, s->nb_sprite);

	//after sorting the sprites, do the projection and draw them
	for (int i = 0; i < s->nb_sprite; i++)
	{
		//translate sprite position to relative to camera
		double spriteX = s->sprite[spriteOrder[i]].x - s->pos.x;
		double spriteY = s->sprite[spriteOrder[i]].y - s->pos.y;

		//transform sprite wits->size.h the inverse camera matrix
		// [ s->plane.x   s->dir.x ] -1                                       [ s->dir.y      -s->dir.x ]
		// [               ]       =  1/(s->plane.x*s->dir.y-s->dir.x*s->plane.y) *   [                 ]
		// [ s->plane.y   s->dir.y ]                                          [ -s->plane.y  s->plane.x ]

		double invDet = 1.0 / (s->plane.x * s->dir.y - s->dir.x * s->plane.y); //required for correct matrix multiplication

		double transformX = invDet * (s->dir.y * spriteX - s->dir.x * spriteY);
		double transformY = invDet * (-s->plane.y * spriteX + s->plane.x * spriteY); //this is actually the depts->size.h inside the screen, that what Z is in 3D

		int spriteScreenX = (int)((s->size.w / 2) * (1 + transformX / transformY));

		//calculate height of the sprite on screen
		int spriteHeight = abs((int)(s->size.h / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + s->size.h / 2;
		if (drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + s->size.h / 2;
		if (drawEndY >= s->size.h)
			drawEndY = s->size.h - 1;

		//calculate widts->size.h of the sprite
		int spriteWidth = abs((int)(s->size.h / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= s->size.w)
			drawEndX = s->size.w - 1;

		//loop througs->size.h every vertical stripe of the sprite on screen
		for (int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * s->textures[SPRITE]->size.w / spriteWidth) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) dda->perpWallDist, wits->size.h perpendicular distance
			if (transformY > 0 && stripe > 0 && stripe < s->size.w && transformY < dda->perpWallDist[stripe])
			{
				for (int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
				{
					int d = (y)*256 - s->size.h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
					int texY = ((d * s->textures[SPRITE]->size.h) / spriteHeight) / 256;
					int color = s->textures[SPRITE]->data[s->textures[SPRITE]->size.w * texY + texX]; //get current color from the texture
					t_2int pixel;
					pixel.w = y;
					pixel.h = stripe;
					if ((color & 0x00FFFFFF) != 0)
						put_texture(img->data, pixel, s->textures[SPRITE]->data, s->res, s->textures[SPRITE]->size.w * texY + texX); //paint pixel if it isn't black, black is the invisible color
				}
			}
		}
	}
}
