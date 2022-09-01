/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:10:33 by thule             #+#    #+#             */
/*   Updated: 2022/09/01 18:40:14 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

/*
Check for duplicates, if yes, return 0
If no duplicates at all, insert new element at the end of the list then return 1
*/
static int	check_then_insert(t_stack **head, int value)
{
	t_stack	*tmp;

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
			break ;
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

/*
Return 1 if there is only spaces or/and numbers, 
or minus/plus right in front of digits.
Otherwise, return 0
*/
static int	raw_form_check(char *array[])
{
	int	x;
	int	y;

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
			if ((array[x][y] == '-' || array[x][y] == '+') &&
				!ft_isdigit(array[x][y + 1]))
				return (0);
			y++;
		}
		x++;
	}
	return (1);
}

/*
if the number is negative, return number length + 1
else if the number is positive, return number length
*/
static int	number_len(long n)
{
	int	len;
	int	sign;

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
		n = n / 10;
		len++;
	}
	return (len + sign);
}

/*
Each argv will be checked and saved as number and saved into the list
If there is error, return (-1)
else, return (amount)
*/
static int	create_stack_helper(int index, char *array[], t_stack **head)
{
	long	number;
	int		count;

	count = 0;
	while (*(array[index]))
	{
		if (*(array[index]) == '+')
			(array[index])++;
		number = ft_atol(array[index]);
		if (number >= INT_MIN && number <= INT_MAX)
		{
			if (!check_then_insert(head, number))
				return (-1);
			count++;
		}
		else
			return (-1);
		array[index] = array[index] + number_len(number);
		while (ft_isspace(*(array[index])))
			(array[index])++;
	}
	return (count);
}

/*
Return -1 if there's an error (duplicate numbers or other chars)
else, return amount
*/
int	create_stack(int amount, char *array[], t_stack **head)
{
	size_t	index;
	long	number;
	int		count;
	int		res;

	count = 0;
	index = 1;
	res = 0;
	if (!raw_form_check(array))
		return (-1);
	while (index < amount)
	{
		res = create_stack_helper(index, array, head);
		if (res == -1)
			return (-1);
		count += res;
		index++;
	}
	return (count);
}
