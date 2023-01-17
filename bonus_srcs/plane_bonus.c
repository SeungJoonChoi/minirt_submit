/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjoon <seungjoon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 21:09:23 by seungjoon         #+#    #+#             */
/*   Updated: 2023/01/17 13:53:05 by seungjoon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_plane	*plane(t_vec origin, t_vec dir, t_color albedo)
{
	t_plane	*new;

	if (vec_range(&dir, -1.0, 1.0) || vec_range(&albedo, 0.0, 1.0))
		return (NULL);
	new = (t_plane *)malloc(sizeof(t_plane));
	if (new == NULL)
		return (NULL);
	new->o = origin;
	if (dir.x == 0.0 && dir.y == 0.0 && dir.z == 0.0)
		dir = vec(0, 1, 0);
	new->d = unit(dir);
	new->albedo = albedo;
	return (new);
}

int	hit_plane(t_ray *ray, t_plane *plane, t_hit_record *rec)
{
	double	parallel;
	double	root;

	parallel = dot(plane->d, ray->d);
	if (parallel == 0)
		return (0);
	root = (dot(plane->d, plane->o) - dot(plane->d, ray->o)) / parallel;
	if (root < rec->t_min || root > rec->t_max)
		return (0);
	rec->t = root;
	rec->t_max = rec->t;
	rec->p = ray_at(ray, root);
	rec->n = plane->d;
	rec->albedo = plane->albedo;
	return (1);
}
