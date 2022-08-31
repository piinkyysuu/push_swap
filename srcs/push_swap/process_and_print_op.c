/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_and_print_op.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:51:07 by thle              #+#    #+#             */
/*   Updated: 2022/08/31 20:19:03 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void append_op_list(t_op **head, char *op)
{
	t_op *new;
	t_op *tmp;
	int len;

	len = ft_strlen(op);
	tmp = *head;
	new = (t_op *)malloc(sizeof(t_op));
	new->op = op;
	new->stack = op[len - 1];
	if (len == 3)
		new->operation = R_ROT;
	else
	{
		if (op[0] == 's')
			new->operation = SWAP;
		else if (op[0] == 'r')
			new->operation = ROT;
		else
			new->operation = PUSH;
	}
	new->next = NULL;
	if (!new)
		exit(1);
	if (!tmp)
	{
		*head = new;
		return;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}


void print_then_del_op(t_op **head)
{
	t_op *next;
	t_op *current;

	current = *head;
	while (current)
	{
		if (current->op[0] != '0')
			printf("%s\n", current->op);
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;
}


t_op *split_instructions(t_op *first)
{
	int first_char;
	t_op *hold;

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
			break;
		}
		first = first->next;
	}
	return (hold);
}

void link_first_and_second(t_op *first, t_op *first_tail, t_op *second_head)
{
	if (first_tail == NULL)
	{
		while (first->next)
			first = first->next;
		first_tail = first;
	}
	first_tail->next = second_head;
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

void process_and_print_op(t_op **head, char *op, t_stack **a, t_stack **b)
{
	if (op[0] == '0')
	{
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
