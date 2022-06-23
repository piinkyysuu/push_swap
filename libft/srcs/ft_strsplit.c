/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 02:33:56 by thule             #+#    #+#             */
/*   Updated: 2021/12/15 23:17:03 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(char const *s, char c)
{
	size_t	index;
	size_t	count;

	index = 0;
	count = 0;
	if (s && *s)
	{
		while (s[index + 1] != '\0')
		{
			if (s[index] == c && s[index + 1] != c)
				count++;
			index++;
		}
		if (!count || s[0] != c)
			count++;
		return (count);
	}
	return (0);
}

static int	next_char(char const *s, size_t index, char c)
{
	while (s[index] != c && s[index] != '\0')
	{
		index++;
	}
	index--;
	return (index);
}

static char	**ft_clear(char ***ptr, size_t new_index)
{
	while (new_index)
	{
		ft_memdel((void **)ptr[new_index]);
		new_index--;
	}
	return (NULL);
}

static char	**append_str(char **new, char const *s, char c, size_t *new_index)
{
	size_t	index;
	size_t	start;
	size_t	end;

	start = 0;
	while (s[start] != '\0')
	{
		if (s[start] != c)
		{
			end = next_char(s, start, c);
			new[*new_index] = ft_strnew(end - start + 1);
			if (new[*new_index])
			{
				index = 0;
				while (start <= end)
					new[*new_index][index++] = s[start++];
				new[(*new_index)++][index] = '\0';
			}
			else
				return (ft_clear(&new, *new_index));
		}
		else
			start++;
	}
	return (new);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**new;
	size_t	new_index;

	new = NULL;
	new_index = 0;
	if (s)
	{
		new = (char **)malloc((sizeof(char *) * (count(s, c) + 1)));
		if (new)
		{
			new = append_str(new, s, c, &new_index);
			if (new)
			{
				new[new_index] = NULL;
			}
		}
	}
	return (new);
}
