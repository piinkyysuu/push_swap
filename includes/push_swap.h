/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:46:00 by thule             #+#    #+#             */
/*   Updated: 2022/08/25 16:23:24 by thle             ###   ########.fr       */
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
	t_stack *sorted;

	t_stack **hold;

	int sorted_start;
	int sorted_end;
	int sorted_amount;

	int splitted;

	int min;
	int max;

	char *op[5];
} t_info;

/* main.c */
int is_sorted(t_stack *stack, int order);
int get_size(t_stack *stack);
long get_first(t_stack *stack);
long get_last(t_stack *stack);
long get_min(t_stack *stack);
long get_max(t_stack *stack);
int get_pos(t_stack *stack, int value);
long get_value(t_stack *stack, int value, int order);
t_stack *retrieve_node(t_stack **stack, int value);
t_stack *copy_stack(t_stack *stack, int amount);
int split_stack(t_op **op, t_info *a, t_info *b, int stack_size);

void print_offical(t_op *head);
void process_and_print_op(t_op **head, char *op, t_stack **a, t_stack **b);

/* solve_small_stack.c */
void solve_three(t_op **op, t_info *stack, int amount);
void solve_five(t_op **op, t_info *a, t_info *b);

/* solve_big_stack.c */
void merge_sort(t_op **op, t_info *a, t_info *b, int stack_size);
t_stack *merge_sort_stack_a(t_op **op, t_info *a, t_info *b, int stack_size);
t_stack *merge_sort_stack_b(t_op **op, t_info *a, t_info *b, int stack_size);
void merge_to_stack_a(t_op **op, t_info *a, t_info *b);
void merge_to_stack_b(t_op **op, t_info *a, t_info *b);

/* rotate_utils.c */
void rotate_to_top(t_op **op, t_info *stack, int pos);
void rotate_to_bottom(t_op **op, t_info *stack, int pos);
