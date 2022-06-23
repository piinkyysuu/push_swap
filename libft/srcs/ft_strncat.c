/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:57:40 by thle              #+#    #+#             */
/*   Updated: 2021/11/12 13:58:13 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t	index;

	index = ft_strlen(dest);
	while (*src && n)
	{
		dest[index] = *src;
		index++;
		src++;
		n--;
	}
	dest[index] = '\0';
	return (dest);
}
