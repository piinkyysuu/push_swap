/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_v2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 13:28:16 by thle              #+#    #+#             */
/*   Updated: 2022/08/09 17:50:24 by thule            ###   ########.fr       */
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

typedef struct s_info
{
	char name;
	t_stack *head;
	int sorted_start;
	int sorted_end;
	int sorted_amount;
} t_info;

int get_size(t_stack *stack);
long get_first(t_stack *stack);
long get_last(t_stack *stack);
long get_min(t_stack *stack);
long get_max(t_stack *stack);

void print_intial_a(t_stack *a);
void append_ops(t_op **head, char *op, t_stack **a, t_stack **b);
void solve_a_max_3(t_op **op, t_stack **stack);
int solve_b_max_3(t_op **op, t_stack **stack);
void print_op(t_op *op);

void print_info(t_info *stack)
{
	printf("%s%c%s: ", CYAN, stack->name, WHITE);
	printf("[sorted:%3d] ", stack->sorted_amount);
	printf("[start:%3d] ", stack->sorted_start);
	printf("[end:%3d]\n", stack->sorted_end);
}

void push_to_b(t_op **op, t_info *a, t_info *b, int amount)
{
	while (amount > 0 && a->head)
	{
		append_ops(op, "pb", &(a->head), &(b->head));
		amount--;
	}
}

void update_info(t_info *stack)
{
	int pos = 1;
	t_stack *tmp = stack->head;

	if (stack->name == 'b')
	{
		stack->sorted_start = get_max(stack->head);
		stack->sorted_end = get_min(stack->head);
		stack->sorted_amount = get_size(stack->head);
		return;
	}
	stack->sorted_start = tmp->value;
	while (tmp && pos < stack->sorted_amount)
	{
		tmp = tmp->next;
		pos++;
	}
	stack->sorted_end = tmp->value;
}

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

void rotate_to_top(t_op **op, t_info *stack, int pos)
{
	int stack_size;

	stack_size = get_size(stack->head);
	if (pos == stack_size + 1)
		return;
	if (stack->name == 'b')
	{
		if (pos > stack_size / 2)
		{
			while (pos++ < stack_size + 1)
				append_ops(op, "rrb", NULL, &(stack->head));
		}
		else
		{
			while (pos-- > 1)
				append_ops(op, "rb", NULL, &(stack->head));
		}
	}
	else
	{
		if (pos > stack_size / 2)
		{
			while (pos++ < stack_size + 1)
				append_ops(op, "rra", &(stack->head), NULL);
		}
		else
		{
			while (pos-- > 1)
				append_ops(op, "ra", &(stack->head), NULL);
		}
	}
}

void rotate_to_bottom(t_op **op, t_info *stack, int pos)
{
	int stack_size = get_size(stack->head);

	while (pos > 0 && pos++ < stack_size)
	{
		append_ops(op, "rra", &(stack->head), NULL);
	}
}

void merge_to_b(t_op **op, t_info *a, t_info *b, int amount)
{
	printf("amount = %d\n", amount);
	if (b->sorted_amount > 0)
	{
		while (amount > 0 && b->sorted_amount > 0)
		{
			printf("a_first: %ld, b_last: %ld\n", get_first(a->head), get_last(b->head));
			if (get_first(a->head) > get_last(b->head))
			{
				printf("get_first(a->head) > get_last(b->head)\n");
				append_ops(op, "rrb", &(a->head), &(b->head));
				b->sorted_amount--;
			}
			else
			{
				printf("else\n");
				append_ops(op, "pb", &(a->head), &(b->head));
				amount--;
			}
		}
		while (b->sorted_amount-- > 0)
			append_ops(op, "rrb", &(a->head), &(b->head));
		while (amount-- > 0)
			append_ops(op, "pb", &(a->head), &(b->head));
	}
	else
	{
		push_to_b(op, a, b, amount);
		solve_b_max_3(op, &(b->head));
	}
	update_info(b);
	printf("end\n");
}

void merge_to_a(t_op **op, t_info *a, t_info *b)
{
	int res = a->sorted_amount + b->sorted_amount;

	while (a->sorted_amount && b->sorted_amount)
	{
		if (get_first(b->head) < get_last(a->head))
		{
			append_ops(op, "rra", &(a->head), &(b->head));
			a->sorted_amount--;
		}
		else
		{
			append_ops(op, "pa", &(a->head), &(b->head));
			b->sorted_amount--;
		}
	}
	while (a->sorted_amount-- > 0)
		append_ops(op, "rra", &(a->head), &(b->head));
	while (b->sorted_amount-- > 0)
		append_ops(op, "pa", &(a->head), &(b->head));
	a->sorted_amount = res;
	update_info(a);
}

void solve_top_a(t_op **op, t_info *a, t_info *b, int amount)
{
	int first;
	int second;
	int third;

	if (amount == 1)
		return;
	if (amount == 2 && a->head->value > a->head->next->value)
		append_ops(op, "sa", &(a->head), &(b->head));
	else if (amount == 3)
	{
		first = a->head->value;
		second = a->head->next->value;
		third = a->head->next->next->value;
		if (first < second && second < third)
			return;
		else if (first < second && first < third && second > third)
		{
			append_ops(op, "pb", &(a->head), &(b->head));
			append_ops(op, "sa", &(a->head), &(b->head));
			append_ops(op, "pa", &(a->head), &(b->head));
		}
		else if (first > second && second < third && third > first)
			append_ops(op, "sa", &(a->head), &(b->head));
		else if (first < second && second > third && first > third)
		{
			append_ops(op, "pb", &(a->head), &(b->head));
			append_ops(op, "sa", &(a->head), &(b->head));
			append_ops(op, "pa", &(a->head), &(b->head));
			append_ops(op, "sa", &(a->head), &(b->head));
		}
		else if (third < second && second < first)
		{
			append_ops(op, "ra", &(a->head), &(b->head));
			append_ops(op, "sa", &(a->head), &(b->head));
			append_ops(op, "pb", &(a->head), &(b->head));
			append_ops(op, "rra", &(a->head), &(b->head));
			append_ops(op, "sa", &(a->head), &(b->head));
			append_ops(op, "pa", &(a->head), &(b->head));
		}
		else
		{
			append_ops(op, "pb", &(a->head), &(b->head));
			append_ops(op, "pb", &(a->head), &(b->head));
			append_ops(op, "sb", &(a->head), &(b->head));
			append_ops(op, "pa", &(a->head), &(b->head));
			append_ops(op, "sa", &(a->head), &(b->head));
			append_ops(op, "pa", &(a->head), &(b->head));
		}
	}
}

void merge(t_op **op, t_info *a, t_info *b)
{
	int a_size = get_size(a->head);
	int remainder = 3;

	// merge_to_b(op, a, b, 3);
	solve_top_a(op, a, b, 3);
	a->sorted_amount = 3;
	a->sorted_start = (a->head)->value;
	a->sorted_end = (a->head)->next->next->value;

	while (a->sorted_amount < a_size)
	{
		printf("%soutter loop%s\n", GREEN, WHITE);
		while (b->sorted_amount < a->sorted_amount && a->sorted_amount != get_size(a->head))
		{
			printf("%sinner loop%s\n", RED, WHITE);
			remainder = a_size - a->sorted_amount - get_size(b->head);
			if (remainder <= 0)
			{
				printf("%sbreak%s\n", RED, WHITE);
				break;
			}
			else if (remainder > 3)
				remainder = 3;
			int rotate = remainder;
			printf("remainder: %d\n", remainder);
			while (rotate-- > 0)
				append_ops(op, "rra", &(a->head), &(b->head));
			print_2_stacks(a->head, b->head);
			if (!(b->head))
			{
				merge_to_b(op, a, b, remainder);
				continue;
			}
			else
			{
				solve_top_a(op, a, b, remainder);
				printf("%ssolve_top_a%s\n", MAGENTA, WHITE);
				print_2_stacks(a->head, b->head);
				merge_to_b(op, a, b, remainder);
			}
			print_2_stacks(a->head, b->head);
		}
		if (a->sorted_amount != get_size(a->head))
		{
			rotate_to_bottom(op, a, get_pos(a->head, a->sorted_end));
		}
		print_2_stacks(a->head, b->head);
		merge_to_a(op, a, b);
		print_2_stacks(a->head, b->head);
	}
}

int main(int argc, char *argv[])
{
	t_info a;
	t_info b;

	t_op *op = NULL;
	int pos = 1;

	a = (t_info){.name = 'a', .head = NULL, 0, 0, 0};
	b = (t_info){.name = 'b', .head = NULL, 0, 0, 0};

	int amount = create_stack(argc, argv, &(a.head));
	if (!amount)
		write(2, "Error\n", 6);
	else
	{
		printf("amount: %d\n", amount);
		print_intial_a(a.head);

		print_2_stacks(a.head, b.head);
		merge(&op, &a, &b);
		printf("\n");
		print_2_stacks(a.head, b.head);
		while (op)
		{
			pos++;
			op = op->next;
		}
		printf("pos: %d\n", pos);
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

int solve_b_max_3(t_op **op, t_stack **stack)
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
			return size;
	}
	if (size == 2 && (*stack)->value < ((*stack)->next)->value)
	{
		append_ops(op, "sb", NULL, stack);
		return size;
	}
	return size;
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
