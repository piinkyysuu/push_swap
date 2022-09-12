/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 14:39:09 by thule             #+#    #+#             */
/*   Updated: 2022/09/12 19:02:21 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shared.h"

static void	del_op_list(t_op **head)
{
	t_op	*next;
	t_op	*current;

	current = *head;
	while (current)
	{
		next = current->next;
		ft_strdel(&(current->op));
		free(current);
		current = next;
	}
	*head = NULL;
}

/*
Central point for reading op_arrays from standard input
The op will be saved in *op
Call apply_op()
After reading all op_array(s), is_stack_sorted() gets called
return (-1) if the op is not correct
return (0) if the stack is not sorted
return (1) if the stack is sorted
*/
static int	read_then_apply_op(int fd, t_stack **a, t_stack **b)
{
	t_op	*op_head;
	t_op	*tmp;
	int		result;
	char	*op;

	result = 1;
	op = NULL;
	op_head = NULL;
	while (get_next_line(fd, &op))
		append_op_list(&op_head, op);
	tmp = op_head;
	while (tmp)
	{
		if (apply_op(tmp->op, a, b) == 0)
			result = -1;
		tmp = tmp->next;
	}
	del_op_list(&op_head);
	if ((!is_stack_sorted(*a) || *b) && result != -1)
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
		return (0);
	if (create_stack(argc, argv, &a) == -1)
		write(2, "Error\n", 6);
	else
	{
		result = read_then_apply_op(0, &a, &b);
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
