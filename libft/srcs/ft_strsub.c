/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 00:15:36 by thule             #+#    #+#             */
/*   Updated: 2021/12/27 20:36:50 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	index;

	if (s || start > ft_strlen(s))
	{
		index = 0;
		new = (char *) malloc(len + 1);
		if (new)
		{
			while (len)
			{
				new[index] = s[start];
				start++;
				index++;
				len--;
			}
			new[index] = '\0';
			return (new);
		}
	}
	return (NULL);
}
