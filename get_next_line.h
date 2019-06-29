/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmashimb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 12:32:38 by nmashimb          #+#    #+#             */
/*   Updated: 2019/06/29 14:42:36 by nmashimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <string.h>
#include <stdlib.h> //free/malloc 
#include <unistd.h> //read

#define BUFF_SIZE 32
#define MAX_FD 1024 + 1

int   get_next_line(const int fd, char **line);

#endif
