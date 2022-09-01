/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimize_ops.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 20:18:05 by thle              #+#    #+#             */
/*   Updated: 2022/09/01 18:46:50 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void change_op(t_op *first, t_op *second)
{
	second->op = "0";
	if (first->operation == SWAP)
		first->op = "ss";
	else if (first->operation == ROT)
		first->op = "rr";
	else if (first->operation == R_ROT)
		first->op = "rrr";
}

void combine_op(t_op *first, t_op *second)
{
	t_op *second_head;
	t_op *first_tail;

	second_head = second;
	first_tail = NULL;
	while (second && first && second->stack != first->stack)
	{
		while (first && second->op[0] != '0')
		{
			if (first->next == NULL)
				first_tail = first;
			if (first->operation == second->operation && first->op[0] != '0')
			{
				change_op(first, second);
				first = first->next;
				break;
			}
			first = first->next;
		}
		second = second->next;
	}
	link_two_op_lists(first, first_tail, second_head);
}

void cancel_push(t_op *first, t_op *second)
{
	t_op *second_head;
	t_op *first_tail;

	second_head = second;
	first_tail = NULL;
	while (second && first && second->stack != first->stack)
	{
		if (first->next == NULL)
			first_tail = first;
		second->op = "0";
		first->op = "0";
		second = second->next;
		first = first->next;
	}
	link_two_op_lists(first, first_tail, second_head);
}

void cancel_rotate_helper(t_op *op, char *counter)
{
	t_op *tmp = op;

	op = op->next;
	while (op)
	{
		if (!ft_strcmp(op->op, counter))
		{
			tmp->op = "0";
			op->op = "0";
			return;
		}
		else if (op->stack == tmp->stack)
			return;
		op = op->next;
	}
}

void cancel_rotate(t_op *op)
{
	t_op *tmp;

	tmp = op;
	while (tmp)
	{
		if (!ft_strcmp("ra", tmp->op))
			cancel_rotate_helper(tmp, "rra");
		else if (!ft_strcmp("rb", tmp->op))
			cancel_rotate_helper(tmp, "rrb");
		else if (!ft_strcmp("rra", tmp->op))
			cancel_rotate_helper(tmp, "ra");
		else if (!ft_strcmp("rrb", tmp->op))
			cancel_rotate_helper(tmp, "rb");
		tmp = tmp->next;
	}
}
