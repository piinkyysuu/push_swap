/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:13:31 by thle              #+#    #+#             */
/*   Updated: 2022/08/02 14:20:25 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int solve_stack(t_stack *a, t_stack *b)
{
	char *op;
	int result;
	void (*op_array[9])(t_stack **);

	int index = 1;
	op = NULL;
	result = 1;
	assign_index_for_op(op_array);
	while (get_next_line(0, &op))
	{
		if (!apply_op(op_array, op, &(a), &(b)))
		{
			result = -1;
			ft_strdel(&op);
			break;
		}
		printf("%s--------------------%s%03d%s--------------------%s\n", YELLOW, MAGENTA, index, YELLOW, WHITE);
		index++;
		print_2_stacks(a, b);
		printf("\n");
		ft_strdel(&op);
	}
	if (!(a))
		return 0;
	if ((!is_stack_sorted(&(a)) || b) && result != -1)
		result = 0;
	delete_stack(&(a));
	delete_stack(&(b));
	return (result);
}

int main(int argc, char *argv[])
{
	int result = 0;
	t_stack *a = NULL;
	t_stack *b = NULL;
	void (*op_array[9])(t_stack **);

	assign_index_for_op(op_array);

	
	create_stack(argc, argv, &a);
	printf("%s--------------------%s%03d%s--------------------%s\n", YELLOW, MAGENTA, 0, YELLOW, WHITE);
	print_2_stacks(a, b);
	printf("\n");

	result = solve_stack(a, b);
	if (result == -1)
	{
		printf("%sMALLOC PROBLEM\n", RED);
	}
	else if (result == 0)
	{
		printf("%sNOT SORTED OR B STILL EXIST\n", RED);
	}
	else
	{
		printf("%sSORTED\n", GREEN);
	}
	exit(1);
	return (0);
}