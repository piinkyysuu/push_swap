/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 14:39:09 by thule             #+#    #+#             */
/*   Updated: 2022/07/04 16:00:10 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int get_instruction_index(char *line)
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

int solve_stack(void (*instruction[9])(t_stack **head),
				char *line, t_stack **a, t_stack **b)
{
	int index;

	index = get_instruction_index(line);
	if (index < 6)
	{
		if (index >= 3)
			instruction[index](b);
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

void assign_index_for_array(void (*instruction[9])(t_stack **head))
{
	instruction[sa] = swap;
	instruction[ra] = rotate;
	instruction[rra] = reverse_rotate;
	instruction[sb] = swap;
	instruction[rb] = rotate;
	instruction[rrb] = reverse_rotate;
	instruction[ss] = swap;
	instruction[rr] = rotate;
	instruction[rrr] = reverse_rotate;
}

int is_stack_sorted(t_stack **head)
{
	t_stack *tmp;
	int value;

	tmp = *head;
	value = tmp->value;
	tmp = tmp->next;
	while (tmp->next)
	{
		if (value > tmp->value)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int main(int argc, char *argv[])
{
	t_stack *a;
	t_stack *b;
	char *line;
	void (*instruction[9])(t_stack * *head);

	a = NULL;
	b = NULL;
	line = NULL;
	assign_index_for_array(instruction);
	if (argc < 2)
		return (0);
	if (!create_stack(argc, argv, &a))
		write(2, "Error\n", 6);
	else
	{
		while (get_next_line(0, &line))
		{
			if (!solve_stack(instruction, line, &a, &b))
			{
				write(2, "Error\n", 6);
				delete_stack(&a);
				delete_stack(&b);
				return (0);
				// break;
			}
			ft_strdel(&line);
		}
		print_2_stacks(a, b);
		if (!is_stack_sorted(&a) || b)
			printf("wrong\n");
		else
			printf("correct\n");
		delete_stack(&a);
		delete_stack(&b);
	}
	return (0);
}