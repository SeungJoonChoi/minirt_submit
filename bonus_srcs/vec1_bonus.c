/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec1_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjoon <seungjoon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 21:21:18 by seungjoon         #+#    #+#             */
/*   Updated: 2023/01/17 13:53:14 by seungjoon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_vec	vec(double x, double y, double z)
{
	t_vec	ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

t_vec	v_sum(t_vec vec1, t_vec vec2)
{
	t_vec	ret;

	ret.x = vec1.x + vec2.x;
	ret.y = vec1.y + vec2.y;
	ret.z = vec1.z + vec2.z;
	return (ret);
}

t_vec	v_sub(t_vec vec1, t_vec vec2)
{
	t_vec	ret;

	ret.x = vec1.x - vec2.x;
	ret.y = vec1.y - vec2.y;
	ret.z = vec1.z - vec2.z;
	return (ret);
}

t_vec	v_mul(t_vec vec, double t)
{
	t_vec	ret;

	ret.x = vec.x * t;
	ret.y = vec.y * t;
	ret.z = vec.z * t;
	return (ret);
}

t_vec	v_div(t_vec vec, double t)
{
	t_vec	ret;

	ret.x = vec.x / t;
	ret.y = vec.y / t;
	ret.z = vec.z / t;
	return (ret);
}
