/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:55:23 by thule             #+#    #+#             */
/*   Updated: 2022/07/25 11:14:54 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
// #include "push_swap.h"

int is_stack_sorted(t_stack **head)
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

void delete_stack(t_stack **head)
{
	t_stack *next;
	t_stack *current;

	current = *head;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;
}

t_stack *create_new_element(int value)
{
	t_stack *new;

	new = (t_stack *)malloc(sizeof(t_stack));
	if (new)
	{
		new->value = value;
		new->next = NULL;
	}
	return (new);
}

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
	printf("%20s %s|%s %-15s\n", "Stack A", YELLOW, WHITE, "Stack B");
	int a_len = count_stack(&a);
	int b_len = count_stack(&b);
	t_stack *t_a = a;
	t_stack *t_b = b;
	int index = 1;
	while (a && b)
	{
		printf("[%3d]%15d %s|%s %-15d\n", index, a->value, YELLOW, WHITE, b->value);
		a = a->next;
		b = b->next;
		index++;
	}
	while (a)
	{
		printf("[%3d]%15d %s|%s\n", index, a->value, YELLOW, WHITE);
		a = a->next;
		index++;
	}
	while (b)
	{
		printf("[%3d]%15s %s|%s %-15d\n", index, " ", YELLOW, WHITE, b->value);
		b = b->next;
		index++;
	}
}