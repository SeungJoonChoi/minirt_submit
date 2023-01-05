/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjoon <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:20:42 by seungjoon         #+#    #+#             */
/*   Updated: 2023/01/05 20:21:09 by seungjoon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	color(double r, double g, double b)
{
	t_color	ret;

	ret.x = r;
	ret.y = g;
	ret.z = b;
	return (ret);
}

t_color	ray_color(t_scene *scene)
{
	double	t;

	if (hit(&scene->ray, &scene->world, &scene->rec))
		return (phong_lighting(scene));
	t = 0.5 * (scene->ray.d.y + 1.0);
	return (vec(1.0 - (0.5 * t), 1.0 - (0.3 * t), 1.0));
}
