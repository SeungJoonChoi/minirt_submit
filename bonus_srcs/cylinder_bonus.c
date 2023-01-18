/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjoon <seungjoon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:22:48 by seungjoon         #+#    #+#             */
/*   Updated: 2023/01/17 13:52:33 by seungjoon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_cylinder	*cylinder(char **e)
{
	t_cylinder	*new;
	t_vec		dir;
	t_color		albedo;

	dir = stov(e[2]);
	if (dir.x == 0.0 && dir.y == 0.0 && dir.z == 0.0)
		return (NULL);
	albedo = ctov(e[5]);
	if (vec_range(&dir, -1.0, 1.0) || vec_range(&albedo, 0.0, 1.0))
		return (NULL);
	new = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (new == NULL)
		return (NULL);
	new->o = stov(e[1]);
	if (dir.x == 0.0 && dir.y == 0.0 && dir.z == 0.0)
		dir = vec(0, 1, 0);
	new->d = unit(dir);
	new->r = atod(e[3]) * 0.5;
	new->half_h = atod(e[4]) * 0.5;
	new->albedo = albedo;
	return (new);
}

static int	circle_root(t_ray *ray, t_cylinder *cy, double *root)
{
	t_vec	c;
	t_vec	oc;

	c = v_sum(cy->o, v_mul(cy->d, cy->half_h));
	oc = v_sub(c, ray->o);
	*root = dot(unit(oc), cy->d) / dot(ray->d, cy->d);
	*root *= len(oc);
	if (len(v_sub(ray_at(ray, *root), c)) > cy->r)
		return (0);
	return (1);
}

static int	hit_circle(t_ray *ray, t_cylinder *cy, t_hit_record *rec)
{
	double	parallel;
	double	root;

	parallel = dot(ray->d, cy->d);
	if (parallel == 0)
		return (0);
	if (parallel > 0)
		cy->d = v_mul(cy->d, -1);
	if (!circle_root(ray, cy, &root) || \
			root < rec->t_min || root > rec->t_max)
	{
		cy->d = v_mul(cy->d, -1);
		if (!circle_root(ray, cy, &root) || \
				root < rec->t_min || root > rec->t_max)
			return (0);
	}
	rec->p = ray_at(ray, root);
	rec->t = root;
	rec->t_max = rec->t;
	rec->n = cy->d;
	rec->albedo = cy->albedo;
	return (1);
}

static int	cylinder_root(t_ray *ray, t_cylinder *cy, \
		t_hit_record *rec, t_cy_calc *calc)
{
	double	a;
	double	half_b;
	double	c;

	a = len_pow(cross(ray->d, cy->d));
	half_b = dot(cross(ray->d, cy->d), cross(v_sub(ray->o, cy->o), cy->d));
	c = len_pow(cross(v_sub(ray->o, cy->o), cy->d)) - (cy->r * cy->r);
	if ((half_b * half_b) - (a * c) < 0)
		return (0);
	else
	{
		calc->root = (-half_b - sqrt((half_b * half_b) - (a * c))) / a;
		if (calc->root < rec->t_min || calc->root > rec->t_max)
		{
			calc->root = (-half_b + sqrt((half_b * half_b) - (a * c))) / a;
			if (calc->root < rec->t_min || calc->root > rec->t_max)
				return (0);
		}
		calc->h = sqrt(len_pow(v_sub(ray_at(ray, calc->root), \
						cy->o)) - (cy->r * cy->r));
		if (calc->h > cy->half_h)
			return (0);
	}
	return (1);
}

int	hit_cylinder(t_ray *ray, t_cylinder *cy, t_hit_record *rec)
{
	t_cy_calc	calc;
	t_vec		f;
	int			ret;

	ret = 0;
	if (cylinder_root(ray, cy, rec, &calc))
	{
		ret = 1;
		rec->p = ray_at(ray, calc.root);
		rec->t = calc.root;
		rec->t_max = rec->t;
		if (dot(v_sub(rec->p, cy->o), cy->d) < 0)
			calc.h *= -1;
		f = v_sum(cy->o, v_mul(cy->d, calc.h));
		rec->n = v_div(v_sub(rec->p, f), cy->r);
		rec->albedo = cy->albedo;
	}
	if (hit_circle(ray, cy, rec))
		ret = 1;
	return (ret);
}
