#include "minirt.h"

t_color color(double r, double g, double b)
{
    t_color ret;

    ret.x = r;
    ret.y = g;
    ret.z = b;
    return (ret);
}

t_color ray_color(t_scene *scene)
{
    double t;

    if (hit(&scene->ray, &scene->world, &scene->rec))
        return (phong_lighting(scene));
    t = 0.5 * (scene->ray.d.y + 1.0);
    return (vec(1.0 - (0.5 * t), 1.0 - (0.3 * t), 1.0));
}