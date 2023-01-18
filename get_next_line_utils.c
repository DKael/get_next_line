/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:07:13 by hyungdki          #+#    #+#             */
/*   Updated: 2023/01/12 16:07:14 by hyungdki         ###   ########.fr       */
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

void	*ft_lstclear(t_temp **lst)
{
	t_temp	*delete;
	t_temp	*next_fd;

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

char	*do_concat(t_temp *tstart)
{
	char	*result;
	int		len;
	int		idx;
	t_temp	*position;

	position = tstart;
	len = 0;
	while (position != NULL)
	{
		len += position->size;
		position = position->next;
	}
	result = (char *)malloc(sizeof(char) * (len + 1));
	position = tstart;
	idx = 0;
	while (position != NULL)
	{
		ft_memmove(&result[idx], position->buffer, position->size);
		idx += position->size;
		position = position->next;
	}
	result[len] = '\0';
	ft_lstclear(&(tstart->next));
	return (result);
}
