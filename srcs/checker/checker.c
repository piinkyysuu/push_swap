/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 14:39:09 by thule             #+#    #+#             */
/*   Updated: 2022/07/12 18:19:07 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

/*
Central point for reading op_arrays from standard input
Before any action, assign_index_for_op() gets called
	to assign function to indexes
The op_array will be saved in *op
Call apply_op()
After reading all op_array(s), is_stack_sorted() gets called
return -1 if the op is not correct
return 0 if the stack is not sorted
return 1 if the stack is sorted
*/
static int solve_stack(t_stack *a, t_stack *b)
{
	char *op;
	int result;
	void (*op_array[9])(t_stack **);

	op = NULL;
	result = 1;
	assign_index_for_op(op_array);
	while (get_next_line(0, &op))
	{
		if (!apply_op(op_array, op, &a, &b))
		{
			result = -1;
			ft_strdel(&op);
			break;
		}
		ft_strdel(&op);
	}
	if ((!is_stack_sorted(&a) || b) && result != -1)
		result = 0;
	delete_stack(&a);
	delete_stack(&b);
	return (result);
}

int main(int argc, char *argv[])
{
	t_stack *a;
	t_stack *b;
	int result;

	a = NULL;
	b = NULL;
	if (argc < 2)
		return (0);
	if (!create_stack(argc, argv, &a))
		write(2, "Error\n", 6);
	else
	{
		result = solve_stack(a, b);
		if (result == -1)
			write(2, "Error\n", 6);
		else if (result == 0)
			write(1, "KO\n", 3);
		else
			write(1, "OK\n", 3);
	}
	return (0);
}
