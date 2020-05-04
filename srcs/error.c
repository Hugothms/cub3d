/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugothms <hugothms@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 18:54:35 by hthomas           #+#    #+#             */
/*   Updated: 2020/05/04 11:39:28 by hugothms         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_err_and_exit(char *str, int err)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(" (exit code: ", STDERR_FILENO);
	ft_putnbr_fd(err, STDERR_FILENO);
	ft_putstr_fd(")\n", STDERR_FILENO);
	exit(err);
}
