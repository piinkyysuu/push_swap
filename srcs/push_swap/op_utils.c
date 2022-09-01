/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 16:51:58 by thle              #+#    #+#             */
/*   Updated: 2022/09/01 18:52:12 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	update_op_node(t_op *node, char *op)
{
	int	len;

	len = ft_strlen(op);
	node->len = len;
	node->op = op;
	node->stack = op[len - 1];
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

t_op	*split_instructions(t_op *first)
{
	t_op	*hold;
	int		first_char;

	hold = NULL;
	while (first && first->op[0] == '0')
		first = first->next;
	if (first)
		first_char = first->stack;
	else
		return (hold);
	while (first->next)
	{
		if (first->next->stack != first_char)
		{
			hold = first->next;
			first->next = NULL;
			break ;
		}
		first = first->next;
	}
	return (hold);
}

void	link_two_op_lists(t_op *first, t_op *first_tail, t_op *second_head)
{
	if (first_tail == NULL)
	{
		while (first->next)
			first = first->next;
		first_tail = first;
	}
	first_tail->next = second_head;
}
