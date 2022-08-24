/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_and_print_op.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:51:07 by thle              #+#    #+#             */
/*   Updated: 2022/08/24 20:42:24 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void append_op_list(t_op **head, char *op)
{
	t_op *new;
	t_op *tmp;

	tmp = *head;
	new = (t_op *)malloc(sizeof(t_op));
	new->op = op;
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
		if (head->op[0] == '0')
			printf("%s%s%s ", MAGENTA, head->op, GREEN);
		else
			printf("%s ", head->op);
		head = head->next;
	}
	printf("%s", WHITE);
	printf("\n");
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

void cancel_instruction(t_op *op)
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

void process_and_print_op(t_op **head, char *op, t_stack **a, t_stack **b)
{
	if (!apply_op(op, a, b))
		exit(1);
	// if (op[0] == 'p')
	// {
	// 	if (*head)
	// 	{
	// 		cancel_instruction(*head);
	// 		print_list(*head);
	// 		delete_list(head);
	// 	}
	// 	printf("%s\n", op);
	// }
	// else
	// {
	// 	append_op_list(head, op);
	// }
	append_op_list(head, op);
}
