/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 16:16:36 by thule             #+#    #+#             */
/*   Updated: 2022/09/21 14:01:57 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	create_line(char **holder, char **line)
{
	char	*tmp;
	int		index;

	index = 0;
	while ((*holder)[index] && (*holder)[index] != '\n')
		index++;
	*line = ft_strsub(*holder, 0, index);
	if ((*holder)[index] == '\n' && (*holder)[index + 1] != '\0')
	{	
		tmp = ft_strsub(*holder, index + 1, ft_strlen(*holder) - index);
		ft_strdel(holder);
		*holder = tmp;
	}
	else
		ft_strdel(holder);
	if (!(*line) || !tmp)
		return (-1);
	return (1);
}

static char	*connect_holder_and_buf(char *holder, char *buf)
{
	char	*temp;

	temp = NULL;
	if (!holder)
		holder = ft_strdup(buf);
	else
	{
		temp = ft_strjoin(holder, buf);
		ft_strdel(&holder);
		holder = temp;
	}
	return (holder);
}

static	int	result(char **holder, char **line, int ret, int fd)
{
	if (!line || ret < 0 || fd < 0)
		return (-1);
	else if (*holder == NULL && ret == 0)
		return (0);
	else
		return (create_line(holder, line));
}

int	get_next_line(const int fd, char **line)
{
	static char	*holder[FD_SIZE];
	char		buf[BUFF_SIZE + 1];
	int			ret;

	ret = 1;
	while (ret > 0 && line)
	{
		ret = read(fd, buf, BUFF_SIZE);
		if (ret > 0)
		{
			buf[ret] = '\0';
			holder[fd] = connect_holder_and_buf(holder[fd], buf);
			if (!holder[fd])
				return (-1);
		}
		if (ret <= 0 || ft_strchr(buf, '\n'))
			break ;
	}
	return (result(&holder[fd], line, ret, fd));
}
