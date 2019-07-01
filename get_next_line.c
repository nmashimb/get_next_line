/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmashimb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 13:42:49 by nmashimb          #+#    #+#             */
/*   Updated: 2019/06/29 17:19:01 by nmashimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
//#include <stdio.h>

static size_t		ft_strlen(const char *str)
{
	size_t len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

static char	*ft_strdup(const char *s1)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc(ft_strlen(s1) + 1);
	if (str == NULL)
		return (0);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	while (*s1)
	{
		*str = *s1;
		s1++;
		str++;
	}
	while (*s2)
	{
		*str = *s2;
		s2++;
		str++;
	}
	*str = '\0';
	str = str - len;
	return (str);
}

//checks if file has nl (valid). if so, retrives line and stack points to !st chr of next ln
//works!!
static	int		check_nl(char **stack, char **line)
{
	size_t	i;
	//size_t	j;
	char	*endof_ln;
	char	*nl_pntr;

	i = 0;
	//j = 0;
	nl_pntr = *stack;
	/*while (nl_pntr[j] == '\n')
		j++;
	i = j;*/
	//nl_pntr[(ft_strlen(nl_pntr)) - 1] = '\0'; //added
	while (nl_pntr[i] != '\n')
	{
		if (nl_pntr[i] == '\0')
			return (0);
		i++;
	}
	endof_ln = &nl_pntr[i];
	*endof_ln = '\0';
	*line = ft_strdup(*stack);
	//*line = ft_strsub(*stack, j, i - j);
	*stack = ft_strdup(endof_ln + 1);
	return (1);
}

static	int		update_stack(int fd, char **stack, char **line, char *buff)
{
	char	*tmp;
	int		ret;

	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (*stack)
		{
			tmp = *stack;
			*stack = ft_strjoin(tmp, buff);
			free(tmp);
			tmp = NULL;
		}
		else
			*stack = ft_strdup(buff);
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
	int i = 0;
	while (i < BUFF_SIZE)
		buff[i++] = '\0';
	ret = update_stack(fd, &stack[fd], line, buff); //updates stack: add content with \n
	free(buff);
	buff = NULL;
	//case where theres nothing in file ?
	if (ret != 0 || stack[fd] == NULL ||stack[fd][0] == '\0')
	{
		if (ret == 0 && *line) //and line exist?
			*line = NULL;
		return (ret);
	}
	*line = stack[fd]; //allocating last line
	stack[fd] = NULL;
	return (1);
}

/*int		main()
{
	int fd = open("text.txt", O_RDONLY);
	char			*line = NULL;

	int x = get_next_line(fd, &line);

	//printf("%d\n", x);
	return 0;
}*/

/*int		main()
{
	int fd = open("text.txt", O_RDONLY);
	char			*line = NULL;

	int count = 1;
	while(count == 1)
	{
		count = get_next_line(fd, &line);
		printf("%d  %s\n", count,line);

	}
	putchar(10);
	printf("%d\n", count);
	return 0;
}*/
