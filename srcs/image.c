/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjoon <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:59:37 by seungjoon         #+#    #+#             */
/*   Updated: 2023/01/05 21:00:17 by seungjoon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_image	image(int width, int height)
{
	t_image	ret;

	ret.image_width = width;
	ret.image_height = height;
	ret.aspect_ratio = (double)width / (double)height;
	return (ret);
}

void	image_put(t_vars *vars, t_scene *scene)
{
	t_color	pixel_color;
	int		i;
	int		j;
	double	u;
	double	v;

	j = scene->image.image_height - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < scene->image.image_width)
		{
			u = (double)i / (double)(scene->image.image_width - 1);
			v = (double)j / (double)(scene->image.image_height - 1);
			scene->ray = ray_viewport(scene, u, v);
			pixel_color = ray_color(scene);
			my_mlx_pixel_put(&vars->data, i, scene->image.image_height - 1 - j, \
					rgb_to_int(0.0, &pixel_color));
			++i;
		}
		--j;
	}
}
