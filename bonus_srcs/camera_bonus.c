/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjoon <seungjoon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:18:14 by seungjoon         #+#    #+#             */
/*   Updated: 2023/01/17 13:52:27 by seungjoon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static double	deg_to_rad(double theta)
{
	return (theta * M_PI / 180.0);
}

static t_vec	lower_left_corner(t_camera *camera)
{
	t_vec	ret;

	ret.x = camera->orig.x - (camera->horiz.x / 2.0) - \
		(camera->vert.x / 2.0) + camera->w.x;
	ret.y = camera->orig.y - (camera->horiz.y / 2.0) - \
		(camera->vert.y / 2.0) + camera->w.y;
	ret.z = camera->orig.z - (camera->horiz.z / 2.0) - \
		(camera->vert.z / 2.0) + camera->w.z;
	return (ret);
}

static t_camera	camera(t_vec orig, t_vec dir, double fov, double aspect_ratio)
{
	t_camera	ret;
	double		h;
	double		viewport_height;
	double		viewport_width;
	t_vec		vup;

	if (dir.x == 0.0 && dir.y == 0.0 && dir.z == 0.0)
		dir = vec(0, 0, 1);
	h = tan(deg_to_rad(fov) / 2.0);
	viewport_height = 2.0 * h;
	viewport_width = aspect_ratio * viewport_height;
	vup = vec(0, 1, 0);
	if (dir.x == 0.0 && dir.y != 0.0 && dir.z == 0.0)
		vup = vec(0, 0, 1);
	ret.w = unit(dir);
	ret.u = unit(cross(vup, ret.w));
	ret.v = cross(ret.w, ret.u);
	ret.orig = orig;
	ret.horiz = v_mul(ret.u, viewport_width);
	ret.vert = v_mul(ret.v, viewport_height);
	ret.lower_left = lower_left_corner(&ret);
	return (ret);
}

int	set_camera(t_scene *scene, char **split)
{
	t_vec	dir;
	double	fov;

	dir = stov(split[2]);
	if (dir.x == 0.0 && dir.y == 0.0 && dir.z == 0.0)
		return (1);
	fov = atod(split[3]);
	if (vec_range(&dir, -1.0, 1.0) || double_range(&fov, 0.0, 180.0))
		return (1);
	scene->camera = camera(stov(split[1]), dir, fov, 16.0 / 9.0);
	return (0);
}
