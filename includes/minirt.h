#ifndef MINIRT_H
#define MINIRT_H

#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)

#include "mlx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_EXIT		17
# define KEY_ESC			53

//object
#define SPHERE 0
#define PLANE 1
#define CYLINDER 2
//light
#define POINT 0

#define SHININESS 128 //shininess value of object
#define SPECULAR_INTENSITY 0.5
#define LUMEN 3; //light_ratio * LUMEN
#define SHADOW_BIAS __FLT_EPSILON__

typedef struct s_vars
{
    void *mlx;
    void *win;
} t_vars;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_data;

typedef struct s_vec
{
    double x;
    double y;
    double z;
} t_vec;

typedef t_vec t_color;

typedef struct s_ray
{
    t_vec orig;
    t_vec dir;
} t_ray;

typedef struct s_image
{
    double aspect_ratio;
    int image_width;
    int image_height;
} t_image;

typedef struct s_camera
{
    t_vec orig;
    t_vec w;
    t_vec u;
    t_vec v;
    t_vec horizontal;
    t_vec vertical;
    t_vec lower_left_corner;
} t_camera;

typedef struct s_hit_record
{
    t_vec p;
    t_vec normal;
    double t_min;
    double t_max;
    double t;
    int front_face;
    t_color albedo;
} t_hit_record;

typedef struct s_sphere
{
    t_vec orig;
    double rad;
    t_color albedo;
} t_sphere;

typedef struct s_plane
{
    t_vec orig;
    t_vec dir;
    t_color albedo;
} t_plane;

typedef struct s_cylinder
{
    t_vec orig;
    t_vec dir;
    double rad;
    double half_h;
    t_color albedo;
} t_cylinder;

typedef struct s_obj
{
    int type;
    void *element;
    struct s_obj *next;
} t_obj;

typedef struct s_light
{
    t_vec orig;
    t_color color;
    double intensity;
} t_light;

typedef struct s_scene
{
    t_image image;
    t_camera camera;
    t_obj world;
    t_obj light;
    t_color ambient;
    t_ray ray;
    t_hit_record rec;
} t_scene;

//vec1.c
t_vec vec(double x, double y, double z);
t_vec vec_sum(t_vec vec1, t_vec vec2);
t_vec vec_sub(t_vec vec1, t_vec vec2);
t_vec vec_mul(t_vec vec, double t);
t_vec vec_div(t_vec vec, double t);
//vec2.c
double vec_dot(t_vec vec1, t_vec vec2);
t_vec vec_cross(t_vec vec1, t_vec vec2);
double length_squared(t_vec vec);
double vec_length(t_vec vec);
t_vec vec_unit(t_vec vec);
//vec3.c
t_vec vec_limit(t_vec vec, t_vec limit);
t_vec vec_mul_v(t_vec vec1, t_vec vec2);
t_vec vec_sum_t(t_vec vec, double t);
//ray.c
t_ray ray_set(t_vec *origin, t_vec* direction);
t_vec ray_at(t_ray *ray, double t);
t_ray ray_viewport(t_scene *scene, double u, double v);
//camera.c
t_vec lower_left_corner(t_camera *camera);
t_camera camera(t_vec orig, t_vec dir, double fov, double aspect_ratio);
//image.c
t_image image(int width, int height);
//color.c
t_color color(double r, double g, double b);
t_color ray_color(t_scene *scene);
//mlx_utils.c
int rgb_to_int(double trans, t_vec *color);
void my_mlx_pixel_put(t_data *data, int x, int y, int color);
//sphere.c
t_sphere *sphere(t_vec origin, double radius, t_color albedo);
int hit_sphere(t_ray *ray, t_sphere *sphere, t_hit_record *rec);
//hit.c
void set_face_normal(t_ray *ray, t_hit_record *rec);
int hit(t_ray *ray, t_obj *head, t_hit_record *rec);
//obj_list.c
void obj_list_init(t_obj *head);
void obj_add(t_obj *head, int type, void *object);
void obj_clear(t_obj *head);
//scene.c
t_scene scene_init(t_image img, t_camera cam, double ambient_ratio, t_color ambient_color);
//light.c
t_light *point_light(t_vec orig, t_color color, double ratio);
t_color phong_lighting(t_scene *scene);
t_color point_light_get(t_scene *scene, t_light *light);
//plane.c
t_plane *plane(t_vec origin, t_vec dir, t_color albedo);
int hit_plane(t_ray *ray, t_plane *plane, t_hit_record *rec);
//cylinder.c
t_cylinder *cylinder(t_vec origin, t_vec dir, double diameter, double height, t_color albedo);
int hit_cylinder(t_ray *ray, t_cylinder *cylinder, t_hit_record *rec);
int hit_circle(t_ray *ray, t_cylinder *cylinder, t_hit_record *rec);

#endif