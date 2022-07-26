/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 17:54:51 by thule             #+#    #+#             */
/*   Updated: 2022/07/25 13:17:41 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

static int get_op_index(char *op)
{
	char **str;
	int index;

	index = 0;
	str = (char *[]){"sa", "ra", "rra", "sb", "rb", "rrb",
					 "ss", "rr", "rrr", "pa", "pb"};
	while (index < 11)
	{
		if (!ft_strcmp(str[index], op))
			break;
		index++;
	}
	return (index);
}

/*
get_op_index will(op) will be called to check for the corresponding op index
if it is more than 11 (not correct op), return (0)
else, call the op function and return (1)
*/
int apply_op(void (*op_array[9])(t_stack **head),
						char *op, t_stack **a, t_stack **b)
{
	int index;

	index = get_op_index(op);
	if (index < 6)
	{
		if (index >= 3)
			op_array[index](b);
		else
			op_array[index](a);
	}
	else if (index >= 6 && index < 9)
	{
		op_array[index](a);
		op_array[index](b);
	}
	else if (index == 9)
		push(a, b);
	else if (index == 10)
		push(b, a);
	else
		return (0);
	return (1);
}

/* this function must be always called before proceeding to call apply_op() */
void assign_index_for_op(void (*op_array[9])(t_stack **head))
{
	op_array[sa] = swap;
	op_array[ra] = rotate;
	op_array[rra] = reverse_rotate;
	op_array[sb] = swap;
	op_array[rb] = rotate;
	op_array[rrb] = reverse_rotate;
	op_array[ss] = swap;
	op_array[rr] = rotate;
	op_array[rrr] = reverse_rotate;
}
