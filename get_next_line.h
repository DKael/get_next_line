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
# define BUFFER_SIZE 100
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>

typedef struct s_node
{
	unsigned int	fd;
	int				index;
	int				end;
	char 			buffer[BUFFER_SIZE];
	struct s_node	*next;
}	t_node;

typedef struct s_temp
{
	int				size;
	char			buffer[BUFFER_SIZE];
	struct s_temp	*next;
}	t_temp;

char	*get_next_line(int fd);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_lstclear(t_temp **lst);
char	*do_concat(t_temp *tstart);

#endif