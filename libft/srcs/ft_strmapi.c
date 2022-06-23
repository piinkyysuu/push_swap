/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 23:38:41 by thule             #+#    #+#             */
/*   Updated: 2021/12/07 14:04:58 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
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
				new[index] = f(index, *s);
				s++;
				index++;
			}
		}
	}
	return (new);
}
