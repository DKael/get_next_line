/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 20:59:42 by hyungdki          #+#    #+#             */
/*   Updated: 2023/01/19 20:59:43 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

#include <stdio.h>

char	*get_next_line(int fd)
{
	static t_fd_node	*start;
	t_data				data;

	data.fd_start = &start;
	data.it = start;
	data.it_back = start;
	while (data.it != NULL && data.it->fd != fd)
	{
		data.it_back = data.it;
		data.it = data.it->next;
	}
	if (data.it == NULL)
	{
		data.it = (t_fd_node *)malloc(sizeof(t_fd_node));
		if (data.it == NULL)
			return (NULL);
		data.it->fd = fd;
		data.it->start = 0;
		data.it->next = start;
		start = data.it;
		data.it_back = start;
	}
	data.node.size = 0;
	data.node.next = NULL;
	return (get_buffer_remains(&data));
}

char	*get_buffer_remains(t_data *data)
{
	int			idx;
	char		*result;
	t_fd_node	*it;

	it = (*data).it;
	idx = (*data).it->start;
	if (it->start != 0 && it->end > it->start)
	{
		while (idx < BUFFER_SIZE && it->bf[idx] != '\n' && idx < it->end)
			idx++;
		if (idx == BUFFER_SIZE)
		{
			(*data).node.size = idx - it->start;
			ft_memmove((*data).node.bf,
				&(it->bf[it->start]), (*data).node.size);
			result = read_lines1(data);
		}
		else
			result = case_nl_eof(data, idx, it);
	}
	else
		result = read_lines1(data);
	if (result == NULL)
		return (free_fd_and_node(data));
	return (result);
}

char	*case_nl_eof(t_data *data, int idx, t_fd_node *it)
{
	char	*result;

	if (it->bf[idx] == '\n')
	{
		result = (char *)malloc(sizeof(char) * (idx - it->start + 2));
		if (result == NULL)
			return (NULL);
		result[idx - it->start + 1] = '\0';
		ft_memmove(result, &(it->bf[it->start]), idx - it->start + 1);
		it->start = idx + 1;
		return (result);
	}
	else
	{
		result = (char *)malloc(sizeof(char) * (idx - it->start + 1));
		if (result == NULL)
			return (NULL);
		result[idx - it->start] = '\0';
		ft_memmove(result, &(it->bf[it->start]), idx - it->start);
		if ((*data).it != (*data).it_back)
			(*data).it_back->next = (*data).it->next;
		else
			*((*data).fd_start) = (*data).it->next;
		return (free((*data).it), result);
	}
}

char	*read_lines1(t_data *data)
{
	int		idx;
	t_lnode	*tmake;
	t_lnode	*pos;

	(*data).it->read = read((*data).it->fd, (*data).it->bf, BUFFER_SIZE);
	if ((*data).it->read == -1
		|| ((*data).it->read == 0 && (*data).node.size == 0))
		return (NULL);
	pos = &((*data).node);
	while ((*data).it->read == BUFFER_SIZE)
	{
		idx = 0;
		parse(data, &idx, &pos, &tmake);
		if (tmake == NULL)
			return (NULL);
		if ((*data).it->bf[idx] == '\n')
			return (do_concat(&((*data).node)));
		(*data).it->read = read((*data).it->fd, (*data).it->bf, BUFFER_SIZE);
		if ((*data).it->read == -1)
			return (NULL);
	}
	return (read_lines2(data, &idx, &pos, &tmake));
}

char	*read_lines2(t_data *data, int *idx, t_lnode **pos, t_lnode **tmake)
{
	if ((*data).it->read == 0 && (*data).node.size != 0)
	{
		if ((*data).it != (*data).it_back)
			(*data).it_back->next = (*data).it->next;
		else
			*((*data).fd_start) = (*data).it->next;
		return (free((*data).it), do_concat(&((*data).node)));
	}
	(*idx) = 0;
	parse(data, idx, pos, tmake);
	if ((*tmake) == NULL)
		return (NULL);
	if ((*data).it->bf[(*idx)] != '\n')
	{
		if ((*data).it != (*data).it_back)
			(*data).it_back->next = (*data).it->next;
		else
			*((*data).fd_start) = (*data).it->next;
		free((*data).it);
	}
	return (do_concat(&((*data).node)));
}
