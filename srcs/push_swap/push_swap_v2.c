/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_v2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 13:28:16 by thle              #+#    #+#             */
/*   Updated: 2022/08/19 03:02:26 by thule            ###   ########.fr       */
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

	int splitted;

	int min;
	int max;

	char *op[5];
} t_info;

t_stack *stack_b(t_op **op, t_info *a, t_info *b, int stack_size);
t_stack *stack_a(t_op **op, t_info *a, t_info *b, int stack_size);

int is_sorted(t_stack *stack, int order);
int get_size(t_stack *stack);
long get_first(t_stack *stack);
long get_last(t_stack *stack);
long get_min(t_stack *stack);
long get_max(t_stack *stack);

void solve_three(t_op **op, t_info *stack, int amount);
void solve_five(t_op **op, t_info *a, t_info *b);
void print_intial_a(t_stack *a);
void append_ops(t_op **head, char *op, t_stack **a, t_stack **b);
void print_op(t_op *op);

t_info g_a;
t_info g_b;

t_stack *sorted_merge(t_stack *a, t_stack *b)
{
	t_stack *result;

	result = NULL;
	if (a == NULL)
		return b;
	else if (b == NULL)
		return a;
	if (a->value <= b->value)
	{
		result = a;
		result->next = sorted_merge(a->next, b);
	}
	else
	{
		result = b;
		result->next = sorted_merge(a, b->next);
	}
	return result;
}

void divide_into_half(t_stack *head, t_stack **first_half, t_stack **second_half)
{
	t_stack *fast;
	t_stack *slow;

	if (!head)
		return;
	fast = head->next;
	slow = head;
	if (fast)
		fast = fast->next;
	while (fast)
	{
		if (fast->next)
			fast = fast->next->next;
		else
			fast = fast->next;
		slow = slow->next;
	}
	*first_half = head;
	*second_half = slow->next;
	slow->next = NULL;
}

void merge_sort(t_stack **head)
{
	t_stack *first_half;
	t_stack *second_half;
	t_stack *tmp_head;

	first_half = NULL;
	second_half = NULL;
	tmp_head = *head;
	if (!tmp_head || !(tmp_head->next))
		return;
	divide_into_half(*head, &first_half, &second_half);
	merge_sort(&first_half);
	merge_sort(&second_half);
	*head = sorted_merge(first_half, second_half);
}

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

// DESC:smaller_value , ASC:bigger_value
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
			return;
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

void update_info(t_info *stack)
{
	stack->sorted_amount = get_size(stack->sorted);
	if (!stack->sorted_amount)
	{
		stack->min = 0;
		stack->max = 0;
		return;
	}
	stack->min = get_min(stack->sorted);
	stack->max = get_max(stack->sorted);
}

void merge_to_b(t_op **op, t_info *a, t_info *b, int amount)
{
	if (b->sorted_amount == 0)
	{
		push_to_b(op, a, b, amount);
		solve_three(op, b, amount);
		b->sorted = copy_stack(b->head, amount);
	}
	while (amount > 0 && b->sorted_amount != 0)
	{
		update_info(b);
		if ((a->head)->value < b->min || (a->head)->value > b->max)
			rotate_to_top(op, b, get_pos(b->head, b->max));
		else
			rotate_to_top(op, b, get_pos(b->head, get_value(b->sorted, a->head->value, DESC)));
		insert_value(&(b->sorted), a->head->value, DESC);
		append_ops(op, b->op[PUSH], &(a->head), &(b->head));
		amount--;
	}
	update_info(b);
}

void merge_to_a(t_op **op, t_info *a, t_info *b)
{
	update_info(a);
	rotate_to_top(op, b, get_pos(b->head, b->max));
	while (b->head)
	{
		if (b->head->value > a->max)
			rotate_to_bottom(op, a, get_pos(a->head, a->max));
		else
			rotate_to_top(op, a, get_pos(a->head, get_value(a->sorted, b->head->value, ASC)));
		insert_value(&(a->sorted), b->head->value, ASC);
		append_ops(op, a->op[PUSH], &(a->head), &(b->head));
		update_info(a);
	}
	rotate_to_top(op, a, get_pos(a->head, a->min));
	delete_stack(&(b->sorted));
	update_info(b);
}

void merge(t_op **op, t_info *a, t_info *b)
{
	int a_size = get_size(a->head);
	int remainder = 3;
	int rotate;

	solve_three(op, a, 3);
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
				merge_to_b(op, a, b, remainder);
				continue;
			}
			// solve_three(op, a, remainder);
			merge_to_b(op, a, b, remainder);
		}
		merge_to_a(op, a, b);
	}
	delete_stack(&(a->sorted));
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

int sequence_count(t_stack *stack)
{
	int hold;

	hold = 1;
	while (stack->next)
	{
		if (stack->value > stack->next->value)
			return (hold);
		hold++;
		stack = stack->next;
	}
	return hold;
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
		append_ops(op, container->op[PUSH], &(a->head), &(b->head));
	// print_2_stacks(g_a.head, g_b.head);
	a->splitted = 0;
	b->splitted = 0;
	return (stack_size / 2);
}

t_stack *combine(t_stack **head, t_stack *tail)
{
	if (!(*head) && tail)
	{
		*head = tail;
		merge_sort(head);
		return *head;
	}
	t_stack *tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = tail;
	merge_sort(head);
	return *head;
}

t_stack *retrieve_node(t_stack **stack, int value)
{
	t_stack *prev;
	t_stack *tmp;

	tmp = *stack;
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

void merge_tmp_stack_order(t_stack **stack, t_stack *new)
{
	t_stack *tmp;
	t_stack *hold;

	tmp = *stack;
	hold = NULL;
	if (!tmp)
	{
		*stack = new;
		return;
	}
	while (tmp)
	{
		if (new->value < tmp->value)
			break;
		hold = tmp;
		tmp = tmp->next;
	}
	if (hold == NULL)
	{
		new->next = tmp;
		*stack = new;
	}
	else
	{
		hold->next = new;
		new->next = tmp;
	}
}

int get_value_desc(t_stack *stack, int value, int order)
{
	while (stack->next)
	{
		if (value > stack->value && value < stack->next->value)
			return stack->value;
		stack = stack->next;
	}
	return (1);
}

void merge_stack_b(t_op **op, t_info *a, t_info *b, t_stack **on_a, t_stack **on_b)
{
	// printf("___________MERGE_B________\n");
	// print_2_stacks(*on_a, *on_b);
	int a_size = get_size(*on_a);
	int value;
	int min;
	int max;

	while (a_size-- > 0)
	{
		value = a->head->value;
		min = get_min(*on_b);
		max = get_max(*on_b);
		if (value > max)
			rotate_to_top(op, b, get_pos(b->head, max));
		else if (value < min)
			rotate_to_bottom(op, b, get_pos(b->head, min));
		else
			rotate_to_top(op, b, get_pos(b->head, get_value_desc(*on_b, value, DESC)));
		append_ops(op, b->op[PUSH], &(a->head), &(b->head));
		// print_2_stacks(a->head, b->head);
		merge_tmp_stack_order(on_b, retrieve_node(on_a, value));
	}
	// rotate_to_top(op, b, get_pos(b->head, get_max(*on_b)));
	// print_2_stacks(a->head, b->head);
}

void merge_stack_a(t_op **op, t_info *a, t_info *b, t_stack **on_a, t_stack **on_b)
{
	// printf("___________MERGE_A________\n");
	int b_size = get_size(*on_b);
	int value;
	int min;
	int max;

	rotate_to_top(op, b, get_pos(b->head, get_max(*on_b)));

	while (b_size-- > 0)
	{
		value = b->head->value;
		min = get_min(*on_a);
		max = get_max(*on_a);
		if (value > max)
			rotate_to_bottom(op, a, get_pos(a->head, max));
		else
		{
			int random = get_value(*on_a, value, ASC);
			int pos = get_pos(a->head, random);
			// print_stack(*on_a, 'o');
			// printf("pos: %d; random:%d; value:%d\n", pos, random, value);
			rotate_to_top(op, a, pos);
			
		}
		append_ops(op, a->op[PUSH], &(a->head), &(b->head));
		// print_2_stacks(a->head, b->head);
		merge_tmp_stack_order(on_a, retrieve_node(on_b, value));
	}
	rotate_to_top(op, a, get_pos(a->head, get_min(*on_a)));
	// print_2_stacks(a->head, b->head);
}

t_stack *stack_b(t_op **op, t_info *a, t_info *b, int stack_size)
{
	// printf("-----------------B-----------------\n");
	t_stack *on_a = NULL;
	t_stack *on_b = NULL;
	t_stack *sorted = NULL;
	int container_size;
	
	if (stack_size <= 3)
	{
		// printf("b: %d\n", stack_size);
		solve_three(op, b, stack_size);
		on_b = copy_stack(b->head, stack_size);
		// merge_sort(&on_b);
		return on_b;
	}
	b->splitted = 1;
	container_size = split_stack(op, a, b, stack_size);
	stack_size = stack_size - container_size;
	// printf("b: stack:%d, container:%d\n", stack_size, container_size);
	
	on_b = stack_b(op, a, b, stack_size);
	merge_sort(&on_b);
	on_a = stack_a(op, a, b, container_size);
	merge_sort(&on_a);

	merge_stack_b(op, a, b, &on_a, &on_b);
	
	// printf("%s stack_b\n", CYAN);
	// print_stack(on_a, 'a');
	// print_stack(on_b, 'b');
	// printf("%s", WHITE);
	// printf("-----------------end:B-----------------\n");
	
	return on_b;
}

t_stack *stack_a(t_op **op, t_info *a, t_info *b, int stack_size)
{
	// printf("-----------------A-----------------\n");
	t_stack *on_a = NULL;
	t_stack *on_b = NULL;
	t_stack *sorted = NULL;
	int container_size;
	
	if (stack_size <= 3)
	{
		// printf("a: %d\n", stack_size);

		solve_three(op, a, stack_size);
		on_a = copy_stack(a->head, stack_size);
		// merge_sort(&on_a);
		return on_a;
	}
	a->splitted = 1;
	container_size = split_stack(op, a, b, stack_size);
	stack_size = stack_size - container_size;
	
	// printf("a: stack:%d, container:%d\n", stack_size, container_size);
	
	
	on_b = stack_b(op, a, b, container_size);
	merge_sort(&on_b);
	on_a = stack_a(op, a, b, stack_size);
	merge_sort(&on_a);
	merge_stack_a(op, a, b, &on_a, &on_b);
	
	
	// printf("%sstack_a\n", CYAN);
	// print_stack(on_a, 'a');
	// print_stack(on_b, 'b');
	// printf("%s", WHITE);
	// printf("-----------------end:A-----------------\n");
	
	return on_a;
}

void merge_test(t_op **op, t_info *a, t_info *b, int stack_size)
{
	t_stack *sorted = stack_a(op, a, b, stack_size);
	// rotate_to_top(op, a, get_pos(a->head, get_min(a->head)));
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
		// print_intial_a(g_a.head);

		// print_2_stacks(g_a.head, g_b.head);

		// merge(&op, &g_a, &g_b);
		
		merge_test(&op, &g_a, &g_b, get_size(g_a.head));

		// appen
		
		// printf("sequence: %d\n", sequence_count(g_a.head));
		// print_2_stacks(g_a.head, g_b.head);

		global_count--;
		if (is_stack_sorted(&(g_a.head)) && !(g_b.head))
			printf("%sSORTED%s %d\n%s", GREEN, YELLOW, global_count, WHITE);
		else
			printf("%sNOT SORTED%s %d%s\n", RED, YELLOW, global_count, WHITE);

		// t_stack *tmp_node = retrieve_node(&(g_a.head), 1);
		// print_2_stacks(g_a.head, tmp_node);
		// merge_tmp_stack_order(&(g_a.head), tmp_node);
		// print_2_stacks(g_a.head, tmp_node);
		
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

void append_ops(t_op **head, char *op, t_stack **a, t_stack **b)
{
	if (!ft_strcmp(op, "pb") || !ft_strcmp(op, "pa"))
		printf("%s%d: %s%s%s\n", MAGENTA, global_count, RED, op, WHITE);
	else
		printf("%s%d: %s%s%s\n", MAGENTA, global_count, YELLOW, op, WHITE);

	// printf("%s%s%s\n", YELLOW, op, WHITE);
	// printf("%s\n", op);

	// global_count++;
	t_op *tmp;
	t_op *new;
	void (*op_array[9])(t_stack **);

	assign_index_for_op(op_array);
	if (!apply_op(op_array, op, a, b))
		exit(1);

	// printf("%s---------------%s", CYAN, WHITE);
	// if (!ft_strcmp(op, "pb") || !ft_strcmp(op, "pa"))
	// 	printf(" %s%5d: %s%3s%s ", MAGENTA, global_count, RED, op, WHITE);
	// else
	// 	printf(" %s%5d: %s%3s%s ", MAGENTA, global_count, YELLOW, op, WHITE);
	// printf("%s---------------%s\n", CYAN, WHITE);
	// print_2_stacks(g_a.head, g_b.head);
	// printf("\n");

	global_count++;
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
	if ((first < second && second > third && first > third && stack->name == 'a')
		|| (first > second && second < third && first < third && stack->name == 'b'))
		append_ops(op, stack->op[SWAP], &(stack->head), &(stack->head));
	else if ((third < second && second < first && stack->name == 'a') 
			|| (third > second && second > first && stack->name == 'b'))
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
	if ((first < second && second < third && stack->name == 'a')
		|| (first > second && second > third && stack->name == 'b'))
		return;
	else if ((first > second && second < third && third > first && stack->name == 'a')
			|| (first < second && second > third && third < first && stack->name == 'b'))
		append_ops(op, stack->op[SWAP], &(stack->head), &(stack->head));
	else if ((first > second && first > third && second < third && stack->name == 'a')
			|| (first < second && first < third && second > third && stack->name == 'b'))
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

void solve_five(t_op **op, t_info *a, t_info *b)
{
	rotate_to_top(op, a, get_pos(a->head, get_min(a->head)));
	append_ops(op, b->op[PUSH], &(a->head), &(b->head));
	rotate_to_top(op, a, get_pos(a->head, get_min(a->head)));
	append_ops(op, b->op[PUSH], &(a->head), &(b->head));
	solve_three(op, a, 3);
	solve_three(op, a, 2);
	append_ops(op, a->op[PUSH], &(a->head), &(b->head));
	append_ops(op, a->op[PUSH], &(a->head), &(b->head));
	b->sorted_amount = 5;
}