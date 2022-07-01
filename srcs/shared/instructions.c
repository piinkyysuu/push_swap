/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:48:59 by thule             #+#    #+#             */
/*   Updated: 2022/07/01 19:52:56 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

void push(t_stack **a, t_stack **b)
{
	t_stack *tmp;
	t_stack *b_new_head;

	if (!(*b))
		return;
	tmp = *b;
	b_new_head = (*b)->next;
	if (!(*a))
	{
		*a = tmp;
		(*a)->next = NULL;
	}
	else
	{
		tmp->next = (*a);
		(*a) = tmp;
	}
	*b = b_new_head;
}

void reverse_rotate(t_stack **head)
{
	t_stack *tmp;
	t_stack *current;

	if (!(*head) || !((*head)->next))
		return;
	current = *head;
	while (current->next)
	{
		if ((current->next)->next == NULL)
		{
			tmp = current->next;
			current->next = NULL;
			break;
		}
		current = current->next;
	}
	tmp->next = *head;
	*head = tmp;
}

void rotate(t_stack **head)
{
	t_stack *tmp;
	t_stack *current;

	if (!(*head) || !((*head)->next))
		return;
	tmp = *head;
	*head = (*head)->next;
	current = *head;
	while (current->next)
		current = current->next;
	current->next = tmp;
	tmp->next = NULL;
}

void swap(t_stack **head)
{
	t_stack *tmp;

	tmp = *head;
	if (!tmp || !(tmp->next))
		return;
	*head = (*head)->next;
	tmp->next = (*head)->next;
	(*head)->next = tmp;
}