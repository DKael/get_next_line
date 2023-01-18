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

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			index;
	unsigned char	*dst_char;
	unsigned char	*src_char;

	if (dst != NULL || src != NULL)
	{
		index = 0;
		dst_char = (unsigned char *)dst;
		src_char = (unsigned char *)src;
		while (index < n)
		{
			dst_char[index] = src_char[index];
			index++;
		}
	}
	return (dst);
}

void	*ft_lstclear(t_temp **lst)
{
	t_temp	*delete;
	t_temp	*next_node;

	if ((*lst) != NULL)
	{
		next_node = (*lst);
		while (next_node != NULL)
		{
			delete = next_node;
			next_node = next_node->next;
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
	if (result == NULL)
		return (NULL);
	position = tstart;
	idx = 0;
	while (position != NULL)
	{
		ft_memcpy(&result[idx], position->buffer, position->size);
		idx += position->size;
		position = position->next;
	}
	result[len] = '\0';
	ft_lstclear(&(tstart->next));
	return (result);
}