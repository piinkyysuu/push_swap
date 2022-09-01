/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:55:23 by thule             #+#    #+#             */
/*   Updated: 2022/09/01 17:14:02 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

int is_stack_sorted(t_stack *head)
{
	t_stack *tmp;
	int value;

	tmp = head;
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
