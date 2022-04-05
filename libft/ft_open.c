/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:11:21 by hyun-zhe          #+#    #+#             */
/*   Updated: 2021/12/14 16:24:00 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_open(char *path, int flags)
{
	if (!flags && access(path, R_OK) < 0)
		return (open("temp.txt", O_RDONLY | O_CREAT, 0644));
	if (flags && !access(path, F_OK) && access(path, W_OK) < 0)
		ft_print_error("zsh: ", 1, path, 1);
	return (open(path, flags, 0644));
}
