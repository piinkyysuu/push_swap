/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:46:18 by thule             #+#    #+#             */
/*   Updated: 2022/08/25 13:34:38 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include <stdio.h> //rmb to delete

#define NORMAL "\x1B[0m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN "\x1B[36m"
#define WHITE "\x1B[37m"

#define OP_INDEX "000111222"

typedef struct s_stack
{
	int value;
	struct s_stack *next;
} t_stack;

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
	SWAP, //0
	ROT, //1
	R_ROT, //2
	PUSH //3
};

/* operations.c */
void swap(t_stack **head);
void rotate(t_stack **head);
void reverse_rotate(t_stack **head);
void push(t_stack **a, t_stack **b);

/* stack_utils.c */
int is_stack_sorted(t_stack **head);
void delete_stack(t_stack **head);
t_stack *create_new_element(int value);
void print_stack(t_stack *head, char c);
int count_stack(t_stack **head);
void print_2_stacks(t_stack *a, t_stack *b);

/* create_stack.c */
int create_stack(int amount, char *array[], t_stack **head);

/* apply_op.c */
int	apply_op(char *op, t_stack **a, t_stack **b);
