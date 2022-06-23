/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 01:42:47 by thule             #+#    #+#             */
/*   Updated: 2022/04/19 23:37:44 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_len(long n)
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

// static long	ft_abs(long n)
// {
// 	if (n < 0)
// 	{
// 		n = -n;
// 	}
// 	return (n);
// }

char	*ft_itoa(int n)
{
	int		len;
	char	*new;
	int		sign;

	len = count_len(n) - 1;
	new = ft_strnew(len + 1);
	sign = 0;
	if (new)
	{
		if (n < 0)
			sign = 1;
		while (len >= 1)
		{
			new[len] = (ft_abs(n) % 10) + 48;
			n = n / 10;
			len--;
		}
		if (sign)
			new[len] = '-';
		else
			new[len] = (ft_abs(n) % 10) + 48;
		return (new);
	}
	return (NULL);
}
