/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmashimb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 13:42:49 by nmashimb          #+#    #+#             */
/*   Updated: 2019/06/20 11:48:39 by nmashimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

//checks if file has nl (valid). if so, retrives line and stack points to !st chr of next ln
//works!!
/*int		check_nl(char **paragraph, char **line)
{
	size_t	i;
	char	*endof_ln;
	char	*nl_pntr;

	i = 0;
	nl_pntr = *paragraph;
	while (nl_pntr[i] != '\n')
	{
		if (nl_pntr[i] == '\0')
			return (0);
		i++;
	}
	endof_ln = &nl_pntr[i];
	*endof_ln = '\0';
	*line = strdup(*paragraph); //change me
	*paragraph = strdup(endof_ln + 1); //change me
	return (1);
}*/

int		get_next_line(const int fd, char **line)
{
	char	*heap_str;

	if (( fd < 0 || fd <= MAX_FD) || (!(heap_str = (char *)malloc(BUFF_SIZE + 1)))\ 
			|| line == NULL || read(fd, stack[fd], 0) < 0) //why stack[fd]
		return (-1);

	
}

int		main()
{

	return 0;
}
