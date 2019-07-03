/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmashimb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 10:14:47 by nmashimb          #+#    #+#             */
/*   Updated: 2019/07/03 17:59:35 by nmashimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	int			ft_get_line(int fd, char **stack, char **line, int ret)
{
	char			*tmp;
	int				i;

	i = 0;
	while (stack[fd][i] != '\n' && stack[fd][i] != '\0')
		i++;
	if (stack[fd][i] == '\n')
	{
		*line = ft_strsub(stack[fd], 0, i);
		tmp = ft_strdup(stack[fd] + i + 1);
		free(stack[fd]);
		stack[fd] = tmp;
	}
	else if (stack[fd][i] == '\0')
	{
		if (ret == BUFF_SIZE)
			return (get_next_line(fd, line));
		*line = ft_strdup(stack[fd]);
		ft_strdel(&stack[fd]);
	}
	return (1);
}

int					get_next_line(const int fd, char **line)
{
	static char		*stack[MAX_FD];
	char			buff[BUFF_SIZE];
	char			*tmp;
	int				ret;

	if (fd < 0 || fd > MAX_FD || line == NULL || (read(fd, stack[fd], 0) < 0))
		return (-1);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (stack[fd] == NULL)
			stack[fd] = ft_strnew(1);
		tmp = ft_strjoin(stack[fd], buff);
		ft_strdel(&stack[fd]);
		stack[fd] = tmp;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (ret < 0)
		return (-1);
	else if (ret == 0 && (stack[fd] == NULL || stack[fd][0] == '\0'))
		return (0);
	return (ft_get_line(fd, stack, line, ret));
}
