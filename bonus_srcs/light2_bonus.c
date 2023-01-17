/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjoon <seungjoon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 21:02:44 by seungjoon         #+#    #+#             */
/*   Updated: 2023/01/17 13:52:58 by seungjoon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static t_vec	reflect(t_vec light_dir, t_vec normal)
{
	t_vec	ret;
	t_vec	a;
	double	n;

	n = dot(light_dir, normal);
	a = v_mul(normal, n);
	ret = v_sum(v_sum(v_mul(light_dir, -1), a), a);
	return (ret);
}

t_color	get_specular(t_scene *scene, t_light *light, t_vec *light_dir)
{
	t_color	specular;
	t_vec	reflect_dir;
	double	spec;
	double	ksn;
	double	ks;

	reflect_dir = reflect(*light_dir, scene->rec.n);
	reflect_dir = v_mul(reflect_dir, -1);
	spec = dot(reflect_dir, scene->ray.d);
	if (spec < 0.0)
		spec = 0.0;
	ksn = SHININESS;
	ks = SPECULAR_INTENSITY;
	spec = pow(spec, ksn);
	specular = v_mul(v_mul(light->color, ks), spec);
	return (specular);
}

t_color	get_diffuse(t_scene *scene, t_light *light, t_vec *light_dir)
{
	t_color	diffuse;
	double	kd;

	kd = dot(*light_dir, scene->rec.n);
	if (kd < 0.0)
		kd = 0.0;
	diffuse = v_mul(light->color, kd);
	return (diffuse);
}
