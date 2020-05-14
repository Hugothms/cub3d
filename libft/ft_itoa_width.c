/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_width.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugothms <hugothms@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:56:15 by hthomas           #+#    #+#             */
/*   Updated: 2020/05/14 13:45:34 by hugothms         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_width(int nb, int width)
{
	char	*res;
	char	*tmp;
	int		diff;
	int		i;

	if (!(res = malloc((width + 1) * sizeof(char))))
		return (NULL);
	diff = width - ft_nbrlen(nb);
	if (diff > 0)
	{
		i = 0;
		while (i < diff)
			res[i++] = '0';
	}
	tmp = ft_itoa(nb);
	ft_memcpy(res + diff, tmp, ft_nbrlen(nb));
	free(tmp);
	return (res);
}