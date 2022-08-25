/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_and_print_op.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:51:07 by thle              #+#    #+#             */
/*   Updated: 2022/08/25 19:25:16 by thle             ###   ########.fr       */
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
		return ;
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

void cancel_instruction_helper(t_op *op, char *instruction, char *counter)
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
			cancel_instruction_helper(tmp, "ra", "rra");
		else if (!ft_strcmp("rb", tmp->op))
			cancel_instruction_helper(tmp, "rb", "rrb");
		else if (!ft_strcmp("rra", tmp->op))
			cancel_instruction_helper(tmp, "rra", "ra");
		else if (!ft_strcmp("rrb", tmp->op))
			cancel_instruction_helper(tmp, "rrb", "rb");
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
			break ;
		}
		first = first->next;
	}
	return (hold);
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
	t_op *tmp_second;
	t_op *tmp_first;
	t_op *hold;
	char second_char;

	if (tmp_first->operation != PUSH)
		cancel_rotate_swap(*first);
	second = split_instructions(*first);
	tmp_second = second;
	tmp_first = *first;
	hold = NULL;
	if (second == NULL)
		return ;
	if (tmp_first->operation == PUSH)
	{
		cancel_push(*first, second);
		return;
	}
	second_char = tmp_second->stack;
	while (tmp_second && tmp_second->stack == second_char)
	{
		while (tmp_first && tmp_second->op[0] != '0')
		{
			if (tmp_first->next == NULL)
				hold = tmp_first;
			if (tmp_second->operation == tmp_first->operation && tmp_first->op[0] != '0')
			{
				tmp_second->op = "0";
				if (tmp_first->operation == SWAP)
					tmp_first->op = "ss";
				else if (tmp_first->operation == ROT)
					tmp_first->op = "rr";
				else if (tmp_first->operation == R_ROT)
					tmp_first->op = "rrr";
				tmp_first = tmp_first->next;
				break;
			}
			tmp_first = tmp_first->next;
		}
		if (hold)
			break;
		tmp_second = tmp_second->next;
	}
	if (hold == NULL)
	{
		while (tmp_first->next)
			tmp_first = tmp_first->next;
		hold = tmp_first;
	}
	hold->next = second;
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
	if (!apply_op(op, a, b))
		exit(1);
	if (op[0] == '0')
	{
		print_offical(*head);
		delete_list(head);
		return ;
	}
	if (*head)
	{
		if ((*head)->op[0] == 'p' && op[0] != 'p')
		{
			central_customization(head);
			// print_list(*head);
			print_offical(*head);
			delete_list(head);
		}
		else if (((*head)->op[0] == 'r' || (*head)->op[0] == 's') && op[0] == 'p')
		{
			// cancel_instruction(*head);
			central_customization(head);
			// print_list(*head);
			print_offical(*head);
			delete_list(head);
		}
	}
	append_op_list(head, op);
}
