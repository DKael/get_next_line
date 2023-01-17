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
	static t_node	nstart;
	t_node	*iter;

	iter = &nstart;
	while (iter != NULL && iter->fd != fd)
		iter = iter->next;
	if (iter == NULL)
	{
		iter = (t_node *)malloc(sizeof(t_node));
		if (iter == NULL)
			return (NULL);
		iter->fd = fd;
		iter->index = 0;
		iter->next = nstart.next;
		iter->before = &nstart;
		iter->next->before = iter;
		nstart.next = iter;
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
		while (idx < BUFFER_SIZE && iter->buffer[idx] != '\n' && idx < iter->back)
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
			if (iter->fd != 0)
			{
				if (iter->next != NULL)
					iter->next->before = iter->before;
				iter->before->next = iter->next;
				free(iter);
			}
			return (result);
		}
	}
//---------------------------------------------------------------------------------------------
	int 	read_cnt;
	int		idx1;
	t_temp	*tmake;
	t_temp	*position;

	read_cnt = read(fd, iter->buffer, BUFFER_SIZE);
	if (read_cnt == -1)
		return (NULL);
	position = &tstart;
	while (read_cnt == BUFFER_SIZE)
	{
		idx1 = 0;
		while (idx1 < BUFFER_SIZE && iter->buffer[idx1] != '\n')
			idx1++;
		tmake = (t_temp *)malloc(sizeof(t_temp));
		if (tmake == NULL)
			return (ft_lstclear(tstart.next));
		ft_memcpy(tmake->buffer, iter->buffer, idx1 + 1);
		position->next = tmake;
		position = tmake;
		if (iter->buffer[idx1] == '\n')
		{
			iter->back = read_cnt;
			iter->index = idx1 + 1;
			return (do_concat(&tstart));
		}
		read_cnt = read(fd, iter->buffer, BUFFER_SIZE);
	}



	return 0;
}

#include <fcntl.h>
int main()
{
	int fd = open("a.txt", O_RDONLY);
	char x[20];
	int count = read(fd, x, 20);
	for (int i = 0; i <= 20; i++)
	{
		write(2, x, 1);
	}
}