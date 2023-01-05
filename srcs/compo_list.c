/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compo_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjoon <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:21:23 by seungjoon         #+#    #+#             */
/*   Updated: 2023/01/05 20:22:21 by seungjoon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	compo_list_init(t_compo *head)
{
	head->split_line = NULL;
	head->next = NULL;
}

int	compo_add(t_compo *head, char **split)
{
	t_compo	*new;
	t_compo	*cur;

	if (split == NULL)
		return (1);
	cur = head;
	while (cur->next)
		cur = cur->next;
	new = (t_compo *)malloc(sizeof(t_compo));
	if (new == NULL)
		return (1);
	cur->next = new;
	cur->next->next = NULL;
	cur->next->split_line = split;
	return (0);
}

void	compo_clear(t_compo *head)
{
	t_compo	*temp;

	while (head->next)
	{
		temp = head->next->next;
		free_strs(head->next->split_line);
		free(head->next);
		head->next = temp;
	}
}
