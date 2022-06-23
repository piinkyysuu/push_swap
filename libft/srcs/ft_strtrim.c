/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 00:42:58 by thule             #+#    #+#             */
/*   Updated: 2021/12/05 21:22:44 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	else
		return (0);
}

char	*ft_strtrim(char const *s)
{
	size_t	start;
	size_t	end;
	size_t	index;
	char	*new;

	new = NULL;
	start = 0;
	end = 0;
	if (*s)
	{
		end = ft_strlen(s) - 1;
		while (ft_space(s[start]) && (s[start] != '\0'))
			start++;
		while (ft_space(s[end]) && start != ft_strlen(s))
			end--;
	}
	new = ft_strnew(end - start + 1);
	if (new)
	{
		index = 0;
		while (start <= end)
			new[index++] = s[start++];
	}
	return (new);
}
