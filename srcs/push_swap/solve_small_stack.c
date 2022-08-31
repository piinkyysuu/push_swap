/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_small_stack.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:06:05 by thle              #+#    #+#             */
/*   Updated: 2022/08/31 20:22:41 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void solve_stack_of_three(t_op **op, t_info *stack)
{
	int size;
	int first;
	int second;
	int third;

	size = get_size(stack->head);
	while (size == 3)
	{
		first = stack->head->value;
		second = stack->head->next->value;
		third = stack->head->next->next->value;
		if ((second > first && second > third && stack->name == 'a') ||
			(second < first && second < third && stack->name == 'b'))
			process_and_print_op(op, stack->op[R_ROT], &(stack->head), &(stack->head));
		else if ((first > third && first > second && stack->name == 'a') ||
				 (first < third && first < second && stack->name == 'b'))
			process_and_print_op(op, stack->op[ROT], &(stack->head), &(stack->head));
		else if ((second < first && stack->name == 'a') ||
				 (second > first && stack->name == 'b'))
			process_and_print_op(op, stack->op[SWAP], &(stack->head), &(stack->head));
		else
			return;
	}
}

static void solve_top_three_helper(t_op **op, t_info *stack)
{
	int first;
	int second;
	int third;

	first = stack->head->value;
	second = stack->head->next->value;
	third = stack->head->next->next->value;
	process_and_print_op(op, stack->op[ROT], &(stack->head), &(stack->head));
	process_and_print_op(op, stack->op[SWAP], &(stack->head), &(stack->head));
	process_and_print_op(op, stack->op[R_ROT], &(stack->head), &(stack->head));
	if ((first < second && second > third && first > third && stack->name == 'a') || (first > second && second < third && first < third && stack->name == 'b'))
		process_and_print_op(op, stack->op[SWAP], &(stack->head), &(stack->head));
	else if ((third < second && second < first && stack->name == 'a') || (third > second && second > first && stack->name == 'b'))
	{
		process_and_print_op(op, stack->op[SWAP], &(stack->head), &(stack->head));
		process_and_print_op(op, stack->op[ROT], &(stack->head), &(stack->head));
		process_and_print_op(op, stack->op[SWAP], &(stack->head), &(stack->head));
		process_and_print_op(op, stack->op[R_ROT], &(stack->head), &(stack->head));
	}
}

static void solve_top_three(t_op **op, t_info *stack)
{
	int first;
	int second;
	int third;

	first = stack->head->value;
	second = stack->head->next->value;
	third = stack->head->next->next->value;
	if ((first < second && second < third && stack->name == 'a') || (first > second && second > third && stack->name == 'b'))
		return;
	else if ((first > second && second < third && third > first && stack->name == 'a') || (first < second && second > third && third < first && stack->name == 'b'))
		process_and_print_op(op, stack->op[SWAP], &(stack->head), &(stack->head));
	else if ((first > second && first > third && second < third && stack->name == 'a') || (first < second && first < third && second > third && stack->name == 'b'))
	{
		process_and_print_op(op, stack->op[SWAP], &(stack->head), &(stack->head));
		process_and_print_op(op, stack->op[ROT], &(stack->head), &(stack->head));
		process_and_print_op(op, stack->op[SWAP], &(stack->head), &(stack->head));
		process_and_print_op(op, stack->op[R_ROT], &(stack->head), &(stack->head));
	}
	else
		solve_top_three_helper(op, stack);
}

void solve_three(t_op **op, t_info *stack, int amount)
{
	int size;

	size = get_size(stack->head);
	if (amount == 1 || size == 1)
		return;
	if (amount <= 2 && size >= 2)
	{
		if ((stack->head->value > stack->head->next->value && stack->name == 'a') ||
			(stack->head->value < stack->head->next->value && stack->name == 'b'))
			process_and_print_op(op, stack->op[SWAP], &(stack->head), &(stack->head));
		return;
	}
	if (size == 3)
		solve_stack_of_three(op, stack);
	else
		solve_top_three(op, stack);
}
