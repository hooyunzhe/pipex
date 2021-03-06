/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freestrarrs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:07:31 by hyun-zhe          #+#    #+#             */
/*   Updated: 2021/12/10 11:23:10 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freestrarrs(char ***arr)
{
	int	i;

	i = 0;
	while (arr[i])
		ft_freestrs(arr[i++]);
	free(arr);
}
