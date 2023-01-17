/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjoon <seungjoon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 19:06:14 by seungjoon         #+#    #+#             */
/*   Updated: 2023/01/17 18:59:38 by seungjoon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_EXIT		17
# define KEY_ESC			53

//object
# define SP 0
# define PL 1
# define CY 2
//light
# define POINT 0

# define SHININESS 128 //shininess value of object
# define SPECULAR_INTENSITY 0.5
# define LUMEN 3; //light_ratio * LUMEN
# define SHADOW_BIAS __FLT_EPSILON__

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		pixel_bits;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_data	data;
}	t_vars;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef t_vec	t_color;

typedef struct s_ray
{
	t_vec	o;
	t_vec	d;
}	t_ray;

typedef struct s_image
{
	double	aspect_ratio;
	int		image_width;
	int		image_height;
}	t_image;

typedef struct s_camera
{
	t_vec	orig;
	t_vec	w;
	t_vec	u;
	t_vec	v;
	t_vec	horiz;
	t_vec	vert;
	t_vec	lower_left;
}	t_camera;

typedef struct s_hit_record
{
	t_vec	p;
	t_vec	n;
	double	t_min;
	double	t_max;
	double	t;
	int		front_face;
	t_color	albedo;
}	t_hit_record;

typedef struct s_sphere
{
	t_vec	o;
	double	r;
	t_color	albedo;
}	t_sphere;

typedef struct s_plane
{
	t_vec	o;
	t_vec	d;
	t_color	albedo;
}	t_plane;

typedef struct s_cylinder
{
	t_vec	o;
	t_vec	d;
	double	r;
	double	half_h;
	t_color	albedo;
}	t_cylinder;

typedef struct s_cy_calc
{
	double	root;
	double	h;
}	t_cy_calc;

typedef struct s_obj
{
	int				type;
	void			*element;
	struct s_obj	*next;
}	t_obj;

typedef struct s_light
{
	t_vec	orig;
	t_color	color;
	double	intensity;
}	t_light;

typedef struct s_scene
{
	t_image					image;
	t_camera				camera;
	t_obj					world;
	t_obj					light;
	t_color					ambient;
	t_ray					ray;
	t_hit_record			rec;
}	t_scene;

typedef struct s_compo
{
	char			**split_line;
	struct s_compo	*next;
}	t_compo;

//vec1.c
t_vec		vec(double x, double y, double z);
t_vec		v_sum(t_vec vec1, t_vec vec2);
t_vec		v_sub(t_vec vec1, t_vec vec2);
t_vec		v_mul(t_vec vec, double t);
t_vec		v_div(t_vec vec, double t);
//vec2.c
double		dot(t_vec vec1, t_vec vec2);
t_vec		cross(t_vec vec1, t_vec vec2);
double		len_pow(t_vec vec);
double		len(t_vec vec);
t_vec		unit(t_vec vec);
//vec3.c
t_vec		limit(t_vec vec, t_vec limit);
t_vec		mul_v(t_vec vec1, t_vec vec2);
t_vec		sum_t(t_vec vec, double t);
//ray.c
t_ray		ray_set(t_vec *origin, t_vec *direction);
t_vec		ray_at(t_ray *ray, double t);
t_ray		ray_viewport(t_scene *scene, double u, double v);
//camera.c
int			set_camera(t_scene *scene, char **split);
//image.c
t_image		image(int width, int height);
void		image_put(t_vars *vars, t_scene *scene);
//color.c
t_color		color(double r, double g, double b);
t_color		ray_color(t_scene *scene);
//mlx_utils.c
void		set_mlx(t_vars *vars, t_scene *scene);
int			rgb_to_int(double trans, t_vec *color);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
//sphere.c
t_sphere	*sphere(t_vec origin, double radius, t_color albedo);
int			hit_sphere(t_ray *ray, t_sphere *sphere, t_hit_record *rec);
//hit.c
void		set_face_normal(t_ray *ray, t_hit_record *rec);
int			hit(t_ray *ray, t_obj *head, t_hit_record *rec);
//obj_list.c
void		obj_list_init(t_obj *head);
int			obj_add(t_obj *head, int type, void *object);
void		obj_clear(t_obj *head);
void		minirt_clear(t_scene *scene, t_compo *compo);
//scene.c
t_vec		stov(char *str);
t_vec		ctov(char *str);
void		scene_init(t_scene *scene, t_compo *compo);
//light1.c
t_light		*point_light(t_vec orig, t_color color, double ratio);
t_color		phong_lighting(t_scene *scene);
//light2.c
t_color		get_specular(t_scene *scene, t_light *light, t_vec *light_dir);
t_color		get_diffuse(t_scene *scene, t_light *light, t_vec *light_dir);
//plane.c
t_plane		*plane(t_vec origin, t_vec dir, t_color albedo);
int			hit_plane(t_ray *ray, t_plane *plane, t_hit_record *rec);
//cylinder.c
t_cylinder	*cylinder(char **e);
int			hit_cylinder(t_ray *ray, t_cylinder *cylinder, t_hit_record *rec);
//utils.c
double		atod(const char *str);
void		free_strs(char **strs);
//exit.c
void		exit_err(char *msg);
void		exit_compo_clear(t_compo *head, char *msg);
//compo_list.c
void		compo_list_init(t_compo *head);
int			compo_add(t_compo *head, char **split);
void		compo_clear(t_compo *head);
//file1.c
void		ele_form_check(t_compo *head);
void		set_compo(t_compo *compo, int fd);
//file2.c
int			invalid_double(char *number);
int			invalid_vec(char *vec);
int			vec_range(t_vec *vec, double min, double max);
int			double_range(double *d, double min, double max);
//file3.c
void		check_a(t_compo *head, char **split);
void		check_c(t_compo *head, char **split);
void		check_l_sp(t_compo *head, char **split);
void		check_pl(t_compo *head, char **split);
void		check_cy(t_compo *head, char **split);

#endif
