/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmashimb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 13:42:49 by nmashimb          #+#    #+#             */
/*   Updated: 2019/06/28 13:15:51 by nmashimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h> //open

//checks if file has nl (valid). if so, retrives line and stack points to !st chr of next ln
//works!!
int		check_nl(char **stack, char **line)
{
	size_t	i;
	char	*endof_ln;
	char	*nl_pntr;

	i = 0;
	nl_pntr = *stack;
	nl_pntr[(strlen(nl_pntr) - 1)] = '\0'; //added
	while (nl_pntr[i] != '\n')
	{
		if (nl_pntr[i] == '\0')
			return (0);
		i++;
	}
	endof_ln = &nl_pntr[i];
	*endof_ln = '\0';
	*line = strdup(*stack); //change me
	*stack = strdup(endof_ln + 1); //change me
	return (1);
}

int		update_stack(int fd, char **stack, char **line, char *buff)
{
	char	*tmp;
	int		ret;

	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (*stack)
		{
			tmp = *stack;
			*stack = ft_strjoin(tmp, buff); //change me
			free(tmp);
			tmp = NULL;
		}
		else
			*stack = strdup(buff); //change me
		if ((check_nl(stack, line)) == 1)
			break;
	}
	if (ret > 0)
		return (1);
	return (ret);
}

int		get_next_line(const int fd, char **line)
{
	static char	*stack[MAX_FD];
	char		*buff;
	int 		ret;

	if (( fd < 0 || fd > MAX_FD) || (!(buff = (char *)malloc(BUFF_SIZE + 1)))\
			|| line == NULL || read(fd, stack[fd], 0) < 0) //why stack[fd]
		return (-1);
	if (*stack)
	{
		if ((check_nl(stack, line)) == 1)
			return (1);
	}
	//bzero(buff, BUFF_SIZE); //optional?
	ret = update_stack(fd, &stack[fd], line, buff); //updates stack: add content with \n
	free(buff);
	buff = NULL;
	//case where theres nothing in file ?
	if (ret != 0 || stack[fd][0] == '\0'  || stack[fd] == NULL)
	{
		/*if (ret == 0 && *line) //and line exist?
			*line = NULL;*/
		return (ret);
	}
	*line = stack[fd]; //allocating last line
	stack[fd] = NULL;
	return (1);
}

int		main()
{
	int fd = open("text.txt", O_RDONLY);
	char			*line = NULL;

	int x = get_next_line(fd, &line);

	//printf("%d\n", x);
	return 0;
}
