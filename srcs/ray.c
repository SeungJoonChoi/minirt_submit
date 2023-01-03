#include "minirt.h"

t_ray ray_set(t_vec *origin, t_vec* direction)
{
    t_ray ret;

    ret.o = *origin;
    ret.d = unit(*direction);
    return (ret);
}

t_vec ray_at(t_ray *ray, double t)
{
    t_vec ret;

    ret.x = ray->o.x + ray->d.x * t;
    ret.y = ray->o.y + ray->d.y * t;
    ret.z = ray->o.z + ray->d.z * t;
    return (ret);
}

t_ray ray_viewport(t_scene *scene, double u, double v)
{
    t_ray ret;
    t_camera *c;

    c = &scene->camera;
    ret.o = c->orig;
    ret.d.x = c->lower_left_corner.x + u * c->horizontal.x + \
    v * c->vertical.x - c->orig.x;
    ret.d.y = c->lower_left_corner.y + u * c->horizontal.y + \
    v * c->vertical.y - c->orig.y;
    ret.d.z = c->lower_left_corner.z + u * c->horizontal.z + \
    v * c->vertical.z - c->orig.z;
    ret.d = unit(ret.d);
    scene->rec.t_max = INFINITY;
    scene->rec.t_min = 0.0;
    return (ret);
}