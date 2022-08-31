/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_big_stack_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:18:51 by thle              #+#    #+#             */
/*   Updated: 2022/08/31 18:27:13 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int split_stack(t_op **op, t_info *a, t_info *b, int stack_size)
{
	t_info *container;
	int other_stack_size;

	container = b;
	other_stack_size = stack_size / 2;
	if (b->splitted == 1)
		container = a;
	while (other_stack_size-- > 0)
		process_and_print_op(op, container->op[PUSH], &(a->head), &(b->head));
	a->splitted = 0;
	b->splitted = 0;
	return (stack_size / 2);
}

t_stack *retrieve_node(t_stack **stack, int value)
{
	t_stack *prev;
	t_stack *tmp;

	tmp = *stack;
	prev = NULL;
	if (tmp && tmp->value == value)
	{
		*stack = (*stack)->next;
		tmp->next = NULL;
		return tmp;
	}
	while (tmp->next)
	{
		if (value == tmp->value)
			break;
		prev = tmp;
		tmp = tmp->next;
	}
	prev->next = tmp->next;
	tmp->next = NULL;
	return tmp;
}

int get_pos(t_stack *stack, int value)
{
	t_stack *tmp = stack;
	int pos = 1;

	while (tmp)
	{
		if (tmp->value == value)
			return pos;
		pos++;
		tmp = tmp->next;
	}
	return (0);
}

long get_value(t_stack *stack, int value, int order)
{
	long hold;

	hold = LONG_MIN;
	if (order == ASC)
		hold = LONG_MAX;
	while (stack)
	{
		if (stack->value < value && hold < stack->value && order == DESC)
			hold = stack->value;
		if (stack->value > value && hold > stack->value && order == ASC)
			hold = stack->value;
		stack = stack->next;
	}
	return hold;
}