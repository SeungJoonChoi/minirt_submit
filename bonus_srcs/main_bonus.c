/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjoon <seungjoon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 21:04:43 by seungjoon         #+#    #+#             */
/*   Updated: 2023/01/17 13:53:00 by seungjoon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static int	key_press(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

static int	quit_window(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}

static void	extension_check(char *filename)
{
	char	*temp;

	temp = ft_strnstr(filename, ".rt", ft_strlen(filename));
	if (temp == NULL || ft_strlen(temp) > 3)
		exit_err("Invalid filename extension.");
}

static int	open_file(char *filename)
{
	int	fd;

	extension_check(filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_err("Can not open file.");
	return (fd);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_scene	scene;
	t_compo	compo;
	int		fd;

	if (argc != 2)
		exit_err("Invalid number of arguments.");
	fd = open_file(argv[1]);
	set_compo(&compo, fd);
	close(fd);
	ele_form_check(&compo);
	scene_init(&scene, &compo);
	set_mlx(&vars, &scene);
	image_put(&vars, &scene);
	minirt_clear(&scene, &compo);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.data.img, 0, 0);
	mlx_hook(vars.win, X_EVENT_KEY_PRESS, 0, &key_press, &vars);
	mlx_hook(vars.win, X_EVENT_KEY_EXIT, 0, &quit_window, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
