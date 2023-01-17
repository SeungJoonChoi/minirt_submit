/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjoon <seungjoon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:56:42 by seungjoon         #+#    #+#             */
/*   Updated: 2023/01/17 15:02:42 by seungjoon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	invalid_double(char *number)
{
	int	dot_count;

	dot_count = 0;
	if (number == NULL || ft_strlen(number) <= 0 || *number == '.')
		return (1);
	while (ft_isdigit(*number) || *number == '.' || \
			*number == '+' || *number == '-')
	{
		if (*number == '.')
			++dot_count;
		++number;
	}
	if (*number != '\0' || dot_count > 1)
		return (1);
	return (0);
}

int	invalid_vec(char *vec)
{
	int		i;
	char	**e;

	e = ft_split(vec, ',');
	if (e == NULL)
		return (1);
	i = 0;
	while (e[i])
	{
		if (e[i][0] == '\0' || invalid_double(e[i]))
		{
			free_strs(e);
			return (1);
		}
		++i;
	}
	if (i != 3)
	{
		free_strs(e);
		return (1);
	}
	free_strs(e);
	return (0);
}

int	vec_range(t_vec *vec, double min, double max)
{
	if (vec->x < min || vec->x > max || vec->y < min || \
			vec->y > max || vec->z < min || vec->z > max)
		return (1);
	return (0);
}

int	double_range(double *d, double min, double max)
{
	if (*d < min || *d > max)
		return (1);
	return (0);
}
