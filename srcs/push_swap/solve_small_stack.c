/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_small_i.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:06:05 by thle              #+#    #+#             */
/*   Updated: 2022/09/02 16:29:19 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	solve_stack_of_three(t_op **op, t_info *i)
{
	int	size;
	int	f;
	int	s;
	int	t;

	size = get_size(i->head);
	while (size == 3)
	{
		f = i->head->value;
		s = i->head->next->value;
		t = i->head->next->next->value;
		if ((s > f && s > t && i->name == 'a')
			|| (s < f && s < t && i->name == 'b'))
			optimize_then_print_op(op, i->op[R_ROT], &(i->head), &(i->head));
		else if ((f > t && f > s && i->name == 'a')
			|| (f < t && f < s && i->name == 'b'))
			optimize_then_print_op(op, i->op[ROT], &(i->head), &(i->head));
		else if ((s < f && i->name == 'a')
			|| (s > f && i->name == 'b'))
			optimize_then_print_op(op, i->op[SWAP], &(i->head), &(i->head));
		else
			return ;
	}
}

static void	solve_top_three_helper(t_op **op, t_info *i)
{
	int	f;
	int	s;
	int	t;

	f = i->head->value;
	s = i->head->next->value;
	t = i->head->next->next->value;
	optimize_then_print_op(op, i->op[ROT], &(i->head), &(i->head));
	optimize_then_print_op(op, i->op[SWAP], &(i->head), &(i->head));
	optimize_then_print_op(op, i->op[R_ROT], &(i->head), &(i->head));
	if ((f < s && s > t && f > t && i->name == 'a')
		|| (f > s && s < t && f < t && i->name == 'b'))
		optimize_then_print_op(op, i->op[SWAP], &(i->head), &(i->head));
	else if ((t < s && s < f && i->name == 'a')
		|| (t > s && s > f && i->name == 'b'))
	{
		optimize_then_print_op(op, i->op[SWAP], &(i->head), &(i->head));
		optimize_then_print_op(op, i->op[ROT], &(i->head), &(i->head));
		optimize_then_print_op(op, i->op[SWAP], &(i->head), &(i->head));
		optimize_then_print_op(op, i->op[R_ROT], &(i->head), &(i->head));
	}
}

static void	solve_top_three(t_op **op, t_info *i)
{
	int	f;
	int	s;
	int	t;

	f = i->head->value;
	s = i->head->next->value;
	t = i->head->next->next->value;
	if ((f < s && s < t && i->name == 'a')
		|| (f > s && s > t && i->name == 'b'))
		return ;
	else if ((f > s && s < t && t > f && i->name == 'a')
		|| (f < s && s > t && t < f && i->name == 'b'))
		optimize_then_print_op(op, i->op[SWAP], &(i->head), &(i->head));
	else if ((f > s && f > t && s < t && i->name == 'a')
		|| (f < s && f < t && s > t && i->name == 'b'))
	{
		optimize_then_print_op(op, i->op[SWAP], &(i->head), &(i->head));
		optimize_then_print_op(op, i->op[ROT], &(i->head), &(i->head));
		optimize_then_print_op(op, i->op[SWAP], &(i->head), &(i->head));
		optimize_then_print_op(op, i->op[R_ROT], &(i->head), &(i->head));
	}
	else
		solve_top_three_helper(op, i);
}

void	solve_three(t_op **op, t_info *i, int amount)
{
	int	size;

	size = get_size(i->head);
	if (amount == 1 || size == 1)
		return ;
	if (amount <= 2 && size >= 2)
	{
		if ((i->head->value > i->head->next->value && i->name == 'a')
			|| (i->head->value < i->head->next->value && i->name == 'b'))
			optimize_then_print_op(op, i->op[SWAP], &(i->head), &(i->head));
		return ;
	}
	if (size == 3)
		solve_stack_of_three(op, i);
	else
		solve_top_three(op, i);
}
