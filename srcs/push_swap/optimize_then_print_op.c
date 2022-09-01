/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimize_then_print_op.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:51:07 by thle              #+#    #+#             */
/*   Updated: 2022/09/01 16:45:32 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void print_then_del_op(t_op **head)
{
	t_op *next;
	t_op *current;

	current = *head;
	while (current)
	{
		if (current->op[0] != '0')
		{
			write(1, current->op, current->len);
			write(1, "\n", 1);
		}
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;
}

void central_customization(t_op **first)
{
	t_op *second;

	if ((*first)->operation != PUSH)
		cancel_rotate(*first);
	second = split_instructions(*first);
	if (second == NULL)
		return;
	if ((*first)->operation == PUSH)
	{
		cancel_push(*first, second);
		return;
	}
	combine_op(*first, second);
}

/*
optimize_then_print_op() will save the linked list of the same type of ops
that can be cancelled out.
It will apply the op then:
For instance: pa and pb will be saved in the list until there are other 
ops appear (ra, rb, rra, rrb) or the other way around.
This will call central_customization to optimize the ops
Then it will print and delete the list print_then_del_op()
If its still the same type, it will just apply then append to the current list.
if op[0] == 0, this means the end of the program, just optimize then print.
*/
void optimize_then_print_op(t_op **head, char *op, t_stack **a, t_stack **b)
{
	if (op[0] == '0')
	{
		if (*head == NULL)
			return;
		central_customization(head);
		print_then_del_op(head);
		return;
	}
	if (!apply_op(op, a, b))
		exit(1);
	if (*head)
	{
		if (((*head)->op[0] == 'p' && op[0] != 'p') ||
			(((*head)->op[0] == 'r' || (*head)->op[0] == 's') && op[0] == 'p'))
		{
			central_customization(head);
			print_then_del_op(head);
		}
	}
	append_op_list(head, op);
}
