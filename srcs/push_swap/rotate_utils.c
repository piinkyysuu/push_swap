/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:34:57 by thle              #+#    #+#             */
/*   Updated: 2022/08/24 18:40:15 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void rotate_to_top(t_op **op, t_info *stack, int pos)
{
	int stack_size;

	stack_size = get_size(stack->head);
	if (pos == stack_size + 1 || pos == 0)
		return;
	if (pos > stack_size / 2)
	{
		while (pos++ < stack_size + 1)
			process_and_print_op(op, stack->op[R_ROT], &(stack->head), &(stack->head));
	}
	else
	{
		while (pos-- > 1)
			process_and_print_op(op, stack->op[ROT], &(stack->head), &(stack->head));
	}
}

void rotate_to_bottom(t_op **op, t_info *stack, int pos)
{
	int stack_size = get_size(stack->head);

	if (pos < stack_size / 2)
	{
		while (pos > 0)
		{
			process_and_print_op(op, stack->op[ROT], &(stack->head), &(stack->head));
			pos--;
		}
		return;
	}
	while (pos > 0 && pos++ < stack_size)
	{
		process_and_print_op(op, stack->op[R_ROT], &(stack->head), &(stack->head));
	}
}
