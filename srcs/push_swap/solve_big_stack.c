/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_big_stack.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:19:12 by thle              #+#    #+#             */
/*   Updated: 2022/08/24 18:45:00 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void merge_to_stack_b(t_op **op, t_info *a, t_info *b)
{
	int a_size;
	int value;
	int min;
	int max;
	t_stack *hold;

	a_size = get_size(*(a->hold));
	while (a_size-- > 0)
	{
		value = a->head->value;
		min = get_min(*(b->hold));
		max = get_max(*(b->hold));
		if (value > max)
			rotate_to_top(op, b, get_pos(b->head, max));
		else if (value < min)
			rotate_to_bottom(op, b, get_pos(b->head, min));
		else
			rotate_to_top(op, b, get_pos(b->head, get_value(*(b->hold), value, DESC)));
		process_and_print_op(op, b->op[PUSH], &(a->head), &(b->head));
		hold = retrieve_node(a->hold, value);
		push(b->hold, &hold);
	}
}

void merge_to_stack_a(t_op **op, t_info *a, t_info *b)
{
	int b_size;
	int value;
	int max;
	t_stack *hold;

	rotate_to_top(op, b, get_pos(b->head, get_max(*(b->hold))));
	b_size = get_size(*(b->hold));
	while (b_size-- > 0)
	{
		value = b->head->value;
		max = get_max(*(a->hold));
		if (value > max)
			rotate_to_bottom(op, a, get_pos(a->head, max));
		else
			rotate_to_top(op, a, get_pos(a->head, get_value(*(a->hold), value, ASC)));
		process_and_print_op(op, a->op[PUSH], &(a->head), &(b->head));
		hold = retrieve_node(b->hold, value);
		push(a->hold, &hold);
	}
	rotate_to_top(op, a, get_pos(a->head, get_min(*(a->hold))));
}

t_stack *merge_sort_stack_b(t_op **op, t_info *a, t_info *b, int stack_size)
{
	t_stack *on_a;
	t_stack *on_b;
	int container_size;

	on_a = NULL;
	on_b = NULL;
	if (stack_size <= 3)
	{
		solve_three(op, b, stack_size);
		on_b = copy_stack(b->head, stack_size);
		return on_b;
	}
	b->splitted = 1;
	container_size = split_stack(op, a, b, stack_size);
	stack_size = stack_size - container_size;
	on_b = merge_sort_stack_b(op, a, b, stack_size);
	on_a = merge_sort_stack_a(op, a, b, container_size);
	a->hold = &on_a;
	b->hold = &on_b;
	merge_to_stack_b(op, a, b);
	return on_b;
}

t_stack *merge_sort_stack_a(t_op **op, t_info *a, t_info *b, int stack_size)
{
	t_stack *on_a;
	t_stack *on_b;
	int container_size;

	on_a = NULL;
	on_b = NULL;
	if (stack_size <= 3)
	{
		solve_three(op, a, stack_size);
		on_a = copy_stack(a->head, stack_size);
		return on_a;
	}
	a->splitted = 1;
	container_size = split_stack(op, a, b, stack_size);
	stack_size = stack_size - container_size;
	on_b = merge_sort_stack_b(op, a, b, container_size);
	on_a = merge_sort_stack_a(op, a, b, stack_size);
	a->hold = &on_a;
	b->hold = &on_b;
	merge_to_stack_a(op, a, b);
	return on_a;
}

void merge_sort(t_op **op, t_info *a, t_info *b, int stack_size)
{
	t_stack *sorted;

	sorted = merge_sort_stack_a(op, a, b, stack_size);
	delete_stack(&sorted);
}