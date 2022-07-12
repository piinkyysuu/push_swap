/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:55:23 by thule             #+#    #+#             */
/*   Updated: 2022/07/12 18:01:00 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

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