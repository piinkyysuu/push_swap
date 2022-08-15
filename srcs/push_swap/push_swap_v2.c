/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_v2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 13:28:16 by thle              #+#    #+#             */
/*   Updated: 2022/08/15 18:07:11 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Aims for merge sort method for bigger than 5 */

#include "push_swap.h"

#define ASC 2
#define DESC 1

#define EMPTY LONG_MIN

int global_count = 1;

enum e_op
{
	PUSH,
	SWAP,
	ROT,
	R_ROT
};

typedef struct s_op
{
	char *op;
	struct s_op *next;
} t_op;

typedef struct s_info
{
	char name;
	t_stack *head;
	t_stack *sorted;
	int sorted_start;
	int sorted_end;
	int sorted_amount;

	int min;
	int max;

	char *op[5];
} t_info;

int is_sorted(t_stack *stack, int order);
int get_size(t_stack *stack);
long get_first(t_stack *stack);
long get_last(t_stack *stack);
long get_min(t_stack *stack);
long get_max(t_stack *stack);

void solve_three(t_op **op, t_info *stack, int amount);
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
		append_ops(op, b->op[PUSH], &(a->head), &(b->head));
		amount--;
	}
}

void update_info(t_info *stack)
{
	int pos = 1;
	int hold = 0;
	t_stack *tmp = stack->head;

	if (stack->name == 'b')
	{
		stack->sorted_start = get_max(stack->head);
		stack->sorted_end = get_min(stack->head);
		stack->sorted_amount = get_size(stack->head);
		return;
	}
	stack->sorted_start = tmp->value;
	hold = tmp->value;
	stack->sorted_amount = 0;
	while (tmp)
	{
		if (hold > tmp->value)
		{
			stack->sorted_end = hold;
			return;
		}
		stack->sorted_amount += 1;
		hold = tmp->value;
		tmp = tmp->next;
		pos++;
	}
	stack->sorted_end = hold;
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
	if (pos == stack_size + 1 || pos == 0)
		return;
	if (pos > stack_size / 2)
	{
		while (pos++ < stack_size + 1)
			append_ops(op, stack->op[R_ROT], &(stack->head), &(stack->head));
	}
	else
	{
		while (pos-- > 1)
			append_ops(op, stack->op[ROT], &(stack->head), &(stack->head));
	}
}

void rotate_to_bottom(t_op **op, t_info *stack, int pos)
{
	int stack_size = get_size(stack->head);

	if (pos < stack_size / 2)
	{
		while (pos > 0)
		{
			append_ops(op, stack->op[ROT], &(stack->head), &(stack->head));
			pos--;
		}
		return;
	}
	while (pos > 0 && pos++ < stack_size)
	{
		append_ops(op, stack->op[R_ROT], &(stack->head), &(stack->head));
	}
}

//old, needs to fix then del
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
			// append_ops(op, "pb", &(a->head), &(b->head));
			// append_ops(op, "sa", &(a->head), &(b->head));
			// append_ops(op, "pa", &(a->head), &(b->head));

			append_ops(op, "ra", &(a->head), &(b->head));
			append_ops(op, "sa", &(a->head), &(b->head));
			append_ops(op, "rra", &(a->head), &(b->head));
		}
		else if (first > second && second < third && third > first)
		{
			append_ops(op, "sa", &(a->head), &(b->head));
		}
		else if (first < second && second > third && first > third)
		{
			// append_ops(op, "pb", &(a->head), &(b->head));
			// append_ops(op, "sa", &(a->head), &(b->head));
			// append_ops(op, "pa", &(a->head), &(b->head));
			// append_ops(op, "sa", &(a->head), &(b->head));

			append_ops(op, "ra", &(a->head), &(b->head));
			append_ops(op, "sa", &(a->head), &(b->head));
			append_ops(op, "rra", &(a->head), &(b->head));
			append_ops(op, "sa", &(a->head), &(b->head));
		}
		else if (third < second && second < first)
		{
			// append_ops(op, "ra", &(a->head), &(b->head));
			// append_ops(op, "sa", &(a->head), &(b->head));
			// append_ops(op, "pb", &(a->head), &(b->head));
			// append_ops(op, "rra", &(a->head), &(b->head));
			// append_ops(op, "sa", &(a->head), &(b->head));
			// append_ops(op, "pa", &(a->head), &(b->head));

			append_ops(op, "ra", &(a->head), &(b->head));
			append_ops(op, "sa", &(a->head), &(b->head));
			append_ops(op, "rra", &(a->head), &(b->head));
			append_ops(op, "sa", &(a->head), &(b->head));
			append_ops(op, "ra", &(a->head), &(b->head));
			append_ops(op, "sa", &(a->head), &(b->head));
			append_ops(op, "rra", &(a->head), &(b->head));
		}
		else
		{
			// append_ops(op, "pb", &(a->head), &(b->head));
			// append_ops(op, "pb", &(a->head), &(b->head));
			// append_ops(op, "sb", &(a->head), &(b->head));
			// append_ops(op, "pa", &(a->head), &(b->head));
			// append_ops(op, "sa", &(a->head), &(b->head));
			// append_ops(op, "pa", &(a->head), &(b->head));

			append_ops(op, "sa", &(a->head), &(b->head));
			append_ops(op, "ra", &(a->head), &(b->head));
			append_ops(op, "sa", &(a->head), &(b->head));
			append_ops(op, "rra", &(a->head), &(b->head));
		}
	}
}

int smaller_value(t_info *stack, int value)
{
	int hold;
	t_stack *tmp;

	hold = stack->sorted_end;
	tmp = stack->head;
	while (tmp)
	{
		if (tmp->value < value)
		{
			if (tmp->value > hold)
				hold = tmp->value;
		}
		tmp = tmp->next;
	}
	return hold;
}

int bigger_value(t_stack *stack, int value)
{
	int hold;

	while (stack)
	{
		if (stack->value > value)
			return stack->value;
		stack = stack->next;
	}
	return (value);
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

void insert_value_asc(t_stack **head, int value)
{
	t_stack *tmp;
	t_stack *hold;

	tmp = *head;
	if (!tmp)
	{
		*head = create_new_element(value);
		return;
	}
	if (tmp->value > value)
	{
		hold = create_new_element(value);
		if (hold)
		{
			hold->next = *head;
			*head = hold;
		}
		return;
	}
	while (tmp->next && tmp->next->value < value)
		tmp = tmp->next;
	hold = tmp->next;
	tmp->next = create_new_element(value);
	if (tmp->next)
		tmp->next->next = hold;
}

void merge_to_b(t_op **op, t_info *a, t_info *b, int amount)
{
	update_info(b);
	while (amount > 0)
	{
		if ((a->head)->value < b->sorted_end || (a->head)->value > b->sorted_start)
			rotate_to_top(op, b, get_pos(b->head, b->sorted_start));
		else
			rotate_to_top(op, b, get_pos(b->head, smaller_value(b, a->head->value)));
		append_ops(op, b->op[PUSH], &(a->head), &(b->head));
		update_info(b);
		amount--;
	}
	rotate_to_top(op, b, get_pos(b->head, b->sorted_start));
}

void merge_to_a(t_op **op, t_info *a, t_info *b)
{
	t_stack *tmp_hold = NULL;

	update_info(a);
	update_info(b);
	tmp_hold = copy_stack(a->head, a->sorted_amount);
	while (b->sorted_amount > 0)
	{
		if (b->head->value > a->sorted_end)
		{
			rotate_to_bottom(op, a, get_pos(a->head, a->sorted_end));
			a->sorted_end = b->head->value;
		}
		else
		{
			rotate_to_top(op, a, get_pos(a->head, bigger_value(tmp_hold, b->head->value)));
			if (a->sorted_start > b->head->value)
				a->sorted_start = b->head->value;
		}
		insert_value_asc(&tmp_hold, b->head->value);
		append_ops(op, a->op[PUSH], &(a->head), &(b->head));
		a->sorted_amount++;
		b->sorted_amount--;
	}
	rotate_to_top(op, a, get_pos(a->head, a->sorted_start));
	update_info(a);
	delete_stack(&tmp_hold);
}

void merge(t_op **op, t_info *a, t_info *b)
{
	int a_size = get_size(a->head);
	int remainder = 3;
	int rotate;

	solve_top_a(op, a, b, 3);
	update_info(a);
	// print_2_stacks(a->head, b->head);
	while (a->sorted_amount < a_size)
	{
		// printf("%sOUTTER\n%s", RED, WHITE);
		while (b->sorted_amount < a->sorted_amount)
		{
			// printf("%sINNER\n%s", RED, WHITE);
			if (a_size - a->sorted_amount - b->sorted_amount < 3)
				remainder = a_size - a->sorted_amount - b->sorted_amount;
			if (remainder <= 0)
				break;
			rotate = remainder;
			while (rotate-- > 0)
				append_ops(op, a->op[R_ROT], &(a->head), &(b->head));
			if (!(b->head))
			{
				// printf("%s!(b->head)\n%s", RED, WHITE);
				push_to_b(op, a, b, remainder);
				solve_b_max_3(op, &(b->head));
				update_info(b);
				continue;
			}
			else
			{
				// printf("%sb->head\n%s", RED, WHITE);
				// printf("remainder: %d\n", remainder);
				rotate = a_size - a->sorted_amount - b->sorted_amount - remainder;
				solve_top_a(op, a, b, remainder);
				while (rotate-- > 0 && a->head->value > get_last(a->head))
				{
					append_ops(op, a->op[R_ROT], &(a->head), &(b->head));
					remainder++;
				}
				merge_to_b(op, a, b, remainder);
			}
			// print_2_stacks(a->head, b->head);
		}
		// print_2_stacks(a->head, b->head);
		merge_to_a(op, a, b);
	}
}

//DESC:smaller_value , ASC:bigger_value
int get_value(t_stack *stack, int value, int order)
{
	int hold;

	while (stack)
	{
		if (stack->value > value && order == ASC)
			return stack->value;
		if (stack->value < value && order == DESC)
			return stack->value;
		stack = stack->next;
	}
	return (value);
}

void insert_value_helper(t_stack **stack, t_stack *new_value, int order)
{
	t_stack *tmp;
	t_stack *hold;

	hold = NULL;
	tmp = *stack;
	while (tmp)
	{
		if (new_value->value == tmp->value)
		{
			free(new_value);
			return ;
		}
		if ((new_value->value > tmp->value && order == DESC) ||
			(new_value->value < tmp->value && order == ASC))
			break;
		hold = tmp;
		tmp = tmp->next;
	}
	if (hold == NULL)
	{
		new_value->next = tmp;
		*stack = new_value;
	}
	else
	{
		hold->next = new_value;
		new_value->next = tmp;
	}
}

void insert_value(t_stack **stack, int value, int order)
{
	t_stack *tmp;
	t_stack *new_value;

	tmp = *stack;
	new_value = create_new_element(value);
	if (!new_value)
		exit(1);
	if (!(*stack))
		*stack = new_value;
	else
		insert_value_helper(stack, new_value, order);
}

void update_info_test(t_info *stack)
{
	stack->sorted_amount = get_size(stack->sorted);
	if (!stack->sorted_amount)
	{
		stack->min = 0;
		stack->max = 0;
		return ;
	}
	stack->min = get_min(stack->sorted);
	stack->max = get_max(stack->sorted);
}

void merge_to_b_test(t_op **op, t_info *a, t_info *b, int amount)
{
	if (b->sorted_amount == 0)
	{
		push_to_b(op, a, b, amount);
		solve_three(op, b, amount);
		b->sorted = copy_stack(b->head, amount);
	}
	while (amount > 0 && b->sorted_amount != 0)
	{
		update_info_test(b);
		if ((a->head)->value < b->min || (a->head)->value > b->max)
			rotate_to_top(op, b, get_pos(b->head, b->max));
		else
			rotate_to_top(op, b, get_pos(b->head, get_value(b->sorted, a->head->value, DESC)));
		insert_value(&(b->sorted), a->head->value, DESC);
		append_ops(op, b->op[PUSH], &(a->head), &(b->head));
		amount--;
	}
	update_info_test(b);
}

void merge_to_a_test(t_op **op, t_info *a, t_info *b)
{
	update_info_test(a);
	rotate_to_top(op, b, get_pos(b->head, b->max));
	while (b->head)
	{
		if (b->head->value > a->max)
			rotate_to_bottom(op, a, get_pos(a->head, a->max));
		else
			rotate_to_top(op, a, get_pos(a->head, get_value(a->sorted, b->head->value, ASC)));
		insert_value(&(a->sorted), b->head->value, ASC);
		append_ops(op, a->op[PUSH], &(a->head), &(b->head));
		update_info_test(a);
	}
	rotate_to_top(op, a, get_pos(a->head, a->min));
	delete_stack(&(b->sorted));
	update_info_test(b);
}

void a_sorted_longest(t_info *a)
{
	t_stack *tmp;
	int hold;

	tmp = a->head;
	hold = tmp->value;
	while (tmp)
	{
		if (hold > tmp->value)
			return ;
		insert_value(&(a->sorted), tmp->value, ASC);
		hold = tmp->value;
		tmp = tmp->next;
	}
	update_info_test(a);
}

void merge_test(t_op **op, t_info *a, t_info *b)
{
	int a_size = get_size(a->head);
	int remainder = 3;
	int rotate;

	solve_three(op, a, 3);
	// a_sorted_longest(a);
	a->sorted = copy_stack(a->head, 3);
	a->sorted_amount = 3;
	while (a->sorted_amount < a_size)
	{
		while (b->sorted_amount < a->sorted_amount)
		{
			if (a_size - a->sorted_amount - b->sorted_amount < 3)
				remainder = a_size - a->sorted_amount - b->sorted_amount;
			if (remainder <= 0)
				break;
			rotate = remainder;
			while (rotate-- > 0)
				append_ops(op, a->op[R_ROT], &(a->head), &(b->head));
			if (!(b->head))
			{
				merge_to_b_test(op, a, b, remainder);
				continue;
			}
			solve_three(op, a, remainder);
			merge_to_b_test(op, a, b, remainder);
		}
		merge_to_a_test(op, a, b);
		// a_sorted_longest(a);
	}
	delete_stack(&(a->sorted));
}

void initialize_info(t_info *stack, char name)
{
	stack->name = name;
	stack->head = NULL;
	stack->sorted = NULL;
	stack->sorted_start = 0;
	stack->sorted_end = 0;
	stack->sorted_amount = 0;

	stack->min = 0;
	stack->max = 0;
	
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

int main(int argc, char *argv[])
{
	t_info a;
	t_info b;
	t_stack *stack;

	t_op *op = NULL;
	int pos = 1;

	initialize_info(&a, 'a');
	initialize_info(&b, 'b');

	int amount = create_stack(argc, argv, &(a.head));
	if (!amount)
		write(2, "Error\n", 6);
	else
	{
		// print_intial_a(a.head);
		

		// print_2_stacks(a.head, b.head);
		merge_test(&op, &a, &b);
		
		// print_2_stacks(a.head, b.head);
		
		// a_sorted_longest(&a);
		// print_stack(a.sorted, 's');


		global_count--;
		if (is_stack_sorted(&(a.head)))
			printf("%sSORTED%s %d\n%s", GREEN, YELLOW, global_count, WHITE);
		else
			printf("%sNOT SORTED%s %d%s\n", RED, YELLOW, global_count, WHITE);
	}
	exit(1);
	return (1);
}

/* later use */

int is_sorted(t_stack *stack, int order)
{
	int value;

	if (!stack)
		return (1);
	value = stack->value;
	while (stack)
	{
		if (value < stack->value && order == DESC)
			return (0);
		else if (value > stack->value && order == ASC)
			return (0);
		value = stack->value;
		stack = stack->next;
	}
	return (1);
}

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
	// if (!ft_strcmp(op, "pb") || !ft_strcmp(op, "pa"))
	// 	printf("%s%d: %s%s%s\n", BLUE, global_count, RED, op, WHITE);
	// else
	// 	printf("%s%d: %s%s%s\n", BLUE, global_count, YELLOW, op, WHITE);
	// printf("%s%s%s\n", YELLOW, op, WHITE);
	global_count++;
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

/* solve_three -- almost normed */

void solve_stack_of_three(t_op **op, t_info *stack)
{
	int size;
	int first;
	int second;
	int third;

	size = get_size(stack->head);
	while (size == 3)
	{
		first = stack->head->value;
		second = stack->head->next->value;
		third = stack->head->next->next->value;
		if ((second > first && second > third && stack->name == 'a') ||
			(second < first && second < third && stack->name == 'b'))
			append_ops(op, stack->op[R_ROT], &(stack->head), &(stack->head));
		else if ((first > third && first > second && stack->name == 'a') ||
				 (first < third && first < second && stack->name == 'b'))
			append_ops(op, stack->op[ROT], &(stack->head), &(stack->head));
		else if ((second < first && stack->name == 'a') ||
				 (second > first && stack->name == 'b'))
			append_ops(op, stack->op[SWAP], &(stack->head), &(stack->head));
		else
			return;
	}
}

void solve_top_three_helper(t_op **op, t_info *stack)
{
	int first;
	int second;
	int third;

	first = stack->head->value;
	second = stack->head->next->value;
	third = stack->head->next->next->value;
	append_ops(op, stack->op[ROT], &(stack->head), &(stack->head));
	append_ops(op, stack->op[SWAP], &(stack->head), &(stack->head));
	append_ops(op, stack->op[R_ROT], &(stack->head), &(stack->head));
	if (first < second && second > third && first > third)
		append_ops(op, stack->op[SWAP], &(stack->head), &(stack->head));
	else if (third < second && second < first)
	{
		append_ops(op, stack->op[SWAP], &(stack->head), &(stack->head));
		append_ops(op, stack->op[ROT], &(stack->head), &(stack->head));
		append_ops(op, stack->op[SWAP], &(stack->head), &(stack->head));
		append_ops(op, stack->op[R_ROT], &(stack->head), &(stack->head));
	}
}

void solve_top_three(t_op **op, t_info *stack)
{
	int first;
	int second;
	int third;

	first = stack->head->value;
	second = stack->head->next->value;
	third = stack->head->next->next->value;
	if (first < second && second < third)
		return;
	else if (first > second && second < third && third > first)
		append_ops(op, stack->op[SWAP], &(stack->head), &(stack->head));
	else if (first > second && first > third && second < third)
	{
		append_ops(op, stack->op[SWAP], &(stack->head), &(stack->head));
		append_ops(op, stack->op[ROT], &(stack->head), &(stack->head));
		append_ops(op, stack->op[SWAP], &(stack->head), &(stack->head));
		append_ops(op, stack->op[R_ROT], &(stack->head), &(stack->head));
	}
	else
		solve_top_three_helper(op, stack);
}

void solve_three(t_op **op, t_info *stack, int amount)
{
	int size;

	size = get_size(stack->head);
	if (amount == 1 || size == 1)
		return;
	if (amount <= 2 && size >= 2)
	{
		if ((stack->head->value > stack->head->next->value && stack->name == 'a') ||
			(stack->head->value < stack->head->next->value && stack->name == 'b'))
			append_ops(op, stack->op[SWAP], &(stack->head), &(stack->head));
		return;
	}
	if (size == 3)
		solve_stack_of_three(op, stack);
	else
		solve_top_three(op, stack);
}
