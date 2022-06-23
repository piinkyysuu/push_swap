/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 00:32:40 by thule             #+#    #+#             */
/*   Updated: 2021/12/27 19:37:45 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	index;
	char	*new;

	new = NULL;
	index = 0;
	if (s1 && s2)
	{
		new = (char *) malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
		if (new)
		{
			while (*s1)
			{
				new[index++] = *s1;
				s1++;
			}
			while (*s2)
			{
				new[index++] = *s2;
				s2++;
			}
			new[index] = '\0';
		}
	}
	return (new);
}
