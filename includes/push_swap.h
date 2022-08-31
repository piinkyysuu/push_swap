/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:46:00 by thule             #+#    #+#             */
/*   Updated: 2022/08/31 20:28:29 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>	//needs removing afterward
#include <stdlib.h> //needs removing afterward
#include <stdbool.h>
#include <limits.h>

#include "libft.h"
#include "shared.h"

#define ASC 2
#define DESC 1

typedef struct s_op
{
	char *op;
	char stack;
	short int operation;
	struct s_op *next;
} t_op;

typedef struct s_info
{
	char name;
	t_stack *head;
	t_stack **hold;
	int splitted;
	char *op[5];
} t_info;

/* main.c */
int get_size(t_stack *stack);
long get_min(t_stack *stack);
long get_max(t_stack *stack);

/* process_and_print_op.c */
void process_and_print_op(t_op **head, char *op, t_stack **a, t_stack **b);
void central_customization(t_op **first);
void link_first_and_second(t_op *first, t_op *first_tail, t_op *second_head);
t_op *split_instructions(t_op *first);
void print_then_del_op(t_op **head);
void append_op_list(t_op **head, char *op);

/* optimize.ops.c */
void cancel_rotate(t_op *op);
void cancel_rotate_helper(t_op *op, char *instruction, char *counter);
void cancel_push(t_op *first, t_op *second);
void change_op(t_op *first, t_op *second);
void combine_op(t_op *first, t_op *second);

/* solve_small_stack.c */
void solve_three(t_op **op, t_info *stack, int amount);

/* solve_big_stack.c */
void merge_sort(t_op **op, t_info *a, t_info *b, int stack_size);
t_stack *merge_sort_stack_a(t_op **op, t_info *a, t_info *b, int stack_size);
t_stack *merge_sort_stack_b(t_op **op, t_info *a, t_info *b, int stack_size);
void merge_to_stack_a(t_op **op, t_info *a, t_info *b);
void merge_to_stack_b(t_op **op, t_info *a, t_info *b);

/* solve_big_stack_helper.c */
int split_stack(t_op **op, t_info *a, t_info *b, int stack_size);
t_stack *retrieve_node(t_stack **stack, int value);
int get_pos(t_stack *stack, int value);
long get_value(t_stack *stack, int value, int order);

/* rotate_utils.c */
void rotate_to_top(t_op **op, t_info *stack, int pos);
void rotate_to_bottom(t_op **op, t_info *stack, int pos);
