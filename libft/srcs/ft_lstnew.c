/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 01:09:34 by thule             #+#    #+#             */
/*   Updated: 2021/12/07 14:01:30 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;

	new = (t_list *) malloc(sizeof(t_list));
	if (new)
	{
		if (!content)
		{
			new->content = NULL;
			content_size = 0;
		}
		else
		{
			new->content = (void *) malloc(content_size);
			if (!new->content)
			{
				ft_memdel((void *)new);
				return (NULL);
			}
			ft_memcpy(new->content, content, content_size);
		}
		new->content_size = content_size;
		new->next = NULL;
	}
	return (new);
}
