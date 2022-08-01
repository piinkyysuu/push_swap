/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:40:01 by thule             #+#    #+#             */
/*   Updated: 2022/08/01 13:14:14 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int find_fitting_pos(t_stack *stack, int value);

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
		printf("fitting:%d\n", find_fitting_pos(b.head, (a.head)->value));
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
	// printf("%s%s%s\n", GREEN, op, WHITE);
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

void best_to_top_a(int pos, t_op **op, t_stack **stack, int amount)
{
	if (pos == 1)
		return;
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
		return;
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
	int amount = 2;

	get_stats(a);
	while (a->amount > 3)
	{
		smallest_pos = find_pos_of_smallest(a->head);
		best_to_top_a(smallest_pos, op, &(a->head), a->amount);
		append_ops(op, "pb", &(a->head), &(b->head));
		get_stats(a);
	}
	solve_stack_of_3(op, a);
	while (b->head && amount-- > 0)
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

int find_range_position(t_content *content, int value)
{
	t_stack *tmp = content->head;
	int pos = 1;
	int first;
	int second;

	get_stats(content);
	if (content->amount == 0)
		return (1);
	if (value < content->min)
	{
		while (tmp)
		{
			if (tmp->value == content->min)
				return (pos + 1);
			tmp = tmp->next;
			pos++;
		}
	}
	else if (value > content->max)
	{
		while (tmp)
		{
			if (tmp->value == content->max)
				return (pos);
			pos++;
			tmp = tmp->next;
		}
	}
	while (tmp->next)
	{
		first = tmp->value;
		second = (tmp->next)->value;
		if (first != content->min && second != content->max)
		{
			if (first < second && value > first && value < second)
				return (pos);
			if (first > second && value < first && value > second)
				return (pos + 1);
		}
		pos++;
		tmp = tmp->next;
	}
	return (1);
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
		// printf("%d %d %d\n", median, pos[0], pos[1]);
		chosen = pos[1];
		if (pos[0] < a->amount / 2)
			chosen = pos[0];
		best_to_top_a(chosen, op, &(a->head), a->amount);

		// get_stats(b);
		// best_to_top_b(find_fitting_pos(b->head, (a->head)->value), op, &(b->head), b->amount);

		append_ops(op, "pb", &(a->head), &(b->head));

		print_2_stacks(a->head, b->head);
		printf("\n");

		(a->amount)--;
		find_less_than_mid(a->head, a->amount, median, pos);
	}
	solve_stack_of_5(op, a, b);
}

void test(t_op **op, t_content *a, t_content *b)
{
	int pos;

	while (a->head)
	{
		pos = find_range_position(b, (a->head)->value);
		if (pos == 1 || pos == 0 || pos == b->amount + 1)
			append_ops(op, "pb", &(a->head), &(b->head));
		else if (pos < ((b->amount / 2) + 1))
		{
			while (pos - 1)
			{
				append_ops(op, "rb", &(a->head), &(b->head));
				pos--;
			}
			append_ops(op, "pb", &(a->head), &(b->head));
		}
		else if (pos >= ((b->amount / 2) + 1))
		{
			while ((b->amount - pos) + 1)
			{
				append_ops(op, "rrb", &(a->head), &(b->head));
				pos++;
			}
			append_ops(op, "pb", &(a->head), &(b->head));
		}
	}

	get_stats(b);
	t_stack *tmp = b->head;
	pos = 1;
	while (tmp)
	{
		if (tmp->value == b->max)
			break;
		pos++;
		tmp = tmp->next;
	}
	if (pos > b->amount / 2)
	{
		while ((b->amount - pos) + 1)
		{
			append_ops(op, "rrb", &(a->head), &(b->head));
			pos++;
		}
	}
	else
	{
		while (pos - 1)
		{
			append_ops(op, "rb", &(a->head), &(b->head));
			pos--;
		}
	}
}

int main(int argc, char *argv[])
{
	printf("\n\n");
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
		// printf("\n");
		get_stats(&a);
		// print_stats(&a, 'a');
		// printf("%s--------------------%s%03d%s--------------------%s\n", YELLOW, MAGENTA, 0, YELLOW, WHITE);
		// print_2_stacks(a.head, b.head);
		printf("\n");
		if (!is_stack_sorted(&(a.head)))
		{
			if (a.amount == 5)
				solve_stack_of_5(&op, &a, &b);
			else if (a.amount == 3)
				solve_stack_of_3(&op, &a);
			else
			{
				if ((a.head)->value > (a.head->next)->value)
					append_ops(&op, "sa", &(a.head), &(b.head));
				append_ops(&op, "pb", &(a.head), &(b.head));
				append_ops(&op, "pb", &(a.head), &(b.head));
				int f = (b.head)->value;
				int s = (b.head->next)->value;
				if ((a.head)->value > f)
					append_ops(&op, "pb", &(a.head), &(b.head));
				else if ((a.head)->value < s)
				{
					append_ops(&op, "pb", &(a.head), &(b.head));
					append_ops(&op, "rb", &(a.head), &(b.head));
				}
				else
				{
					append_ops(&op, "pb", &(a.head), &(b.head));
					append_ops(&op, "sb", &(a.head), &(b.head));
				}
				// print_2_stacks(a.head, b.head);

				// printf("-------------------calling test-------------------\n");
				test(&op, &a, &b);
				// solve_stack_of_med(&op, &a, &b);
				// printf("%s--------------------%sFINAL%s--------------------%s\n", YELLOW, MAGENTA, YELLOW, WHITE);
				
				// for (int i = 0; i < 20; i++)
				// {
				// 	append_ops(&op, "pb", &(a.head), &(b.head));
				// }
				
				temp = (b.head)->next;
				int val = (b.head)->value;
				while (temp)
				{
					if (val < temp->value)
					{
						printf("%sERROR%s\n", RED, WHITE);
						print_2_stacks(a.head, b.head);
						exit(1);
					}
					val = temp->value;
					temp = temp->next;
				}
				printf("%sSORTED%s\n", GREEN, WHITE);
				print_2_stacks(a.head, b.head);
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