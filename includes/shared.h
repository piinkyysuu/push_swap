/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:46:18 by thule             #+#    #+#             */
/*   Updated: 2022/09/01 18:11:28 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H

# include <stdlib.h>
# include "libft.h"

# define OP_INDEX "000111222"

typedef struct s_stack
{
	int				value;
	struct s_stack	*next;
}					t_stack;

enum e_instructions
{
	sa,
	ra,
	rra,
	sb,
	rb,
	rrb,
	ss,
	rr,
	rrr,
	pa,
	pb
};

enum e_op
{
	SWAP,
	ROT,
	R_ROT,
	PUSH
};

/* operations.c */
void	swap(t_stack **head);
void	rotate(t_stack **head);
void	reverse_rotate(t_stack **head);
void	push(t_stack **a, t_stack **b);

/* stack_utils.c */
t_stack	*create_new_element(int value);
int		is_stack_sorted(t_stack *head);
void	delete_stack(t_stack **head);

/* create_stack.c */
int		create_stack(int amount, char *array[], t_stack **head);

/* apply_op.c */
int		apply_op(char *op, t_stack **a, t_stack **b);

#endif