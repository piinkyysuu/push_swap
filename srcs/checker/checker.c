/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 14:39:09 by thule             #+#    #+#             */
/*   Updated: 2022/09/01 17:11:50 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shared.h"

/*
Central point for reading op_arrays from standard input
The op will be saved in *op
Call apply_op()
After reading all op_array(s), is_stack_sorted() gets called
return (-1) if the op is not correct
return (0) if the stack is not sorted
return (1) if the stack is sorted
*/
static int	read_then_apply_op(t_stack *a, t_stack *b)
{
	char	*op;
	int		result;

	op = NULL;
	result = 1;
	while (get_next_line(0, &op))
	{
		if (!apply_op(op, &a, &b))
		{
			result = -1;
			ft_strdel(&op);
			break ;
		}
		ft_strdel(&op);
	}
	if ((!is_stack_sorted(a) || b) && result != -1)
		result = 0;
	return (result);
}

int	main(int argc, char *argv[])
{
	t_stack	*a;
	t_stack	*b;
	int		result;

	a = NULL;
	b = NULL;
	if (argc < 2)
		return (write(1, "\n", 1), 0);
	if (create_stack(argc, argv, &a) == -1)
		write(2, "Error\n", 6);
	else
	{
		result = read_then_apply_op(a, b);
		if (result == -1)
			write(2, "Error\n", 6);
		else if (result == 0)
			write(1, "KO\n", 3);
		else
			write(1, "OK\n", 3);
	}
	delete_stack(&a);
	delete_stack(&b);
	return (0);
}
