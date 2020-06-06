/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 00:16:37 by hthomas           #+#    #+#             */
/*   Updated: 2020/06/07 00:17:11 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_map_color(char **map, t_couple couple, t_couple size)
{
	printf("couple%d:%d\n", couple.h, couple.w);
	int i = 0;
	int j;
	while (i < size.h)
	{
		j=0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				printf("\033[48;5;39m");
				printf("%c", map[i][j]);
				printf("\033[m"); 
			}
			else if (map[i][j] == '8')
			{
				printf("\033[48;5;213m");
				printf("%c", map[i][j]);
				printf("\033[m"); 
			}
			else
				printf("%c", map[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}
	sleep(1);
}

int		recurs_map(char **map, t_couple c, t_couple size)
{
	int ok[4];
	
	ok[0] = 1;
	ok[1] = 1;
	ok[2] = 1;
	ok[3] = 1;
	//print_map_color(map, couple, size);
	map[c.h][c.w] = '0';
	if (!c.h || !c.w || c.h == size.h - 1 || c.w == size.w - 1)
		return (0);
	c.h -= 1;
	if (map[c.h][c.w] == '8')
		ok[0] = recurs_map(map, c, size);
	c.h += 1;
	c.w -= 1;
	if (map[c.h][c.w] == '8')
		ok[1] = recurs_map(map, c, size);
	c.w += 1;
	c.h += 1;
	if (map[c.h][c.w] == '8')
		ok[2] = recurs_map(map, c, size);
	c.h -= 1;
	c.w += 1;
	if (map[c.h][c.w] == '8')
		ok[3] = recurs_map(map, c, size);
	return (ok[0] && ok[1] && ok[2] && ok[3]);
}

void		check_map(char **map, t_pos pos, t_couple size)
{
	t_couple	couple;
	
	couple.h = (int)pos.x;
	couple.w = (int)pos.y;
	if (!recurs_map(map, couple, size))
		print_err_and_exit("Map not closed", PARSE_ERROR);
}
