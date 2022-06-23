/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 16:16:36 by thule             #+#    #+#             */
/*   Updated: 2022/01/14 10:58:32 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	append_line(char **holder, char **line)
{
	int		index;
	char	*tmp_holder;

	index = 0;
	while ((*holder)[index] && (*holder)[index] != '\n')
		index++;
	*line = ft_strsub(*holder, 0, index);
	if ((*holder)[index] == '\n' && (*holder)[index + 1] != '\0')
	{	
		tmp_holder = ft_strsub(*holder, index + 1, ft_strlen(*holder) - index);
		ft_strdel(holder);
		*holder = tmp_holder;
	}
	else
		ft_strdel(holder);
	return (1);
}

static	int	result(char **holder, char **line, int ret, int fd)
{
	if (!line || ret < 0 || fd < 0)
		return (-1);
	else if (*holder == NULL && ret == 0)
		return (0);
	else
		return (append_line(holder, line));
}

int	get_next_line(const int fd, char **line)
{
	static char	*holder[FD_SIZE];
	char		buf[BUFF_SIZE + 1];
	char		*temp;
	int			ret;

	ret = 1;
	while (ret > 0 && line)
	{
		ret = read(fd, buf, BUFF_SIZE);
		if (ret > 0)
		{
			buf[ret] = '\0';
			if (!holder[fd])
				holder[fd] = ft_strdup(buf);
			else
			{
				temp = ft_strjoin(holder[fd], buf);
				ft_strdel(&holder[fd]);
				holder[fd] = temp;
			}
		}
		if (ft_strchr(buf, '\n') || ret <= 0)
			break ;
	}
	return (result(&holder[fd], line, ret, fd));
}
