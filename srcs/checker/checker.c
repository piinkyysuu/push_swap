/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 14:39:09 by thule             #+#    #+#             */
/*   Updated: 2022/07/05 13:21:43 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void assign_index_for_array(void (*instruction[9])(t_stack **head))
{
	instruction[sa] = swap;
	instruction[ra] = rotate;
	instruction[rra] = reverse_rotate;
	instruction[sb] = swap;
	instruction[rb] = rotate;
	instruction[rrb] = reverse_rotate;
	instruction[ss] = swap;
	instruction[rr] = rotate;
	instruction[rrr] = reverse_rotate;
}

int main(int argc, char *argv[])
{
	t_stack *a;
	t_stack *b;
	void (*instruction[9])(t_stack **);
	int result;

	a = NULL;
	b = NULL;
	assign_index_for_array(instruction);
	if (argc < 2)
		return (0);
	if (!create_stack(argc, argv, &a))
		write(2, "Error\n", 6);
	else
	{
		result = solve_stack(a, b, instruction);
		if (result == -1)
			write(2, "Error\n", 6);
		else if (result == 0)
			write(1, "KO\n", 3);
		else
			write(1, "OK\n", 3);
	}
	return (0);
}