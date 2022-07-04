/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 14:39:09 by thule             #+#    #+#             */
/*   Updated: 2022/07/04 13:10:25 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

enum e_instructions
{
	sa,
	ra,
	rra,
	sb,
	rb,
	rrb
};

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

int solve_stack(char *line, t_stack **a, t_stack **b)
{
	// printf("solve_stack called\n");
	//                0     1      2     3     4     5      6     7     8     9      10
	char *str[11] = {"sa", "ra", "rra", "sb", "rb", "rrb", "pa", "pb", "ss", "rr", "rrr"};
	typedef void general(t_stack **head);
	t_stack **tmp = b;
	general *arr[6];
	int index = 0;

	arr[sa] = swap;
	arr[sb] = swap;
	arr[ra] = rotate;
	arr[rb] = rotate;
	arr[rra] = reverse_rotate;
	arr[rrb] = reverse_rotate;
	while (index < 11)
	{
		if (!ft_strcmp(str[index], line))
			break;
		index++;
	}
	if (index < 3)
		tmp = a;
	if (index < 6)
	{
		arr[index](tmp);
	}
	else if (index == 6)
	{
		push(a, b);
	}
	else if (index == 7)
	{
		push(b, a);
	}
	else if (index == 8)
	{
		swap(a);
		swap(b);
	}
	else if (index == 9)
	{
		rotate(a);
		rotate(b);
	}
	else if (index == 10)
	{
		reverse_rotate(a);
		reverse_rotate(b);
	}
	else
		return (0);
	return (1);
}

int main(int argc, char *argv[])
{
	t_stack *a;
	t_stack *b;
	char *line;
	int index = 0;
	char *str[11] = {"sa", "sb", "ss", "pa", "pb", "ra", "rb", "rr", "rra", "rrb", "rrr"};

	a = NULL;
	b = NULL;
	line = NULL;
	if (argc < 2)
		return (0);
	if (!create_stack(argc, argv, &a))
		write(2, "Error\n", 6);
	// else
	// {
	// 	printf("og\n");
	// 	printf("----------------------------------");
	// 	print_2_stacks(a, b);
	// 	printf("\n");
	// 	while (get_next_line(0, &line))
	// 	{
	// 		printf("----------------------------------");
	// 		index = 0;
	// 		while (str[index])
	// 		{
	// 			if (!ft_strcmp(str[index], line))
	// 				break;
	// 			index++;
	// 		}
	// 		switch (index)
	// 		{
	// 		case 0:
	// 			swap(&a);
	// 			break;
	// 		case 1:
	// 			swap(&b);
	// 			break;
	// 		case 2:
	// 			swap(&a);
	// 			swap(&b);
	// 			break;
	// 		case 3:
	// 			push(&a, &b);
	// 			break;
	// 		case 4:
	// 			push(&b, &a);
	// 			break;
	// 		case 5:
	// 			rotate(&a);
	// 			break;
	// 		case 6:
	// 			rotate(&b);
	// 			break;
	// 		case 7:
	// 			rotate(&a);
	// 			rotate(&b);
	// 			break;
	// 		case 8:
	// 			reverse_rotate(&a);
	// 			break;
	// 		case 9:
	// 			reverse_rotate(&b);
	// 			break;
	// 		case 10:
	// 			reverse_rotate(&a);
	// 			reverse_rotate(&b);
	// 			break;
	// 		case 11:
	// 			printf("not exists");
	// 			break;
	// 		}
	// 		print_2_stacks(a, b);
	// 		printf("\n");
	// 		ft_strdel(&line);
	// 	}
	// }

	printf("og\n");
	printf("----------------------------------");
	print_2_stacks(a, b);
	printf("\n");
	while (get_next_line(0, &line))
	{
		printf("----------------------------------");
		solve_stack(line, &a, &b);
		print_2_stacks(a, b);
		ft_strdel(&line);
		printf("\n");
	}

	// print_2_stacks(a, b);
	// printf("\n-------------------------\n");
	// reverse_rotate(&a);
	// print_2_stacks(a, b);

	return (0);
}