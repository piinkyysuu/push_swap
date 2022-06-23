/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:59:43 by thule             #+#    #+#             */
/*   Updated: 2022/03/22 09:14:36 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_len(long long int n)
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

static void	make_string(char *str, int len, long long int n)
{
	int	sign;

	sign = 0;
	if (n < 0)
	{
		sign = -1;
		n = -n;
	}
	while (len >= 1)
	{
		str[len] = (n % 10) + 48;
		n = n / 10;
		len--;
	}
	if (sign)
		str[len] = '-';
	else
		str[len] = (n % 10) + 48;
}

char	*ft_lltoa(long long int n)
{
	char	*str;
	int		len;

	str = NULL;
	if (n == LLONG_MIN)
		str = ft_strdup("-9223372036854775808");
	else
	{
		len = count_len(n) - 1;
		str = ft_strnew(len + 1);
		if (str)
			make_string(str, len, n);
	}
	return (str);
}
