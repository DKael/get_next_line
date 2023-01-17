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

char *get_next_line(int fd)
{
	static t_node	nstart;
	t_node	*iter;

	// fd에 해당하는 노드 찾기
	// 0이면 스타트에서 멈춰있고, 0이 아닌 숫자중 찾으면 해당 노드에서 멈춰있고, 못 찾으면 노드 생성
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
		nstart.next = iter;
	}
	// 해당 iter는 해당 fd의 노드 주소를 가지고 있음
	// 이제 읽기
	int 	read_cnt;
	int		idx;
	char	*result;
	t_temp	tstart;

	if (iter->index != 0)
	{
		idx = iter->index;
		while (idx <= iter->back && iter->buffer[idx] != '\n' && iter->buffer[idx] != EOF)
			idx++;
		tstart.size = iter->back - iter->index + 1;
		if (iter->buffer[idx] == '\n')
			tstart.size == idx - iter->index + 1;
		else if (iter->buffer[idx] == EOF)
			tstart.size == idx - iter->index;
		if (idx == iter->back + 1)
			ft_memcpy(tstart.buffer, &(iter->buffer[iter->index]), tstart.size);
		else if (iter->buffer[idx] == '\n' || iter->buffer[idx] == EOF)
		{
			result = (char *)malloc(sizeof(char) * tstart.size);
			if (result == NULL)
				return (NULL);
			ft_memcpy(result, &(iter->buffer[iter->index]), tstart.size);
			iter->index = idx + 1;
			return (result);
		}
	}
	read_cnt = read(fd, iter->buffer, BUFFER_SIZE);
	if (read_cnt < BUFFER_SIZE)
	{
		idx = -1;
		while (++idx < read_cnt && iter->buffer[idx] != '\n')
		{
			
		}
	}
	while (read_cnt != EOF || read_cnt < BUFFER_SIZE)
	{
		read_cnt = read(fd, iter->buffer, BUFFER_SIZE);
	}

	return 0;
}

int main()
{
	get_next_line(0);
}