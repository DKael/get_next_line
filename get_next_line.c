/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:06:51 by hyungdki          #+#    #+#             */
/*   Updated: 2023/01/12 16:06:52 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

#include <stdio.h>

char	*get_next_line(int fd)
{
	static t_fd	*fd_start;
	t_data		data;

	data.iter = fd_start;
	while (data.iter != NULL && data.iter->fd != fd)
	{
		data.iter_back = data.iter;
		data.iter = data.iter->next;
	}
	if (data.iter == NULL)
	{
		data.iter = (t_fd *)malloc(sizeof(t_fd));
		if (data.iter == NULL)
			return (NULL);
		data.iter->fd = fd;
		data.iter->start = 0;
		data.iter->next = fd_start;
		fd_start = data.iter;
		data.iter_back = fd_start;
	}
	data.node.size = 0;
	(data.node.buffer)[0] = '\0';
	if (data.iter->start != 0)
		return (get_result(&fd_start, data));
	return (read_lines(&fd_start, data));
}

char	*get_result(t_fd **fd_start, t_data data)
{
	int		idx;
	t_fd	*it;

	it = data.iter;
	idx = it->start;
	while (idx < BUFFER_SIZE && it->buffer[idx] != '\n' && idx < it->end)
		idx++;
	if (idx == BUFFER_SIZE)
	{
		data.node.size = idx - it->start;
		ft_memmove(data.node.buffer, &(it->buffer[it->start]), data.node.size);
		return (read_lines(&fd_start, data));
	}
	else
		return (return_remains(&fd_start, data, idx, it));
}

char	*return_remains(t_fd **fd_start, t_data data, int idx, t_fd	*it)
{
	int		flag;
	char	*result;

	flag = 0;
	if (data.iter->buffer[idx] == '\n')
		flag = 1;
	result = (char *)malloc(sizeof(char) * (idx - it->start + flag + 1));
	if (result == NULL)
		return (free_fd_and_node(&fd_start, data));
	result[idx - it->start + flag] = '\0';
	ft_memmove(result, &(it->buffer[it->start]), idx - it->start + flag);
	if (flag == 1)
		it->start = idx + 1;
	else
		free_fd_and_node(&fd_start, data);
	return (result);
}

void	*free_fd_and_node(t_fd **fd_start, t_data data)
{
	if (data.iter != data.iter_back)
		data.iter_back->next = data.iter->next;
	else
		*fd_start = data.iter->next;
	free(data.iter);
	return (ft_lstclear(&(data.node.next)));
}

char	*read_lines(t_fd **fd_start, t_data data)
{
	int 	read_cnt;
	int		idx1;
	t_temp	*tmake;
	t_temp	*pos;

	read_cnt = read(data.iter->fd, data.iter->buffer, BUFFER_SIZE);
	if (read_cnt == -1 || read_cnt == 0)
		return (free_fd_and_node(&fd_start, data));
	pos = &(data.node);
	while (read_cnt == BUFFER_SIZE)
	{
		tmake = (t_temp *)malloc(sizeof(t_temp));
		if (tmake == NULL)
			return (free_fd_and_node(&fd_start, data));
		tmake->next = NULL;
		pos->next = tmake;
		pos = tmake;
		tmake->size = BUFFER_SIZE;
		idx1 = 0;
		while (idx1 < BUFFER_SIZE && data.iter->buffer[idx1] != '\n')
			idx1++;
		if (data.iter->buffer[idx1] == '\n')
		{
			ft_memmove(tmake->buffer, data.iter->buffer, idx1 + 1);
			if (idx1 + 1 != read_cnt)
			{
				data.iter->end = read_cnt;
				data.iter->start = idx1 + 1;
			}
			else
				data.iter->start = 0;
			tmake->size = idx1 + 1;
			return (do_concat(&(data.node)));
		}
		else
			ft_memmove(tmake->buffer, data.iter->buffer, idx1);
		read_cnt = read(data.iter->fd, data.iter->buffer, BUFFER_SIZE);
		if (read_cnt == -1 || read_cnt == 0)
			return (free_fd_and_node(&fd_start, data));
	}
//-------------------------------------------
	tmake = (t_temp *)malloc(sizeof(t_temp));
	tmake->next = NULL;
	pos->next = tmake;
	idx1 = 0;
	while (idx1 < read_cnt && data.iter->buffer[idx1] != '\n')
		idx1++;
	if (data.iter->buffer[idx1] == '\n')
	{
		ft_memmove(tmake->buffer, data.iter->buffer, idx1 + 1);
		if (idx1 + 1 != read_cnt)
		{
			data.iter->end = read_cnt;
			data.iter->index = idx1 + 1;
		}
		else
			data.iter->index = 0;
		tmake->size = idx1 + 1;
	}
	else
	{
		ft_memmove(tmake->buffer, data.iter->buffer, idx1);
		if (data.iter != data.iter_back)
			data.iter_back->next = data.iter->next;
		else
			nstart = data.iter->next;
		free(data.iter);
		tmake->size = idx1;
	}
	return (do_concat(&(data.tstart)));
}
