/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:53:29 by thle              #+#    #+#             */
/*   Updated: 2022/02/08 13:03:13 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned const char	*s;
	unsigned char		*d;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (dest == src || !n)
		return (dest);
	else if ((unsigned char *)d - (unsigned char *)s >= (unsigned char)n)
		return (ft_memcpy(dest, src, n));
	else
	{
		d = d + n - 1;
		s = s + n - 1;
		while (n)
		{
			*d = *s;
			d--;
			s--;
			n--;
		}
		return (dest);
	}
}
