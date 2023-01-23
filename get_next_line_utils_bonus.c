/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:23:45 by hyungdki          #+#    #+#             */
/*   Updated: 2023/01/23 17:24:01 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			index;
	unsigned char	*dst_cptr;
	unsigned char	*src_cptr;

	index = -1;
	dst_cptr = (unsigned char *)dst;
	src_cptr = (unsigned char *)src;
	if (dst != NULL || src != NULL)
	{
		if (src - dst > 0)
		{
			while (++index < len)
				dst_cptr[index] = src_cptr[index];
		}
		else
		{
			while (++index < len)
				dst_cptr[len - index - 1] = src_cptr[len - index - 1];
		}
	}
	return (dst);
}

void	*ft_lstclear(t_lnode **lst)
{
	t_lnode	*delete;
	t_lnode	*next_fd;

	if ((*lst) != NULL)
	{
		next_fd = (*lst);
		while (next_fd != NULL)
		{
			delete = next_fd;
			next_fd = next_fd->next;
			free(delete);
		}
		*lst = NULL;
	}
	return (NULL);
}

char	*do_concat(t_lnode *node_start)
{
	char	*result;
	int		len;
	t_lnode	*position;

	position = node_start;
	len = 0;
	while (position != NULL)
	{
		len += position->size;
		position = position->next;
	}
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	result[len] = '\0';
	position = node_start;
	len = 0;
	while (position != NULL)
	{
		ft_memmove(&result[len], position->bf, position->size);
		len += position->size;
		position = position->next;
	}
	ft_lstclear(&(node_start->next));
	return (result);
}

void	*free_fd_and_node(t_data *data, int flag)
{
	if (data->it != NULL)
	{
		if (data->it != data->it_back)
			data->it_back->next = data->it->next;
		else
		{
			if (data->it->next != NULL)
				*(data->fd_start) = data->it->next;
			else
				*(data->fd_start) = NULL;
		}
		free(data->it);
		data->it = NULL;
	}
	if (flag == CLEAN_ALL)
		return (ft_lstclear(&(data->node.next)));
	else
		return (NULL);
}

void	parse(t_data *data, int *idx, t_lnode **pos, t_lnode **tmake)
{
	(*tmake) = (t_lnode *)malloc(sizeof(t_lnode));
	if ((*tmake) == NULL)
		return ;
	(*tmake)->next = NULL;
	(*pos)->next = (*tmake);
	(*pos) = (*tmake);
	while ((*idx) < data->it->read && data->it->bf[(*idx)] != '\n')
		(*idx)++;
	if (data->it->bf[(*idx)] == '\n' && (*idx) != data->it->read)
	{
		(*tmake)->size = (*idx) + 1;
		ft_memmove((*tmake)->bf, data->it->bf, (*idx) + 1);
		if ((*idx) + 1 != data->it->read)
		{
			data->it->end = data->it->read;
			data->it->start = (*idx) + 1;
		}
		else
			data->it->start = 0;
		return ;
	}
	if ((*idx) == data->it->read)
		data->it->start = 0;
	(*tmake)->size = data->it->read;
	ft_memmove((*tmake)->bf, data->it->bf, data->it->read);
}
