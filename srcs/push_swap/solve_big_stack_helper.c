/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_big_stack_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:18:51 by thle              #+#    #+#             */
/*   Updated: 2022/09/01 19:01:05 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	split_stack(t_op **op, t_info *a, t_info *b, int stack_size)
{
	t_info	*container;
	int		other_stack_size;

	container = b;
	other_stack_size = stack_size / 2;
	if (b->splitted == 1)
		container = a;
	while (other_stack_size-- > 0)
		optimize_then_print_op(op, container->op[PUSH], &(a->head), &(b->head));
	a->splitted = 0;
	b->splitted = 0;
	return (stack_size / 2);
}

t_stack	*retrieve_node(t_stack **stack, int value)
{
	t_stack	*prev;
	t_stack	*tmp;

	tmp = *stack;
	prev = NULL;
	if (tmp && tmp->value == value)
	{
		*stack = (*stack)->next;
		tmp->next = NULL;
		return (tmp);
	}
	while (tmp->next)
	{
		if (value == tmp->value)
			break ;
		prev = tmp;
		tmp = tmp->next;
	}
	prev->next = tmp->next;
	tmp->next = NULL;
	return (tmp);
}

t_stack	*copy_stack(t_stack *stack, int amount)
{
	t_stack	*tmp;
	t_stack	*head;

	if (amount > 0 && stack)
	{
		head = create_new_element(stack->value);
		amount--;
		tmp = head;
		stack = stack->next;
		while (stack && amount > 0)
		{
			tmp->next = create_new_element(stack->value);
			tmp = tmp->next;
			stack = stack->next;
			amount--;
		}
		return (head);
	}
	return (NULL);
}
