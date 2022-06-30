/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 14:39:09 by thule             #+#    #+#             */
/*   Updated: 2022/06/30 14:27:39 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "checker.h"

void print_stack(t_stack *head)
{
	t_stack *tmp = head;
	while (tmp)
	{
		printf("%d\n", tmp->value);
		tmp = tmp->next;
	}
}

void delete_stack(t_stack **head)
{
	t_stack *next;
	t_stack *current;

	current = *head;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;
}

t_stack *create_new_element(int value)
{
	t_stack *new;

	new = (t_stack *)malloc(sizeof(t_stack));
	if (new)
	{
		new->value = value;
		new->next = NULL;
	}
	return (new);
}

// check for duplicates, if yes, return 0
// if no duplicates at all, insert the new elements
// at the end of the list
int check_then_insert(t_stack **head, int value)
{
	t_stack *tmp;

	tmp = *head;
	while (tmp)
	{
		if (tmp->value == value)
			return (0);
		if (tmp->next == NULL)
		{
			tmp->next = create_new_element(value);
			if (tmp->next == NULL)
				return (0);
			break;
		}
		tmp = tmp->next;
	}
	if (!tmp)
	{
		*head = create_new_element(value);
		if (!(*head))
			return (0);
	}
	return (1);
}

// convert string to long
long ft_atol(const char *str)
{
	short int sign;
	unsigned long acc;

	sign = 1;
	acc = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str) && *str)
	{
		acc = acc * 10 + (*str - 48);
		str++;
	}
	return (acc * sign);
}

/*
Return 1 if there is only spaces or/and numbers. Otherwise, return 0
*/
int space_and_digit_check(char *array[])
{
	int x;
	int y;

	x = 1;
	y = 0;
	while (array[x])
	{
		y = 0;
		while (array[x][y])
		{
			if (!ft_isdigit(array[x][y]) && !ft_isspace(array[x][y]) && 
				array[x][y] != '-' && array[x][y] != '+')
				return (0);
			if ((array[x][y] == '-' || array[x][y] == '+') && !ft_isdigit(array[x][y + 1]))
				return (0);
			y++;
		}
		x++;
	}
	return (1);
}

int number_len(long n, int base)
{
	int len;
	int sign;

	len = 0;
	sign = 0;
	if (n < 0)
	{
		n = -n;
		sign = 1;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / base;
		len++;
	}
	return (len + sign);
}

int create_stack(int amount, char *array[], t_stack **head)
{
	size_t index;
	long number;

	index = 1;
	if (!space_and_digit_check(array))
		return (0);
	while (index < amount)
	{
		while (*(array[index]))
		{
			if (*(array[index]) == '+')
				(array[index])++;
			number = ft_atol(array[index]);
			if (number >= INT_MIN && number <= INT_MAX)
			{
				if (!check_then_insert(head, number))
				{
					delete_stack(head);
					return 0;
				}
			}
			else
			{
				delete_stack(head);
				return (0);
			}
			array[index] = array[index] + number_len(number, 10);
			while (ft_isspace(*(array[index])))
				(array[index])++;
		}
		index++;
	}
	return (1);
}

int main(int argc, char *argv[])
{
	t_stack *a;
	a = NULL;
	if (argc < 2)
		return (0);

	if (!create_stack(argc, argv, &a))
	{
		printf("ERROR!\n");
	}
	else
	{
		printf("\n-----------------------------\n");
		print_stack(a);
	}

	return (0);
}