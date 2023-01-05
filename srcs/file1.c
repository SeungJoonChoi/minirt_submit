/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjoon <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:55:48 by seungjoon         #+#    #+#             */
/*   Updated: 2023/01/05 20:56:21 by seungjoon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	ele_number_check(t_compo *head)
{
	t_compo	*cur;
	int		a;
	int		c;
	int		l;

	a = 0;
	c = 0;
	l = 0;
	cur = head->next;
	while (cur)
	{
		if (!ft_strcmp(cur->split_line[0], "A"))
			++a;
		else if (!ft_strcmp(cur->split_line[0], "C"))
			++c;
		else if (!ft_strcmp(cur->split_line[0], "L"))
			++l;
		cur = cur->next;
	}
	if (a != 1 || c != 1 || l != 1)
		exit_compo_clear(head, "Invalid number of component.");
}

void	ele_form_check(t_compo *head)
{
	t_compo	*cur;

	ele_number_check(head);
	cur = head->next;
	while (cur)
	{
		if (!ft_strcmp(cur->split_line[0], "A"))
			check_a(head, cur->split_line);
		else if (!ft_strcmp(cur->split_line[0], "C"))
			check_c(head, cur->split_line);
		else if (!ft_strcmp(cur->split_line[0], "L"))
			check_l_sp(head, cur->split_line);
		else if (!ft_strcmp(cur->split_line[0], "sp"))
			check_l_sp(head, cur->split_line);
		else if (!ft_strcmp(cur->split_line[0], "pl"))
			check_pl(head, cur->split_line);
		else if (!ft_strcmp(cur->split_line[0], "cy"))
			check_cy(head, cur->split_line);
		else
			exit_compo_clear(head, "Invalid element type.");
		cur = cur->next;
	}
}

void	set_compo(t_compo *compo, int fd)
{
	char	*buf;
	char	**split_line;

	compo_list_init(compo);
	while (1)
	{
		buf = get_next_line(fd);
		if (buf && *buf != '\0')
		{
			split_line = ft_split(buf, ' ');
			if (compo_add(compo, split_line))
			{
				free(buf);
				compo_clear(compo);
				close(fd);
				exit_err("Can not open file.");
			}
		}
		else if (!buf)
			break ;
		free(buf);
	}
}
