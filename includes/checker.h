/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 14:42:24 by thule             #+#    #+#             */
/*   Updated: 2022/07/04 15:18:06 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //needs removing afterward
#include <stdlib.h> //needs removing afterward
#include <stdbool.h>
#include <limits.h>

#include "libft.h"
#include "shared.h"


#define STACK_EMPTY LONG_MIN

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