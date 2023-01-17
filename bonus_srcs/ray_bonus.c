/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjoon <seungjoon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 21:10:14 by seungjoon         #+#    #+#             */
/*   Updated: 2023/01/17 13:53:07 by seungjoon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_ray	ray_set(t_vec *origin, t_vec *direction)
{
	t_ray	ret;

	ret.o = *origin;
	ret.d = unit(*direction);
	return (ret);
}

t_vec	ray_at(t_ray *ray, double t)
{
	t_vec	ret;

	ret.x = ray->o.x + ray->d.x * t;
	ret.y = ray->o.y + ray->d.y * t;
	ret.z = ray->o.z + ray->d.z * t;
	return (ret);
}

t_ray	ray_viewport(t_scene *scene, double u, double v)
{
	t_ray		ret;
	t_camera	*c;

	c = &scene->camera;
	ret.o = c->orig;
	ret.d.x = c->lower_left.x + u * c->horiz.x + v * c->vert.x - c->orig.x;
	ret.d.y = c->lower_left.y + u * c->horiz.y + v * c->vert.y - c->orig.y;
	ret.d.z = c->lower_left.z + u * c->horiz.z + v * c->vert.z - c->orig.z;
	ret.d = unit(ret.d);
	scene->rec.t_max = INFINITY;
	scene->rec.t_min = 0.0;
	return (ret);
}
