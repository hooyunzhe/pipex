/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 12:16:04 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/02/21 11:30:26 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_error(char *message, int print_error, char *path, int err)
{
	if (err || (errno && !access("temp.txt", F_OK)))
	{
		write(2, message, ft_strlen(message));
		if (print_error)
			write(2, strerror(errno), ft_strlen(strerror(errno)));
		if (path)
		{
			write(2, ": ", 2);
			write(2, path, ft_strlen(path));
		}
		write(2, "\n", 1);
	}
	if (errno)
	{
		if (!access("temp.txt", F_OK))
			unlink("temp.txt");
		exit(errno);
	}
	return (0);
}
