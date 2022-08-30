/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_and_print_op.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:51:07 by thle              #+#    #+#             */
/*   Updated: 2022/08/31 01:27:12 by thule            ###   ########.fr       */
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

void print_list(t_op *head)
{
	printf("%s", GREEN);
	while (head)
	{
		// if (head->op[0] != '0')
		// 	printf("%s\n", head->op);
		if (head->op[0] == '0')
			printf("%s%s%s ", MAGENTA, head->op, GREEN);
		else
			// printf("%s%s_%c_%d %s", head->op, WHITE, head->stack, head->operation, GREEN);
			printf("%s%s ", head->op, GREEN);
		head = head->next;
	}
	// printf("%s", WHITE);
	printf("\n%s", WHITE);
}

void delete_list(t_op **head)
{
	t_op *next;
	t_op *current;

	current = *head;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;
}

void cancel_rotate_swap_helper(t_op *op, char *instruction, char *counter)
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

void cancel_rotate_swap(t_op *op)
{
	t_op *tmp;

	tmp = op;
	while (tmp)
	{
		if (!ft_strcmp("ra", tmp->op))
			cancel_rotate_swap_helper(tmp, "ra", "rra");
		else if (!ft_strcmp("rb", tmp->op))
			cancel_rotate_swap_helper(tmp, "rb", "rrb");
		else if (!ft_strcmp("rra", tmp->op))
			cancel_rotate_swap_helper(tmp, "rra", "ra");
		else if (!ft_strcmp("rrb", tmp->op))
			cancel_rotate_swap_helper(tmp, "rrb", "rb");
		tmp = tmp->next;
	}
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

void change_op(t_op *first, t_op *second)
{
	second->op = "0";
	if (first->operation == SWAP)
		first->op = "ss";
	else if (first->operation == ROT)
		first->op = "rr";
	else if (first->operation == R_ROT)
		first->op = "rrr";
	// first = first->next;
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
	link_first_and_second(first, first_tail, second_head);
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
	link_first_and_second(first, first_tail, second_head);
}

void central_customization(t_op **first)
{
	t_op *second;

	if ((*first)->operation != PUSH)
		cancel_rotate_swap(*first);
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

void print_offical(t_op *head)
{
	while (head)
	{
		if (head->op[0] != '0')
			printf("%s\n", head->op);
		head = head->next;
	}
}

void process_and_print_op(t_op **head, char *op, t_stack **a, t_stack **b)
{
	if (op[0] == '0')
	{
		central_customization(head);
		print_offical(*head);
		delete_list(head);
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
			print_offical(*head);
			delete_list(head);
		}
	}
	append_op_list(head, op);
}
