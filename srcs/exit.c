/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjoon <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:55:24 by seungjoon         #+#    #+#             */
/*   Updated: 2023/01/05 20:55:33 by seungjoon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	exit_err(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(1);
}

void	exit_compo_clear(t_compo *head, char *msg)
{
	compo_clear(head);
	ft_putendl_fd(msg, 2);
	exit(1);
}
