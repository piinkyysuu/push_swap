/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 13:28:16 by thle              #+#    #+#             */
/*   Updated: 2022/09/05 12:02:24 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	initialize_info(t_info *stack, char name)
{
	stack->name = name;
	stack->head = NULL;
	stack->hold = NULL;
	stack->splitted = 0;
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

int	main(int argc, char *argv[])
{
	t_info	a;
	t_info	b;
	t_op	*op;
	int		size;

	op = NULL;
	initialize_info(&a, 'a');
	initialize_info(&b, 'b');
	if (argc < 2)
		return (0);
	size = create_stack(argc, argv, &(a.head));
	if (size == -1)
		return (write(2, "Error\n", 6), 0);
	if (size != 1 && !is_stack_sorted(a.head))
	{
		if (size <= 3 && size > 1)
			solve_three(&op, &a, size);
		else
			merge_sort(&op, &a, &b, get_size(a.head));
		optimize_then_print_op(&op, "0", &(a.head), &(b.head));
	}
	delete_stack(&(a.head));
	delete_stack(&(b.head));
	return (0);
}
