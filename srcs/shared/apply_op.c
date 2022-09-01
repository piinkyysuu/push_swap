/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 17:54:51 by thule             #+#    #+#             */
/*   Updated: 2022/09/01 18:37:48 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

static int	get_op_index(char *op)
{
	char	**str;
	int		index;

	index = 0;
	str = (char *[]){"sa", "sb", "ss", "ra", "rb", "rr",
		"rra", "rrb", "rrr", "pa", "pb"};
	while (index < 11)
	{
		if (!ft_strcmp(str[index], op))
			break ;
		index++;
	}
	return (index);
}

/*
get_op_index will(op) will be called to check for the corresponding op index
if it is more than 11 (not correct op), return (0)
else, call the op function and return (1)
*/
int	apply_op(char *op, t_stack **a, t_stack **b)
{
	void	(*array[3])(t_stack **head);
	int		index;

	index = get_op_index(op);
	array[SWAP] = swap;
	array[ROT] = rotate;
	array[R_ROT] = reverse_rotate;
	if (index == 9)
		push(a, b);
	else if (index == 10)
		push(b, a);
	else if (index == 2 || index == 5 || index == 8)
	{
		array[OP_INDEX[index] - '0'](a);
		array[OP_INDEX[index] - '0'](b);
	}
	else if (index == 0 || index == 3 || index == 6)
		array[OP_INDEX[index] - '0'](a);
	else if (index == 1 || index == 4 || index == 7)
		array[OP_INDEX[index] - '0'](b);
	else
		return (0);
	return (1);
}
