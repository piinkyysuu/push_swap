/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:40:01 by thule             #+#    #+#             */
/*   Updated: 2022/07/26 19:25:36 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

typedef struct s_content
{
	t_stack *head;
	t_stack *less_than_mid;
	int min;
	int max;
	int sum;
	int mid;
	int amount;
} t_content;

typedef struct s_op
{
	char *op;
	struct s_op *next;
} t_op;

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

void get_stats(t_content *stack)
{
	t_stack *tmp;

	stack->sum = 0;
	stack->amount = 0;
	tmp = stack->head;
	if (!tmp)
		return;
	stack->min = tmp->value;
	stack->max = tmp->value;
	while (tmp)
	{
		if (tmp->value < stack->min)
			stack->min = tmp->value;
		if (tmp->value > stack->max)
			stack->max = tmp->value;
		stack->sum += tmp->value;
		(stack->amount)++;
		tmp = tmp->next;
	}
	stack->mid = ((stack->sum / stack->amount) + (stack->min + stack->max) / 2) / 2;
}

void print_stats(t_content *stack, char stack_character)
{
	printf("%s%c: %s", CYAN, stack_character, WHITE);
	printf("amt:%d ", stack->amount);
	printf("sum:%d avg:%d | ", stack->sum, stack->sum / stack->amount);
	printf("min:%d ", stack->min);
	printf("max:%d avg:%d | ", stack->max, (stack->min + stack->max) / 2);
	printf("AVG:%d\n", stack->mid);
}

static int solve_stack(t_content a, t_content b)
{
	char *op;
	int result;
	void (*op_array[9])(t_stack **);

	int index = 1;
	op = NULL;
	result = 1;
	assign_index_for_op(op_array);
	while (get_next_line(0, &op))
	{
		if (!apply_op(op_array, op, &(a.head), &(b.head)))
		{
			result = -1;
			ft_strdel(&op);
			break;
		}
		printf("%s--------------------%s%03d%s--------------------%s\n", YELLOW, MAGENTA, index, YELLOW, WHITE);
		index++;
		print_2_stacks(a.head, b.head);
		printf("\n");
		ft_strdel(&op);
	}
	if (!(a.head))
		return 0;
	if ((!is_stack_sorted(&(a.head)) || b.head) && result != -1)
		result = 0;
	delete_stack(&(a.head));
	delete_stack(&(b.head));
	return (result);
}

void print_ops(t_op *head)
{
	while (head)
	{
		printf("%s ", head->op);
		head = head->next;
	}
	printf("\n");
}

void append_ops(t_op **head, char *op, t_stack **a, t_stack **b)
{
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

// t_op *try_solve(t_content *a, t_content *b)
// {
// 	int index = 0;
// 	t_op *op = NULL;

// 	int pos[2] = {-1, -1};
// 	t_stack *c = NULL;

// 	while (a->amount > 3)
// 	{
// 		find_less_than_mid(a->head, a->amount, a->mid, pos);
// 		if (pos[0] == -1 && pos[1] == -1)
// 		{
// 			get_stats(a);
// 			find_less_than_mid(a->head, a->amount, a->mid, pos);
// 		}
// 		if (pos[0] == 1 || pos[0] == 2)
// 		{
// 			if (pos[0] == 2)
// 			{
// 				swap(&(a->head));
// 				append_ops(&op, "sa");
// 			}
// 			push(&c, &(a->head));
// 		}
// 		else if (pos[0] <= a->amount / 2 && pos[0] != -1)
// 		{
// 			while (pos[0] - 1)
// 			{
// 				rotate(&(a->head));
// 				append_ops(&op, "ra");
// 				pos[0]--;
// 			}
// 			push(&c, &(a->head));
// 		}
// 		else if (pos[1] > a->amount / 2 && pos[1] != -1)
// 		{
// 			while (a->amount - pos[1] + 1)
// 			{
// 				reverse_rotate(&(a->head));
// 				append_ops(&op, "rra");
// 				pos[1]--;
// 			}
// 			push(&c, &(a->head));
// 		}
// 		push_sort(op, b, &c);
// 		a->amount--;
// 	}
// 	// push(&c, &(a->head));
// 	// print_stack(c, 'c');
// 	// print_2_stacks(a->head, b->head);

// 	// push_sort(op, b, &c);
// 	// print_stack(c, 'c');

// 	print_2_stacks(a->head, b->head);
// 	return op;
// }

void best_to_top_a(int pos, t_op **op, t_stack **stack, int amount)
{
	if (pos == 1)
		return ;
	else if (pos == 2)
		append_ops(op, "sa", stack, NULL);
	else if (pos < (amount / 2) + 1)
	{
		while (amount > (pos++))
			append_ops(op, "ra", stack, NULL);
	}
	else if (pos >= (amount / 2) + 1)
	{
		while (amount + 1 > (pos++))
			append_ops(op, "rra", stack, NULL);
	}
}

void best_to_top_b(int pos, t_op **op, t_stack **stack, int amount)
{
	if (pos == 1)
		return ;
	else if (pos == 2)
		append_ops(op, "sb", NULL, stack);
	else if (pos < (amount / 2) + 1)
	{
		while (amount > (pos++))
			append_ops(op, "rb", NULL, stack);
	}
	else if (pos >= (amount / 2) + 1)
	{
		while (amount + 1 > (pos++))
			append_ops(op, "rrb", NULL, stack);
	}
}

void solve_stack_of_3(t_op **op, t_content *a)
{
	int first;
	int second;
	int last;

	while (1)
	{
		first = (a->head)->value;
		second = ((a->head)->next)->value;
		last = ((a->head)->next->next)->value;
		if (second > first && second > last)
			append_ops(op, "rra", &(a->head), NULL);
		else if (first > last && first > second)
			append_ops(op, "ra", &(a->head), NULL);
		else if (second < first)
			append_ops(op, "sa", &(a->head), NULL);
		else
			break;
	}
}
int find_pos_of_smallest(t_stack *head)
{
	t_stack *tmp;
	int pos;
	int smallest;
	int smallest_pos;

	tmp = head;
	smallest = tmp->value;
	pos = 1;
	smallest_pos = pos;
	if (!tmp)
		return (0);
	while (tmp)
	{
		if (tmp->value < smallest)
		{
			smallest = tmp->value;
			smallest_pos = pos;
		}
		pos++;
		tmp = tmp->next;
	}
	return (smallest_pos);
}
// right now: max: 11, avg: 9
void solve_stack_of_5(t_op **op, t_content *a, t_content *b)
{
	int smallest_pos;

	get_stats(a);
	while (a->amount > 3)
	{
		smallest_pos = find_pos_of_smallest(a->head);
		best_to_top_a(smallest_pos, op, &(a->head), a->amount);
		append_ops(op, "pb", &(a->head), &(b->head));
		get_stats(a);
	}
	solve_stack_of_3(op, a);
	while (b->head)
		append_ops(op, "pa", &(a->head), &(b->head));
}

void find_less_than_mid(t_stack *head, int amount, int mid, int *pos)
{
	int least_pos = -1;
	int most_pos = -1;
	int index = 1;
	while (head)
	{
		if (head->value < mid)
		{
			least_pos = index;
			break;
		}
		index++;
		head = head->next;
	}
	while (head)
	{
		if (head->value < mid)
			most_pos = index;
		index++;
		head = head->next;
	}
	pos[0] = least_pos;
	pos[1] = most_pos;
}

void solve_stack_of_med(t_op **op, t_content *a, t_content *b)
{
	t_stack *hold = NULL;
	int pos[2] = {-1, -1};
	int chosen = 0;
	int median;
	

	
	while (a->amount > 5)
	{
		if (pos[0] == -1 && pos[1] == -1)
		{
			get_stats(a);
			median = a->mid;
			find_less_than_mid(a->head, a->amount, median, pos);
		}
		printf("%d %d %d\n", median, pos[0], pos[1]);
		chosen = pos[1];
		if (pos[0] < a->amount / 2)
			chosen = pos[0];
		printf("chosen:%d\n", chosen);
		best_to_top_a(chosen, op, &(a->head), a->amount);
		push(&hold, &(a->head));
		print_2_stacks(a->head, hold);
		(a->amount)--;
		find_less_than_mid(a->head, a->amount, median, pos);
	}
}

int main(int argc, char *argv[])
{
	int result = 0;
	t_content a;
	t_content b;
	t_op *op = NULL;
	void (*op_array[9])(t_stack **);

	a = (t_content){NULL, NULL, 0, 0, 0, 0, 0};
	b = (t_content){NULL, NULL, 0, 0, 0, 0, 0};
	assign_index_for_op(op_array);
	if (!create_stack(argc, argv, &(a.head)))
		write(2, "Error\n", 6);
	else
	{
		t_stack *temp;
		temp = a.head;
		while (temp)
		{
			printf("%d ", temp->value);
			temp = temp->next;
		}
		printf("\n");
		get_stats(&a);
		print_stats(&a, 'a');
		printf("%s--------------------%s%03d%s--------------------%s\n", YELLOW, MAGENTA, 0, YELLOW, WHITE);
		print_2_stacks(a.head, b.head);
		printf("\n");
		if (!is_stack_sorted(&(a.head)))
		{
			if (a.amount == 5)
				solve_stack_of_5(&op, &a, &b);
			else if (a.amount == 3)
				solve_stack_of_3(&op, &a);
			else
			{
				solve_stack_of_med(&op, &a, &b);
			}
			// printf("%s", GREEN);
			// int count = 0;
			// while (op)
			// {
			// 	printf("%s ", op->op);
			// 	op = op->next;
			// 	count++;
			// }
			// printf("%s%d%s \n", MAGENTA, count, WHITE);
			// print_2_stacks(a.head, b.head);
			// if (is_stack_sorted(&(a.head)) && (b.head == NULL))
			// 	printf("%sSORTED\n", GREEN);
			// else
			// 	printf("%sNOT-SORTED\n", RED);
		}
		// else
		// 	printf("sorted!\n");
		// printf("%s", WHITE);


		
		// result = solve_stack(a, b);
		// if (result == -1)
		// {
		// 	printf("%sMALLOC PROBLEM\n", RED);
		// }
		// else if (result == 0)
		// {
		// 	printf("%sNOT SORTED OR B STILL EXIST\n", RED);
		// }
		// else
		// {
		// 	printf("%sSORTED\n", GREEN);
		// }
	}
	exit(1);
	return (0);
}