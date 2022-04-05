/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrimchr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:12:58 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/01/13 16:01:57 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrimchr(const char *str, char c)
{
	int		i;
	int		len;
	char	*newstr;

	if (!str)
		return (NULL);
	if (ft_strchr(str, c))
	{
		i = -1;
		len = ft_strlen(str) - ft_strlen(ft_strchr(str, c));
		newstr = malloc((len * sizeof(char)) + 1);
		while (str[++i] != c)
			newstr[i] = str[i];
		newstr[i] = 0;
	}
	else
		newstr = ft_strdup(str);
	return (newstr);
}
