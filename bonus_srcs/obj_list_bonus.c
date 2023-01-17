/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_list_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjoon <seungjoon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 21:08:17 by seungjoon         #+#    #+#             */
/*   Updated: 2023/01/17 13:53:03 by seungjoon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	obj_list_init(t_obj *head)
{
	head->element = NULL;
	head->type = -1;
	head->next = NULL;
}

int	obj_add(t_obj *head, int type, void *object)
{
	t_obj	*new;
	t_obj	*cur;

	if (object == NULL)
		return (1);
	cur = head;
	while (cur->next)
		cur = cur->next;
	new = (t_obj *)malloc(sizeof(t_obj));
	if (new == NULL)
		return (1);
	cur->next = new;
	cur->next->next = NULL;
	cur->next->type = type;
	cur->next->element = object;
	return (0);
}

void	obj_clear(t_obj *head)
{
	t_obj	*temp;

	while (head->next)
	{
		temp = head->next->next;
		free(head->next->element);
		free(head->next);
		head->next = temp;
	}
}

void	minirt_clear(t_scene *scene, t_compo *compo)
{
	t_obj	*obj;

	obj = &scene->world;
	obj_clear(obj);
	obj = &scene->light;
	obj_clear(obj);
	compo_clear(compo);
}
