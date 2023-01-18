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
#include "get_next_line_utils.c"

#include <stdio.h>

char *get_next_line(int fd)
{
	static t_node	*nstart;
	t_node			*iter;
	t_node			*iter_back;
	int				read_cnt1;

	iter = nstart;
	while (iter != NULL && iter->fd != fd)
	{
		iter_back = iter;
		iter = iter->next;
	}
	if (iter == NULL)
	{
		iter = (t_node *)malloc(sizeof(t_node));
		if (iter == NULL)
			return (NULL);
		iter->fd = fd;
		iter->index = 0;
		iter->next = nstart;
		nstart = iter;
		iter_back = nstart;
	}
//---------------------------------------------------------------------------------------------
	int		idx;
	char	*result;
	t_temp	tstart;

	tstart.size = 0;
	(tstart.buffer)[0] = '\0';
	tstart.next = NULL;
	if (iter->index != 0)
	{
		idx = iter->index;
		while (idx < BUFFER_SIZE && iter->buffer[idx] != '\n' && idx < iter->end)
			idx++;
		if (idx == BUFFER_SIZE)
		{
			tstart.size = idx - iter->index;
			ft_memcpy(tstart.buffer, &(iter->buffer[iter->index]), tstart.size);
		}
		else if (iter->buffer[idx] == '\n')
		{
			result = (char *)malloc(sizeof(char) * (idx - iter->index + 2));
			if (result == NULL)
				return (NULL);
			ft_memcpy(result, &(iter->buffer[iter->index]), idx - iter->index + 1);
			result[idx - iter->index + 1] = '\0';
			iter->index = idx + 1;
			return (result);
		}
		else
		{
			result = (char *)malloc(sizeof(char) * (idx - iter->index + 1));
			if (result == NULL)
				return (NULL);
			ft_memcpy(result, &(iter->buffer[iter->index]), idx - iter->index);
			result[idx - iter->index] = '\0';
			if (iter != iter_back)
				iter_back->next = iter->next;
			else
				nstart = iter->next;
			free(iter);
			return (result);
		}
	}
//---------------------------------------------------------------------------------------------
	int 	read_cnt;
	int		idx1;
	t_temp	*tmake;
	t_temp	*pos;

	read_cnt = read(fd, iter->buffer, BUFFER_SIZE);
	if (read_cnt == -1 || read_cnt == 0)
		return (NULL);
	pos = &tstart;
	while (read_cnt == BUFFER_SIZE)
	{
		tmake = (t_temp *)malloc(sizeof(t_temp));
		if (tmake == NULL)
			return (ft_lstclear(&(tstart.next)));
		tmake->next = NULL;
		pos->next = tmake;
		pos = tmake;
		tmake->size = BUFFER_SIZE;
		idx1 = 0;
		while (idx1 < BUFFER_SIZE && iter->buffer[idx1] != '\n')
			idx1++;
		if (iter->buffer[idx1] == '\n')
		{
			ft_memcpy(tmake->buffer, iter->buffer, idx1 + 1);
			if (idx1 + 1 != read_cnt)
			{
				iter->end = read_cnt;
				iter->index = idx1 + 1;
			}
			else
				iter->index = 0;
			tmake->size = idx1 + 1;
			return (do_concat(&tstart));
		}
		else
			ft_memcpy(tmake->buffer, iter->buffer, idx1);
		read_cnt = read(fd, iter->buffer, BUFFER_SIZE);
		if (read_cnt == -1 || read_cnt == 0)
			return (ft_lstclear(&(tstart.next)));
	}
//---------------------------------------------------------------------------------------------
	tmake = (t_temp *)malloc(sizeof(t_temp));
	if (tmake == NULL)
		return (ft_lstclear(&(tstart.next)));
	tmake->next = NULL;
	pos->next = tmake;
	idx1 = 0;
	while (idx1 < read_cnt && iter->buffer[idx1] != '\n')
		idx1++;
	if (iter->buffer[idx1] == '\n')
	{
		ft_memcpy(tmake->buffer, iter->buffer, idx1 + 1);
		if (idx1 + 1 != read_cnt)
		{
			iter->end = read_cnt;
			iter->index = idx1 + 1;
		}
		else
			iter->index = 0;
		tmake->size = idx1 + 1;
	}
	else
	{
		ft_memcpy(tmake->buffer, iter->buffer, idx1);
		if (iter != iter_back)
				iter_back->next = iter->next;
		else
			nstart = iter->next;
		free(iter);
		tmake->size = idx1;
	}
	return (do_concat(&tstart));
}
