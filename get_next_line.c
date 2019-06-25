/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmashimb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 13:42:49 by nmashimb          #+#    #+#             */
/*   Updated: 2019/06/25 17:25:43 by nmashimb         ###   ########.fr       */
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
	printf("%zu\n", i);
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
		if (check_nl(stack, line))
			break;
	}
	if (ret > 0)
		return (1);
	return (ret);
}

/*int		get_next_line(const int fd, char **line)
{
	char	*buff;

	if (( fd < 0 || fd <= MAX_FD) || (!(buff = (char *)malloc(BUFF_SIZE + 1)))\ 
			|| line == NULL || read(fd, stack[fd], 0) < 0) //why stack[fd]
		return (-1);
	bzero(buff, BUFF_SIZE - 1);
	ret = update_stack(fd, stack[fd], line, buff); //updates stack: add content with \n
	free(buff);

}*/

int		main()
{
	int fd = open("text.txt", O_RDONLY);
	static char		*stack[MAX_BUFF];
	char			*buff = NULL;
	char			**line = NULL;
	//int i = 0;

	//if (!(buff = (char *)malloc(BUFF_SIZE + 1)))
	//	return -1;
	//while (i < 10)
	//	buff[i++] = '\0';

	if (!(buff = (char *)malloc(BUFF_SIZE + 1)))
		return (0);
	bzero(buff, BUFF_SIZE);
	int ret = update_stack(fd, &stack[fd], line, buff);
	//int ret = read(fd, buff, BUFF_SIZE);
	//buff[ret] = '\0';
	//*stack = strdup(buff);
	printf("%s\n", *line);
	return 0;
}
