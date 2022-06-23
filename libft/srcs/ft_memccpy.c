/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:06:45 by thle              #+#    #+#             */
/*   Updated: 2021/12/06 17:42:48 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (src == dst)
		return (dst);
	while (n)
	{
		*d = *s;
		if (*d == (unsigned char)c)
		{
			return (d + 1);
		}
		d++;
		s++;
		n--;
	}
	return (NULL);
}
