/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:46:18 by thule             #+#    #+#             */
/*   Updated: 2022/07/01 19:19:16 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include <stdio.h>

typedef struct s_stack
{
	int value;
	struct s_stack *next;
} t_stack;

/* instructions.c */
void swap(t_stack **head);
void rotate(t_stack **head);
void reverse_rotate(t_stack **head);
void push(t_stack **a, t_stack **b);

/* stack_utils.c */
void delete_stack(t_stack **head);
t_stack *create_new_element(int value);

/* create_stack.c */
int create_stack(int amount, char *array[], t_stack **head);
