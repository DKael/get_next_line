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
#  define BUFFER_SIZE 128
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_fd
{
	int			fd;
	int			start;
	int			end;
	char		buffer[BUFFER_SIZE];
	struct s_fd	*next;
}	t_fd;

typedef struct s_temp
{
	int				size;
	char			buffer[BUFFER_SIZE];
	struct s_temp	*next;
}	t_temp;

typedef struct s_data
{
	t_fd	*iter;
	t_fd	*iter_back;
	t_temp	node;
}	t_data;

char	*get_next_line(int fd);

char	*get_result(t_fd **nstart, t_data data);
char	*read_lines1(t_fd **fd_start, t_data data);
char	*read_lines2(t_fd **fd_start, t_data data);
char	*return_remains(t_fd **fd_start, t_data data, int idx, t_fd	*it);

void	*ft_memmove(void *dst, const void *src, size_t n);
void	*ft_lstclear(t_temp **lst);
char	*do_concat(t_temp *tstart);
void	*free_fd_and_node(t_fd **fd_start, t_data data);
char	*make_node(t_fd **fd_start, t_data data, t_temp **tmake, t_temp **pos)
#endif