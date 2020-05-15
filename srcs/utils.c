/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugothms <hugothms@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 10:24:22 by hthomas           #+#    #+#             */
/*   Updated: 2020/05/15 20:31:51 by hugothms         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*screenshot_datetime(char res[])
{
	time_t		t;
	struct tm	tm;
	char		*tmp;

	t = time(NULL);
	tm = *localtime(&t);
	ft_memcpy(res, "Screenshot YYYY-MM-DD hh:mm:ss.bmp", 35);
	tmp = ft_itoa_width(tm.tm_year + 1900, 4);
	ft_memcpy(res + 11, tmp, 4);
	free(tmp);
	tmp = ft_itoa_width(tm.tm_mon + 1, 2);
	ft_memcpy(res + 16, tmp, 2);
	free(tmp);
	tmp = ft_itoa_width(tm.tm_mday, 2);
	ft_memcpy(res + 19, tmp, 2);
	free(tmp);
	tmp = ft_itoa_width(tm.tm_hour, 2);
	ft_memcpy(res + 22, tmp, 2);
	free(tmp);
	tmp = ft_itoa_width(tm.tm_min, 2);
	ft_memcpy(res + 25, tmp, 2);
	free(tmp);
	tmp = ft_itoa_width(tm.tm_sec, 2);
	ft_memcpy(res + 28, tmp, 2);
	free(tmp);
	return (*res);
}

int     ft_tab_size(char **tab)
{
    int i;

    if (!tab)
        return (0);
    i = 0;
    while (tab[i])
        i++;
    return (i);
}

void	free_tab(void **tab)
{
	int i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	rotation(t_pos *dir, float angle)
{
	float	x;
	
	x = dir->x;
	dir->x = x * cos(angle) - dir->y * sin(angle);
	dir->y = x * sin(angle) + dir->y * cos(angle);
}
