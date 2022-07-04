/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 14:39:09 by thule             #+#    #+#             */
/*   Updated: 2022/07/04 15:18:00 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void print_stack(t_stack *head, char c)
{
	t_stack *tmp = head;
	while (tmp)
	{
		printf("%d\n", tmp->value);
		tmp = tmp->next;
	}
	printf("-\n%c\n", c);
}

int count_stack(t_stack **head)
{
	t_stack *tmp;
	int len;

	len = 0;
	tmp = *head;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return len;
}

void print_2_stacks(t_stack *a, t_stack *b)
{
	int a_len = count_stack(&a);
	int b_len = count_stack(&b);
	t_stack *t_a = a;
	t_stack *t_b = b;
	int max_len = a_len > b_len ? a_len : b_len;
	while (max_len >= 0)
	{
		if (a_len > max_len)
		{
			printf("%d", a->value);
			a = a->next;
		}
		if (b_len > max_len)
		{
			printf("			%d\n", b->value);
			b = b->next;
		}
		else
			printf("\n");
		max_len--;
	}
	printf("-			-\n");
	printf("a			b\n");
}

int get_instruction_index( char *line)
{
	char **str;
	int index;
	
	index = 0;
	str = (char *[]){"sa", "ra", "rra", "sb", "rb", "rrb", "ss", "rr", "rrr", "pa", "pb"};
	while (index < 11)
	{
		if (!ft_strcmp(str[index], line))
			break;
		index++;
	}
	return (index);
}

int solve_stack(void (*instruction[9])(t_stack **head), char *line, t_stack **a , t_stack **b)
{
	int		index;

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
		push(b , a);
	else
		return (0);
	return (1);
}

void	assign_func_array(void (*instruction[9])(t_stack **head))
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

int main(int argc, char *argv[])
{
	t_stack	*a;
	t_stack	*b;
	char	*line;
	void	(*instruction[9])(t_stack **head);

	a = NULL;
	b = NULL;
	line = NULL;
	assign_func_array(instruction);
	if (argc < 2)
		return (0);
	if (!create_stack(argc, argv, &a))
	{
		write(2, "Error\n", 6);
		return 0;
	}
	printf("og\n");
	printf("----------------------------------");
	print_2_stacks(a, b);
	printf("\n");
	while (get_next_line(0, &line))
	{
		printf("----------------------------------");
		solve_stack(instruction, line, &a, &b);
		print_2_stacks(a, b);
		ft_strdel(&line);
		printf("\n");
	}
	return (0);
}