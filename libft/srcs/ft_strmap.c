/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 23:14:39 by thule             #+#    #+#             */
/*   Updated: 2021/12/07 14:03:38 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*new;
	int		index;

	new = NULL;
	if (*s)
	{
		new = ft_strnew(ft_strlen(s));
		if (new)
		{
			index = 0;
			while (*s)
			{
				new[index] = f(*s);
				s++;
				index++;
			}
		}
	}
	return (new);
}
