/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 01:15:53 by thule             #+#    #+#             */
/*   Updated: 2021/12/06 17:41:21 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_delete(void *content, size_t content_size)
{
	if (content_size && content)
	{
		free(content);
	}
}

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*current;
	t_list	*next;
	t_list	*new_node;
	t_list	*head;

	current = lst;
	head = NULL;
	while (current)
	{
		next = current->next;
		current = f(current);
		new_node = ft_lstnew(current->content, current->content_size);
		if (new_node)
		{
			ft_lstaddlast(&head, new_node);
		}
		else
		{
			ft_lstdel(&head, &ft_delete);
		}
		current = next;
	}
	return (head);
}
