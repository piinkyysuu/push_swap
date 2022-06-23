/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 14:39:09 by thule             #+#    #+#             */
/*   Updated: 2022/06/23 16:28:32 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "checker.h"

void print_stack(t_stack *head)
{
	t_stack *tmp = head;
	while (tmp)
	{
		printf("%d\n", tmp->value);
		tmp = tmp->next;
	}
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

void insert_at_end(t_stack **head, t_stack *element)
{
	t_stack *tmp;

	tmp = *head;
	if (!tmp)
	{
		*head = element;
	}
	else
	{
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = element;
	}
}

int main(int argc, char *argv[])
{
	t_stack *s1 = create_new_element(1);
	t_stack *s2 = create_new_element(2);
	t_stack *s3 = create_new_element(3);
	t_stack *head = NULL;

	insert_at_end(&head, s1);
	insert_at_end(&head, s2);
	insert_at_end(&head, s3);

	print_stack(head);

	return (0);
}