/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_op_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:27:38 by thle              #+#    #+#             */
/*   Updated: 2022/09/12 19:02:43 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

static void	update_op_node(t_op *node, char *op)
{
	int	len;

	len = ft_strlen(op);
	node->len = len;
	node->op = op;
	if (len == 3)
		node->operation = R_ROT;
	else
	{
		if (op[0] == 's')
			node->operation = SWAP;
		else if (op[0] == 'r')
			node->operation = ROT;
		else
			node->operation = PUSH;
	}
	if (len > 0)
		node->stack = op[len - 1];
	node->next = NULL;
}

void	append_op_list(t_op **head, char *op)
{
	t_op	*new;
	t_op	*tmp;

	tmp = *head;
	new = (t_op *)malloc(sizeof(t_op));
	if (!new)
		exit(1);
	update_op_node(new, op);
	if (!tmp)
	{
		*head = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
