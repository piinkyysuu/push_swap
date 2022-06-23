/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 23:07:10 by thule             #+#    #+#             */
/*   Updated: 2021/11/16 23:28:06 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*mem;
	size_t	index;

	index = 0;
	mem = (char *)malloc(size);
	if (mem)
	{
		while (index <= size)
		{
			mem[index] = 0;
			index++;
		}
		return (mem);
	}
	else
	{
		return (NULL);
	}
}
