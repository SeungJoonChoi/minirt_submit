#include "minirt.h"

int vec_range(t_vec* vec, double min, double max)
{
    if (vec->x < min || vec->x > max || vec->y < min || \
    vec->y > max || vec->z < min || vec->z > max)
        return (1);
    return (0);
}

int double_range(double* d, double min, double max)
{
    if (*d < min || *d > max)
        return (1);
    return (0);
}

int set_ambient(t_scene *scene, char **split)
{
    t_vec rgb;
    double ratio;

    rgb = ctov(split[2]);
    ratio = atod(split[1]);

    if (vec_range(&rgb, 0.0, 1.0) || double_range(&ratio, 0.0, 1.0))
        return (1);
    scene->ambient = v_mul(rgb, ratio);
    return (0);
}

int set_camera(t_scene *scene, char **split)
{
    t_vec dir;
    double fov;

    dir = stov(split[2]);
    fov = atod(split[3]);
    if (vec_range(&dir, -1.0, 1.0) || double_range(&fov, 0.0, 180.0))
        return (1);
    scene->camera = camera(stov(split[1]), dir, fov, 16.0 / 9.0);
    return (0);
}