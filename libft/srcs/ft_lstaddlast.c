/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddlast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 21:16:07 by thule             #+#    #+#             */
/*   Updated: 2021/12/06 14:31:03 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddlast(t_list **alst, t_list *new)
{
	t_list	*last;

	last = *alst;
	if (!(*alst))
	{
		*alst = new;
	}
	else
	{
		while (last->next != NULL)
		{
			last = last->next;
		}
		last->next = new;
	}
}
