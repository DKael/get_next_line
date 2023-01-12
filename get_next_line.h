/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:06:58 by hyungdki          #+#    #+#             */
/*   Updated: 2023/01/12 16:07:00 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 1000
# endif

# include <unistd.h>
# include <stdlib.h>

typedef unsigned int fd;
typedef struct s_fdnode
{
	fd 				fd;
	char 			buffer[BUFFER_SIZE];
	struct s_fdnode	*next;
}	t_fdnode;

char	*get_next_line(int fd);

#endif
