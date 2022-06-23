/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:24:24 by thle              #+#    #+#             */
/*   Updated: 2021/11/22 14:52:18 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;

	dst_len = ft_strlen(dst);
	if (dstsize - dst_len <= 0 || dstsize <= dst_len)
		return (ft_strlen(src) + dstsize);
	else
	{
		ft_strncat(dst, src, dstsize - dst_len - 1);
	}
	return (ft_strlen(src) + dst_len);
}
