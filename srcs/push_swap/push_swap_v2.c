/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_v2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 13:28:16 by thle              #+#    #+#             */
/*   Updated: 2022/08/24 20:42:37 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Aims for merge sort method for bigger than 5 */

#include "push_swap.h"

#define EMPTY LONG_MIN

int global_count = 1;

void print_intial_a(t_stack *a);
void process_and_print_op(t_op **head, char *op, t_stack **a, t_stack **b);
void print_op(t_op *op);

t_info g_a;
t_info g_b;

int get_pos(t_stack *stack, int value)
{
	t_stack *tmp = stack;
	int pos = 1;

	while (tmp)
	{
		if (tmp->value == value)
			return pos;
		pos++;
		tmp = tmp->next;
	}
	return (0);
}

t_stack *copy_stack(t_stack *stack, int amount)
{
	t_stack *tmp;
	t_stack *head;

	if (amount > 0 && stack)
	{
		head = create_new_element(stack->value);
		amount--;
		tmp = head;
		stack = stack->next;
		while (stack && amount > 0)
		{
			tmp->next = create_new_element(stack->value);
			tmp = tmp->next;
			stack = stack->next;
			amount--;
		}
		return head;
	}
	return (NULL);
}

void initialize_info(t_info *stack, char name)
{
	stack->name = name;
	stack->head = NULL;
	stack->sorted = NULL;

	stack->sorted_amount = 0;

	stack->splitted = 0;
	stack->min = 0;
	stack->max = 0;
	stack->hold = NULL;

	stack->op[4] = "\0";
	stack->op[PUSH] = "pa";
	stack->op[SWAP] = "sa";
	stack->op[ROT] = "ra";
	stack->op[R_ROT] = "rra";
	if (stack->name == 'b')
	{
		stack->op[PUSH] = "pb";
		stack->op[SWAP] = "sb";
		stack->op[ROT] = "rb";
		stack->op[R_ROT] = "rrb";
	}
}

int split_stack(t_op **op, t_info *a, t_info *b, int stack_size)
{
	t_info *container;
	int other_stack_size;

	container = b;
	other_stack_size = stack_size / 2;
	if (b->splitted == 1)
		container = a;
	while (other_stack_size-- > 0)
		process_and_print_op(op, container->op[PUSH], &(a->head), &(b->head));
	a->splitted = 0;
	b->splitted = 0;
	return (stack_size / 2);
}

t_stack *retrieve_node(t_stack **stack, int value)
{
	t_stack *prev;
	t_stack *tmp;

	tmp = *stack;
	prev = NULL;
	if (tmp && tmp->value == value)
	{
		*stack = (*stack)->next;
		tmp->next = NULL;
		return tmp;
	}
	while (tmp->next)
	{
		if (value == tmp->value)
			break;
		prev = tmp;
		tmp = tmp->next;
	}
	prev->next = tmp->next;
	tmp->next = NULL;
	return tmp;
}

long get_value(t_stack *stack, int value, int order)
{
	long hold;

	hold = LONG_MIN;
	if (order == ASC)
		hold = LONG_MAX;
	while (stack)
	{
		if (stack->value < value && hold < stack->value && order == DESC)
			hold = stack->value;
		if (stack->value > value && hold > stack->value && order == ASC)
			hold = stack->value;
		stack = stack->next;
	}
	return hold;
}

void print_op_test(t_op *op)
{
	while (op)
	{
		if (op->op[0] != '0')
			printf("%s%s%s ", GREEN, op->op, WHITE);
		else
			printf("%s%s%s ", MAGENTA, op->op, WHITE);
		op = op->next;
	}
	printf("\n");

	// while (op)
	// {
	// 	if (op->op[0] != '0')
	// 		printf("%s\n", op->op);
	// 	op = op->next;
	// }
}

// void cancel_instruction_helper(t_op *op, char *instruction, char *counter)
// {
// 	t_op *tmp = op;

// 	op = op->next;
// 	while (op)
// 	{
// 		if (!ft_strcmp(op->op, counter))
// 		{
// 			tmp->op = "0";
// 			op->op = "0";
// 			return;
// 		}
// 		else if (op->stack == tmp->stack)
// 			return;
// 		op = op->next;
// 	}
// }

// void cancel_instruction(t_op *op)
// {
// 	t_op *tmp;

// 	tmp = op;
// 	while (tmp)
// 	{
// 		if (!ft_strcmp("ra", tmp->op))
// 			cancel_instruction_helper(tmp, "ra", "rra");
// 		else if (!ft_strcmp("rb", tmp->op))
// 			cancel_instruction_helper(tmp, "rb", "rrb");
// 		else if (!ft_strcmp("rra", tmp->op))
// 			cancel_instruction_helper(tmp, "rra", "ra");
// 		else if (!ft_strcmp("rrb", tmp->op))
// 			cancel_instruction_helper(tmp, "rrb", "rb");
// 		tmp = tmp->next;
// 	}
// }

void print_instruction_final(t_op *op)
{
	t_op *hold;
	t_op *tmp;

	if (op->next == NULL)
		return;
	while (op)
	{
		if (op->op[0] != '0' && ft_strlen(op->op) < 3)
		{
			tmp = op;
			if (op->op[0] == 's' && op->op[1] == 'a')
			{
				while (tmp)
				{
					if (tmp->op[0] == 's' && tmp->op[1] == 'b')
					{
						op->op = "ss";
						tmp->op = "0";
						break;
					}
					tmp = tmp->next;
				}
			}
			else if (op->op[0] == 's' && op->op[1] == 'b')
			{
				while (tmp)
				{
					if (tmp->op[0] == 's' && tmp->op[1] == 'a')
					{
						op->op = "ss";
						tmp->op = "0";
						break;
					}
					tmp = tmp->next;
				}
			}
			else if (op->op[0] == 'r' && op->op[1] == 'a')
			{
				while (tmp)
				{
					if (tmp->op[0] == 'r' && tmp->op[1] == 'b')
					{
						op->op = "rr";
						tmp->op = "0";
						break;
					}
					tmp = tmp->next;
				}
			}
			else if (op->op[0] == 'r' && op->op[1] == 'b')
			{
				while (tmp)
				{
					if (tmp->op[0] == 'r' && tmp->op[1] == 'a')
					{
						op->op = "rr";
						tmp->op = "0";
						break;
					}
					tmp = tmp->next;
				}
			}
		}
		op = op->next;
	}
}

t_op *clean_instruction(t_op *op)
{
	t_op *tmp;
	t_op *hold;

	tmp = op;
	hold = NULL;
	while (tmp)
	{
		if (!ft_strcmp("pa", tmp->op) || !ft_strcmp("pb", tmp->op))
			break;
		hold = tmp;
		tmp = tmp->next;
	}
	hold->next = NULL;
	// cancel_instruction(op);
	// print_instruction_final(op);
	print_op_test(op);
	return tmp;
}

void optimize_instruction(t_op **op)
{
	int pos = 1;
	t_op *tmp = *op;
	t_op *hold = NULL;

	while (tmp)
	{
		if (tmp->op[0] == 'p')
		{
			hold = tmp;
			tmp = tmp->next;
			// printf("%s\n", hold->op);
			free(hold);
			continue;
		}
		else
		{
			tmp = clean_instruction(tmp);
			continue;
		}
		tmp = tmp->next;
	}
}

int main(int argc, char *argv[])
{
	t_stack *stack;

	t_op *op = NULL;
	int pos = 1;

	initialize_info(&g_a, 'a');
	initialize_info(&g_b, 'b');

	int amount = create_stack(argc, argv, &(g_a.head));
	if (!amount)
		write(2, "Error\n", 6);
	else
	{
		global_count = 1;
		print_intial_a(g_a.head);
		// print_2_stacks(g_a.head, g_b.head);
		merge_sort(&op, &g_a, &g_b, get_size(g_a.head));
		// print_op_test(op);
		// optimize_instruction(&op);


		t_op *tmp = op;
		while (tmp)
		{
			if (!ft_strcmp(tmp->op, "pb") || !ft_strcmp(tmp->op, "pa"))
				printf("%s%d: %s%s%s\n", MAGENTA, pos, RED, tmp->op, WHITE);
			else
				printf("%s%d: %s%s%s\n", MAGENTA, pos, YELLOW, tmp->op, WHITE);
			pos++;
			tmp = tmp->next;
		}
		if (is_stack_sorted(&(g_a.head)) && !(g_b.head))
			printf("%sSORTED%s %d\n%s", GREEN, YELLOW,pos, WHITE);
		else
			printf("%sNOT SORTED%s %d%s\n", RED, YELLOW, pos, WHITE);
	}
	exit(1);
	return (1);
}

/* later use */

int get_size(t_stack *stack)
{
	t_stack *tmp;
	int pos = 0;

	tmp = stack;
	pos = 0;
	while (tmp)
	{
		pos++;
		tmp = tmp->next;
	}
	return (pos);
}

long get_last(t_stack *stack)
{
	t_stack *tmp;

	tmp = stack;
	if (!tmp)
		return EMPTY;
	while (tmp->next)
		tmp = tmp->next;
	return tmp->value;
}

long get_first(t_stack *stack)
{
	if (!stack)
		return EMPTY;
	else
		return stack->value;
}

long get_max(t_stack *stack)
{
	t_stack *tmp;
	int max;

	tmp = stack;
	if (!tmp)
		return EMPTY;
	max = tmp->value;
	tmp = tmp->next;
	while (tmp)
	{
		if (max < tmp->value)
			max = tmp->value;
		tmp = tmp->next;
	}
	return max;
}

long get_min(t_stack *stack)
{
	t_stack *tmp;
	int min;

	tmp = stack;
	if (!tmp)
		return EMPTY;
	min = tmp->value;
	tmp = tmp->next;
	while (tmp)
	{
		if (min > tmp->value)
			min = tmp->value;
		tmp = tmp->next;
	}
	return min;
}

/* trivia functions */
void print_op(t_op *op)
{
	t_op *tmp = op;
	int index = 0;
	while (tmp)
	{
		tmp = tmp->next;
		index++;
	}
	printf("\ncount: %d", index);
	printf("\n");
}

void print_intial_a(t_stack *a)
{
	t_stack *tmp = a;
	printf("%s", MAGENTA);
	while (tmp)
	{
		printf("%d ", tmp->value);
		tmp = tmp->next;
	}
	printf("\n%s", WHITE);
}
