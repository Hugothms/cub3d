/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 00:16:37 by hthomas           #+#    #+#             */
/*   Updated: 2020/07/01 12:40:31 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** void	print_map_color(char **map, t_2int couple, t_2int size)
** {
** 	print("couple%d:%d\n", couple.h, couple.w);
** 	int	i = 0;
** 	int	j;
** 	while (i < size.h)
** 	{
** 		j=0;
** 		while (map[i][j])
** 		{
** 			if (map[i][j] == '0')
** 			{
** 				print("\033[48;5;39m");
** 				print("%c", map[i][j]);
** 				print("\033[m");
** 			}
** 			else if (map[i][j] == '8')
** 			{
** 				print("\033[48;5;213m");
** 				print("%c", map[i][j]);
** 				print("\033[m");
** 			}
** 			else
** 				print("%c", map[i][j]);
** 			j++;
** 		}
** 		i++;
** 		print("\n");
** 	}
** 	sleep(1);
** }
*/

void	check_case(char **map, t_2int c, t_2int size, int *ok)
{
	if (map[c.h][c.w] == '8')
		*ok = recurs_map(map, c, size);
	else if (map[c.h][c.w] == ' ')
		*ok = 0;
}

int		recurs_map(char **map, t_2int c, t_2int size)
{
	int	ok[4];

	ok[0] = 1;
	ok[1] = 1;
	ok[2] = 1;
	ok[3] = 1;
	map[c.h][c.w] = '0';
	if (!c.h || !c.w || c.h == size.h - 1 || c.w == size.w - 1)
		return (0);
	c.h -= 1;
	check_case(map, c, size, &ok[0]);
	c.h += 1;
	c.w -= 1;
	check_case(map, c, size, &ok[1]);
	c.w += 1;
	c.h += 1;
	check_case(map, c, size, &ok[2]);
	c.h -= 1;
	c.w += 1;
	check_case(map, c, size, &ok[3]);
	return (ok[0] && ok[1] && ok[2] && ok[3]);
}

void	check_map(char **map, t_2float pos, t_2int size)
{
	t_2int	couple;

	couple.h = (int)pos.x;
	couple.w = (int)pos.y;
	if (!recurs_map(map, couple, size))
		print_err_and_exit("Map not closed", PARSE_ERROR);
}
