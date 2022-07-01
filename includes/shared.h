/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:46:18 by thule             #+#    #+#             */
/*   Updated: 2022/07/01 14:51:08 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

typedef struct s_stack
{
	int value;
	struct s_stack *next;
} t_stack;

/* instructions */
void swap(t_stack **head);
void rotate(t_stack **head);
void reverse_rotate(t_stack **head);
void push(t_stack **a, t_stack **b);