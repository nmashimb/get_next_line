/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmashimb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 12:32:38 by nmashimb          #+#    #+#             */
/*   Updated: 2019/06/27 14:49:20 by nmashimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <string.h>
#include <stdlib.h> //free/malloc 
#include <unistd.h> //read

#define BUFF_SIZE 40
#define MAX_FD 1024 + 1

int   get_next_line(const int fd, char **line);
char	*ft_strjoin(char const *s1, char const *s2);

#endif
