/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjoon <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:57:27 by seungjoon         #+#    #+#             */
/*   Updated: 2023/01/05 20:58:57 by seungjoon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_a(t_compo *head, char **split)
{
	int	i;

	i = 0;
	while (split[i])
		++i;
	if (i != 3 || invalid_double(split[1]) || invalid_vec(split[2]))
		exit_compo_clear(head, "Invalid file form.");
}

void	check_c(t_compo *head, char **split)
{
	int	i;

	i = 0;
	while (split[i])
		++i;
	if (i != 4 || invalid_vec(split[1]) || invalid_vec(split[2]) \
			|| invalid_double(split[3]))
		exit_compo_clear(head, "Invalid file form.");
}

void	check_l_sp(t_compo *head, char **split)
{
	int	i;

	i = 0;
	while (split[i])
		++i;
	if (i != 4 || invalid_vec(split[1]) || invalid_double(split[2]) \
			|| invalid_vec(split[3]))
		exit_compo_clear(head, "Invalid file form.");
}

void	check_pl(t_compo *head, char **split)
{
	int	i;

	i = 0;
	while (split[i])
		++i;
	if (i != 4 || invalid_vec(split[1]) || invalid_vec(split[2]) || \
			invalid_vec(split[3]))
		exit_compo_clear(head, "Invalid file form.");
}

void	check_cy(t_compo *head, char **split)
{
	int	i;

	i = 0;
	while (split[i])
		++i;
	if (i != 6 || invalid_vec(split[1]) || invalid_vec(split[2]) || \
			invalid_double(split[3]) || invalid_double(split[4]) \
			|| invalid_vec(split[5]))
		exit_compo_clear(head, "Invalid file form.");
}
