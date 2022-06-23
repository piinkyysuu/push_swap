/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 23:49:16 by thule             #+#    #+#             */
/*   Updated: 2021/11/28 00:09:48 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strequ(char const *s1, char const *s2)
{
	if (s1 && s2)
	{
		if (ft_strlen(s1) != ft_strlen(s2))
			return (0);
		return (ft_strnequ(s1, s2, ft_strlen(s1)));
	}
	return (0);
}
