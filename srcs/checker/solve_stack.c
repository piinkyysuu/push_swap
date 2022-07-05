/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:19:50 by thule             #+#    #+#             */
/*   Updated: 2022/07/05 13:33:42 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static int get_instruction_index(char *line)
{
	char **str;
	int index;

	index = 0;
	str = (char *[]){"sa", "ra", "rra", "sb", "rb", "rrb",
					 "ss", "rr", "rrr", "pa", "pb"};
	while (index < 11)
	{
		if (!ft_strcmp(str[index], line))
			break;
		index++;
	}
	return (index);
}

/*
get_instruction_index will(line) will be called to check for the corresponding index
if it is more than 11 (not correct instruction), return (0)
else, call the instruction function and return (1)
*/
static int solve_with_instruction(void (*instruction[9])(t_stack **head),
									char *line, t_stack **a, t_stack **b)
{
	int index;

	index = get_instruction_index(line);
	if (index < 6)
	{
		if (index >= 3)
			instruction[index](b);
		else
			instruction[index](a);
	}
	else if (index >= 6 && index < 9)
	{
		instruction[index](a);
		instruction[index](b);
	}
	else if (index == 9)
		push(a, b);
	else if (index == 10)
		push(b, a);
	else
		return (0);
	return (1);
}

static int is_stack_sorted(t_stack **head)
{
	t_stack *tmp;
	int value;

	tmp = *head;
	value = tmp->value;
	tmp = tmp->next;
	while (tmp)
	{
		if (value > tmp->value)
		{
			return (0);
		}
		value = tmp->value;
		tmp = tmp->next;
	}
	return (1);
}

/*
Central point for reading instructions from standard input
The instruction will be saved in *line
Call solve_with_instruction()
After reading all instruction(s), is_stack_sorted() gets called
return -1 if the instruction is not correct
return 0 if the stack is not sorted
return 1 if the stack is sorted
*/
int solve_stack(t_stack *a, t_stack *b, void (*instruction[9])(t_stack **head))
{
	char *line;
	int result;

	line = NULL;
	result = 1;
	while (get_next_line(0, &line))
	{
		if (!solve_with_instruction(instruction, line, &a, &b))
		{
			result = -1;
			ft_strdel(&line);
			break;
		}
		ft_strdel(&line);
	}
	if ((!is_stack_sorted(&a) || b) && result != -1)
		result = 0;
	delete_stack(&a);
	delete_stack(&b);
	return (result);
}