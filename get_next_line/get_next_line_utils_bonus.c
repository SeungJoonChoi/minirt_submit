/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunchoi <seunchoi@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:36:23 by seunchoi          #+#    #+#             */
/*   Updated: 2022/02/10 13:36:25 by seunchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_dupjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*ret;

	if (s1)
		str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) \
				* sizeof(char));
	else
		str = (char *)malloc((ft_strlen(s2) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ret = str;
	while (s1 && *s1 != '\0')
	{
		*str = *s1;
		str++;
		s1++;
	}
	while (*s2 != '\0')
	{
		*str = *s2;
		str++;
		s2++;
	}
	*str = '\0';
	return (ret);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	i;

	src_len = ft_strlen(src);
	i = 0;
	while ((i + 1) < dstsize && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize > 0)
		dst[i] = '\0';
	return (src_len);
}

char	*ft_strchr(const char *s, int c)
{
	int		len;

	len = ft_strlen(s);
	while (0 < len + 1)
	{
		if (*s == (char)c)
			return ((char *)s);
		len--;
		s++;
	}
	return (NULL);
}

t_list	*get_node(t_list *head, int fd)
{
	t_list	*node;

	node = head->next;
	while (node)
	{
		if (node->fd == fd)
			return (node);
		else
			node = node->next;
	}
	node = (t_list *)malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->fd = fd;
	node->backup = NULL;
	node->prev = head;
	node->next = head->next;
	if (head->next)
		head->next->prev = node;
	head->next = node;
	return (node);
}

char	*del_node(t_list **node)
{
	free((*node)->backup);
	(*node)->prev->next = (*node)->next;
	if ((*node)->next)
		(*node)->next->prev = (*node)->prev;
	free(*node);
	*node = NULL;
	return (NULL);
}
