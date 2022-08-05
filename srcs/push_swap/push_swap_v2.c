/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_v2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 13:28:16 by thle              #+#    #+#             */
/*   Updated: 2022/08/05 18:24:16 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Aims for merge sort method for bigger than 5 */

#include "push_swap.h"

#define ASC 2
#define DESC 1

#define EMPTY LONG_MIN

typedef struct s_op
{
	char *op;
	struct s_op *next;
} t_op;

int get_size(t_stack *stack);
long get_first(t_stack *stack);
long get_last(t_stack *stack);
long get_min(t_stack *stack);
long get_max(t_stack *stack);

void print_intial_a(t_stack *a);
void append_ops(t_op **head, char *op, t_stack **a, t_stack **b);
void solve_a_max_3(t_op **op, t_stack **stack);
void solve_b_max_3(t_op **op, t_stack **stack);
void print_op(t_op *op);

int merge_to_a(t_op **op, t_stack **a, t_stack **b, int amount)
{
	int res = get_size(*b) + amount;
	
	while (*b)
	{
		if (get_last(*a) > (*b)->value && amount > 0)
		{
			append_ops(op, "rra", a, b);
			amount--;
			continue;
		}
		append_ops(op, "pa", a, b);
	}
	while (amount-- > 0)
		append_ops(op, "rra", a, b);
	return res;
}

int merge_to_b(t_op **op, t_stack **a, t_stack **b, int amount)
{
	int b_size; 
	
	b_size = get_size(*b);
	while (*a && amount)
	{
		if ((*a)->value > get_last(*b) && b_size > 0)
		{
			append_ops(op, "rrb", a, b);
			b_size--;
			continue;
		}
		append_ops(op, "pb", a, b);
		amount--;
	}
	while (b_size-- > 0)
		append_ops(op, "rrb", a, b);
	return get_size(*b);
}

void split_in_half(t_op **op, char stack, t_stack **a, t_stack **b)
{
	int size;

	size = get_size(*a) / 2;
	while (size)
	{
		if (stack == 'a')
			append_ops(op, "pb", a, b);
		else 
			append_ops(op, "pa", a, b);
		size--;
	}
}

void push_less_than_3(t_op **op, t_stack **a, t_stack **b, int amount)
{
	while (*a && amount)
	{
		append_ops(op, "pb", a, b);
		amount--;
	}
}

void solve_first_a(t_op **op, t_stack **a, int amount)
{
	t_stack *tmp = *a;
	int first = -1;
	int second = -1;
	int third = -1;

	if (amount == 2 && tmp->next->next)
	{
		first = tmp->value;
		second = tmp->next->value;
		if (first < second)
			return ;
		else
			append_ops(op, "sa", a, NULL);
	}
	else if (amount == 3 &&  tmp->next->next->next)
	{
		first = tmp->value;
		second = tmp->next->value;
		third = tmp->next->next->value;
		if (first < second && second < third)
			return ;
		else if (first < second && first < third && second > third)
		{
			append_ops(op, "ra", a, NULL);
			append_ops(op, "sa", a, NULL);
			append_ops(op, "rra", a, NULL);
		}
		else if (first > second && first < third && second < third)
			append_ops(op, "sa", a, NULL);
		else if (first < second && first > third && second > third)
		{
			append_ops(op, "ra", a, NULL);
			append_ops(op, "sa", a, NULL);
			append_ops(op, "rra", a, NULL);
			append_ops(op, "sa", a, NULL);
		}
		else if (third < second && second < first)
		{
			append_ops(op, "sa", a, NULL);
			append_ops(op, "ra", a, NULL);
			append_ops(op, "sa", a, NULL);
			append_ops(op, "rra", a, NULL);
			append_ops(op, "sa", a, NULL);
		}
		else
		{
			append_ops(op, "sa", a, NULL);
			append_ops(op, "ra", a, NULL);
			append_ops(op, "sa", a, NULL);
			append_ops(op, "rra", a, NULL);
		}
	}
}

int get_sorted_end(t_stack *a, int size)
{
	t_stack *tmp = a;

	size = size - 1;
	while (tmp->next && size)
	{
		tmp = tmp->next;
		size--;
	}
	return tmp->value;
}

int get_value_pos(t_stack *stack, int value)
{
	t_stack *tmp;
	int pos;
	
	tmp = stack;
	pos = 1;
	while (tmp)
	{
		if (tmp->value == value)
			return (pos);
		pos++;
		tmp = tmp->next;
	}
	return (0);
}

void rotate_sorted_to_bottom(t_op **op, t_stack **stack, int sorted_start, int sorted_end, int sorted_amount)
{
	int sorted_start_pos = get_value_pos(*stack, sorted_start);
	int sorted_end_pos = get_value_pos(*stack, sorted_end);
	int size = get_size(*stack);

	while (sorted_start_pos + sorted_amount - 1)
	{
		append_ops(op, "ra", stack, NULL);
		sorted_amount--;
	}
}

void merge(t_op **op, t_stack **a, t_stack **b)
{
	int a_size = get_size(*a);
	int a_sorted = 3;

	int sorted_start = 0;
	int sorted_end = 0;

	push_less_than_3(op, a, b, 3);
	solve_first_a(op, a, 3);
	sorted_start = (*a)->value;
	sorted_end = get_sorted_end(*a, 3);
	solve_b_max_3(op, b);
	
	print_2_stacks(*a, *b);
	rotate_sorted_to_bottom(op, a, sorted_start, sorted_end, a_sorted);
	print_2_stacks(*a, *b);
}

int main(int argc, char *argv[])
{
	t_stack *a = NULL;
	t_stack *b = NULL;
	t_op *op = NULL;

	int amount = create_stack(argc, argv, &a);
	if (!amount)
		write(2, "Error\n", 6);
	else
	{
		printf("amount: %d\n", amount);
		print_intial_a(a);
		
		print_2_stacks(a, b);
		merge(&op, &a, &b);
		print_2_stacks(a, b);
		// split_in_half(&op, 'a', &a, &b);
		// split_in_half(&op, 'b', &a, &b);
		// print_2_stacks(a, b);
		
		printf("\n");
		
		// print_2_stacks(a, b);
	}
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
		// printf("%s ", tmp->op);
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

void solve_b_max_3(t_op **op, t_stack **stack)
{
	int first;
	int second;
	int third;
	int size;

	size = get_size(*stack);
	while (size == 3)
	{
		first = (*stack)->value;
		second = ((*stack)->next)->value;
		third = ((*stack)->next->next)->value;
		if (second < first && second < third)
			append_ops(op, "rrb", NULL, stack);
		else if (first < third && first < second)
			append_ops(op, "rb", NULL, stack);
		else if (second > first)
			append_ops(op, "sb", NULL, stack);
		else
			break;
	}
	if (size == 2 && (*stack)->value < ((*stack)->next)->value)
		append_ops(op, "sb", NULL, stack);
}

void solve_a_max_3(t_op **op, t_stack **stack)
{
	int first;
	int second;
	int third;
	int size;

	size = get_size(*stack);
	while (size == 3)
	{
		first = (*stack)->value;
		second = ((*stack)->next)->value;
		third = ((*stack)->next->next)->value;
		if (second > first && second > third)
			append_ops(op, "rra", stack, NULL);
		else if (first > third && first > second)
			append_ops(op, "ra", stack, NULL);
		else if (second < first)
			append_ops(op, "sa", stack, NULL);
		else
			return;
	}
	if (size == 2 && (*stack)->value > ((*stack)->next)->value)
		append_ops(op, "sa", stack, NULL);
}

void append_ops(t_op **head, char *op, t_stack **a, t_stack **b)
{
	printf("%s\n", op);
	t_op *tmp;
	t_op *new;
	void (*op_array[9])(t_stack **);

	assign_index_for_op(op_array);
	if (!apply_op(op_array, op, a, b))
		exit(1);
	tmp = *head;
	new = (t_op *)malloc(sizeof(t_op));
	if (!new)
		return;
	new->op = op;
	new->next = NULL;
	while (tmp)
	{
		if (tmp->next == NULL)
		{
			tmp->next = new;
			return;
		}
		tmp = tmp->next;
	}
	if (!tmp)
		*head = new;
}
