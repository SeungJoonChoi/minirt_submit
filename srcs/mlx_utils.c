/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjoon <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 21:06:08 by seungjoon         #+#    #+#             */
/*   Updated: 2023/01/05 21:08:04 by seungjoon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_mlx(t_vars *vars, t_scene *scene)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, scene->image.image_width, \
			scene->image.image_height, "seunchoi_minirt");
	vars->data.img = mlx_new_image(vars->mlx, scene->image.image_width, \
			scene->image.image_height);
	vars->data.addr = mlx_get_data_addr(vars->data.img, &vars->data.pixel_bits, \
			&vars->data.line_length, &vars->data.endian);
}

int	rgb_to_int(double trans, t_vec *color)
{
	int	t;
	int	r;
	int	g;
	int	b;

	t = trans * 255.999;
	r = color->x * 255.999;
	g = color->y * 255.999;
	b = color->z * 255.999;
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->pixel_bits / 8));
	*(unsigned int *)dst = color;
}
