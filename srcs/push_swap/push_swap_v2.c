/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_v2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 13:28:16 by thle              #+#    #+#             */
/*   Updated: 2022/08/31 20:28:37 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Aims for merge sort method for bigger than 5 */

#include "push_swap.h"

#define EMPTY LONG_MIN


void process_and_print_op(t_op **head, char *op, t_stack **a, t_stack **b);


void initialize_info(t_info *stack, char name)
{
	stack->name = name;
	stack->head = NULL;
	stack->splitted = 0;
	stack->hold = NULL;
	stack->op[4] = "\0";
	stack->op[PUSH] = "pa";
	stack->op[SWAP] = "sa";
	stack->op[ROT] = "ra";
	stack->op[R_ROT] = "rra";
	if (stack->name == 'b')
	{
		stack->op[PUSH] = "pb";
		stack->op[SWAP] = "sb";
		stack->op[ROT] = "rb";
		stack->op[R_ROT] = "rrb";
	}
}


int main(int argc, char *argv[])
{
	t_info a;
	t_info b;
	t_op *op = NULL;

	initialize_info(&a, 'a');
	initialize_info(&b, 'b');

	int amount = create_stack(argc, argv, &(a.head));
	if (!amount)
		write(2, "Error\n", 6);
	else
	{
		merge_sort(&op, &a, &b, get_size(a.head));
		process_and_print_op(&op, "0", &(a.head), &(b.head));
	}
	exit(1);
	return (1);
}

/* later use */

int get_size(t_stack *stack)
{
	t_stack *tmp;
	int pos = 0;

	tmp = stack;
	pos = 0;
	while (tmp)
	{
		pos++;
		tmp = tmp->next;
	}
	return (pos);
}

long get_max(t_stack *stack)
{
	t_stack *tmp;
	int max;

	tmp = stack;
	if (!tmp)
		return EMPTY;
	max = tmp->value;
	tmp = tmp->next;
	while (tmp)
	{
		if (max < tmp->value)
			max = tmp->value;
		tmp = tmp->next;
	}
	return max;
}

long get_min(t_stack *stack)
{
	t_stack *tmp;
	int min;

	tmp = stack;
	if (!tmp)
		return EMPTY;
	min = tmp->value;
	tmp = tmp->next;
	while (tmp)
	{
		if (min > tmp->value)
			min = tmp->value;
		tmp = tmp->next;
	}
	return min;
}
