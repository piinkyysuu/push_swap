/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 14:42:24 by thule             #+#    #+#             */
/*   Updated: 2022/06/29 13:29:37 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //needs removing afterward
#include <stdlib.h> //needs removing afterward
#include <stdbool.h>
#include <limits.h>


#define STACK_EMPTY LONG_MIN

typedef struct s_stack
{
	int value;
	struct s_stack *next;
} t_stack;