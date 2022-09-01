/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:46:00 by thule             #+#    #+#             */
/*   Updated: 2022/09/01 18:08:40 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include "libft.h"
# include "shared.h"

# define ASC 2
# define DESC 1
# define EMPTY LONG_MIN

typedef struct s_op
{
	char		*op;
	char		stack;
	short int	operation;
	short int	len;
	struct s_op	*next;
}				t_op;

typedef struct s_info
{
	t_stack		*head;
	t_stack		**hold;
	char		*op[5];
	short int	splitted;
	char		name;
}				t_info;

/* solve_small_stack.c */
void	solve_three(t_op **op, t_info *stack, int amount);

/* solve_big_stack.c */
t_stack	*merge_sort_stack_a(t_op **op, t_info *a, t_info *b, int stack_size);
t_stack	*merge_sort_stack_b(t_op **op, t_info *a, t_info *b, int stack_size);
void	merge_sort(t_op **op, t_info *a, t_info *b, int stack_size);
void	merge_to_stack_a(t_op **op, t_info *a, t_info *b);
void	merge_to_stack_b(t_op **op, t_info *a, t_info *b);

/* solve_big_stack_helper.c */
t_stack	*retrieve_node(t_stack **stack, int value);
t_stack	*copy_stack(t_stack *stack, int amount);
int		split_stack(t_op **op, t_info *a, t_info *b, int stack_size);

/* optimize_then_print_op.c */
void	optimize_then_print_op(t_op **head, char *op, t_stack **a, t_stack **b);
void	central_customization(t_op **first);
void	print_then_del_op(t_op **head);

/* optimize.ops.c */
void	cancel_rotate(t_op *op);
void	cancel_rotate_helper(t_op *op, char *instruction, char *counter);
void	cancel_push(t_op *first, t_op *second);
void	change_op(t_op *first, t_op *second);
void	combine_op(t_op *first, t_op *second);

/* rotate_utils.c */
void	rotate_to_top(t_op **op, t_info *stack, int pos);
void	rotate_to_bottom(t_op **op, t_info *stack, int pos);

/* utils.c */
int		get_size(t_stack *stack);
int		get_pos(t_stack *stack, int value);
long	get_min(t_stack *stack);
long	get_max(t_stack *stack);
long	get_value(t_stack *stack, int value, int order);

/* op_utils.c */
t_op	*split_instructions(t_op *first);
void	link_two_op_lists(t_op *first, t_op *first_tail, t_op *second_head);
void	print_then_del_op(t_op **head);
void	append_op_list(t_op **head, char *op);
void	update_op_node(t_op *node, char *op);

#endif
