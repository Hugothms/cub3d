/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 10:43:06 by hthomas           #+#    #+#             */
/*   Updated: 2020/06/07 00:29:04 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*file_header_bmp(const int filesize)
{
	char	*bmpfileheader;

	if (!(bmpfileheader = malloc(14 * sizeof(char))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	ft_memcpy(bmpfileheader, (char[]){'B','M', 0, 0, 0, 0, 0, 0, 0, 0,\
										54,0, 0, 0}, 14);
	bmpfileheader[2] = filesize;
	bmpfileheader[3] = filesize >> 8;
	bmpfileheader[4] = filesize >> 16;
	bmpfileheader[5] = filesize >> 24;
	return (bmpfileheader);
}

char	*info_header_bmp(const t_couple resolution)
{
	char	*bmpinfoheader;

	if (!(bmpinfoheader = malloc(40 * sizeof(char))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	ft_memcpy(bmpinfoheader, (char[]){40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
	1,0, 32,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
	0, 0, 0, 0}, 40);
	bmpinfoheader[4] = resolution.w;
	bmpinfoheader[5] = resolution.w >> 8;
	bmpinfoheader[6] = resolution.w >> 16;
	bmpinfoheader[7] = resolution.w >> 24;
	bmpinfoheader[8] = resolution.h;
	bmpinfoheader[9] = resolution.h >> 8;
	bmpinfoheader[10] = resolution.h >> 16;
	bmpinfoheader[11] = resolution.h >> 24;
	return (bmpinfoheader);
}

void			write_data(const int f, const char *data, t_couple r)
{
	int			line;

	line = r.h;
	while (--line + 1)
		write(f, data + r.w * line * 4, r.w * 4);
}

void			save_bmp(const char *fn, const char *data, const t_couple r)
{
	int		filesize;
	int		fd;
	char	*bmpfileheader;
	char	*bmpinfoheader;

	filesize = 14 + 40 + 3 * r.w * r.h;
	fd = open(fn, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0755);
	bmpfileheader = file_header_bmp(filesize);
	write(fd, bmpfileheader, 14);
	free(bmpfileheader);
	bmpinfoheader = info_header_bmp(r);
	write(fd, bmpinfoheader, 40);
	free(bmpinfoheader);
	write_data(fd, data, r);
	close(fd);
}
