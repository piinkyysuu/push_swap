/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 21:48:14 by thule             #+#    #+#             */
/*   Updated: 2022/03/29 22:02:43 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

static int	count_len(unsigned long long int n)
{
	int	count;

	count = 0;
	if (n <= 0)
	{
		n = -n;
		count++;
	}
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_ulltoa(unsigned long long int n)
{
	char	*str;
	int		len;

	str = NULL;
	len = count_len(n) - 1;
	str = ft_strnew(len + 1);
	if (str)
	{
		while (len >= 0)
		{
			str[len] = (n % 10) + 48;
			n = n / 10;
			len--;
		}
	}
	return (str);
}
