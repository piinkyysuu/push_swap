/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:57:55 by thle              #+#    #+#             */
/*   Updated: 2021/11/11 17:47:23 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	int	index;

	index = ft_strlen(dest);
	while (*src)
	{
		dest[index] = *src;
		index++;
		src++;
	}
	dest[index] = '\0';
	return (dest);
}
