/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupdate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:14:05 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/01/13 16:04:41 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strupdate(char *s1, const char *s2)
{
	int		i;
	int		j;
	int		len;
	char	*newstr;

	if (s1)
	{
		i = 0;
		len = ft_strlen(s1) + ft_strlen(s2);
		newstr = malloc((len * sizeof(char)) + 1);
		if (!newstr)
			return (NULL);
		j = 0;
		while (s1[j])
			newstr[i++] = s1[j++];
		j = 0;
		while (s2[j])
			newstr[i++] = s2[j++];
		newstr[i] = 0;
		free(s1);
		s1 = NULL;
	}
	else
		newstr = ft_strdup(s2);
	return (newstr);
}
