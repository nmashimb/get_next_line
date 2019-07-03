/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmashimb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 10:14:47 by nmashimb          #+#    #+#             */
/*   Updated: 2019/07/03 16:13:53 by nmashimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t		ft_strlen(const char *str)
{
	size_t len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

static void	ft_strdel(char **as)
{
	if (!as)
		return ;
	free(*as);
	*as = NULL;
}

static char	*ft_strnew(size_t size)
{
	size_t	i;
	char	*str;

	str = (char *)malloc(size + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i <= size + 1)
	{
		str[i] = 0;
		i++;
	}
	return (str);
}

static char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (0);
	str = (char *)malloc(len + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*ft_strchr(const char *s, int c)
{
	size_t i;

	i = 0;
	while (s[i] != (char)c)
	{
		if (s[i] == '\0')
			return (NULL);
		i++;
	}
	return ((char *)&s[i]);
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

static	int		ft_get_line(int fd, char **stack, char **line, int ret)
{
	char	*hold;
	int		i;

	i = 0;
	while (stack[fd][i] != '\n' && stack[fd][i] != '\0')
		i++;
	if (stack[fd][i] == '\n')
	{
		*line = ft_strsub(stack[fd], 0, i);
		hold = ft_strdup(stack[fd] + i + 1);
		free(stack[fd]);
		stack[fd] = hold;
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

int		get_next_line(const int fd, char **line)
{
	static char		*stack[1024 + 1];
	char			buff[BUFF_SIZE];
	char			*tmp;
	int				ret;

	if (fd < 0 || line == NULL)
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

/*int		main()
{
	int fd = open("text.txt", O_RDONLY);
	char		*line = NULL;
	
	get_next_line(fd, &line);
	int count = 1;
	while(count == 1)
	{
		count = get_next_line(fd, &line);
		printf("%d  %s\n", count,line);
	}
	
	printf("%d\n", count);
	return 0;
}*/
