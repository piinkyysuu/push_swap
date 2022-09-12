/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 16:51:58 by thle              #+#    #+#             */
/*   Updated: 2022/09/12 16:28:39 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_op	*split_instructions(t_op *first)
{
	t_op	*hold;
	int		first_char;

	hold = NULL;
	while (first && first->op[0] == '0')
		first = first->next;
	if (first)
		first_char = first->stack;
	else
		return (hold);
	while (first->next)
	{
		if (first->next->stack != first_char)
		{
			hold = first->next;
			first->next = NULL;
			break ;
		}
		first = first->next;
	}
	return (hold);
}

void	link_two_op_lists(t_op *first, t_op *first_tail, t_op *second_head)
{
	if (first_tail == NULL)
	{
		while (first->next)
			first = first->next;
		first_tail = first;
	}
	first_tail->next = second_head;
}
