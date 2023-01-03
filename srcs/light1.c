#include "minirt.h"

t_light *point_light(t_vec orig, t_color color, double intensity)
{
    t_light *new;

    new = (t_light*)malloc(sizeof(t_light));
    new->orig = orig;
    new->color = color;
    new->intensity = intensity;
    return (new);
}

static int in_shadow(t_scene *scene, t_light *light)
{
    t_ray light_ray;
    double light_len;
    t_hit_record rec;

    light_ray.d = unit(v_sub(light->orig, scene->rec.p));
    light_ray.o = v_sum(scene->rec.p, v_mul(scene->rec.n, SHADOW_BIAS));
    light_len = len(v_sub(light->orig, scene->rec.p));
    rec.t_max = light_len;
    rec.t_min = 0.0;
    if (hit(&light_ray, &scene->world, &rec))
        return (1);
    return (0);
}

static t_color point_light_get(t_scene *scene, t_light *light)
{
    t_vec light_dir;
    t_color diffuse;
    t_color specular;
    double brightness;

    if (in_shadow(scene, light))
        return (color(0, 0, 0));
    light_dir = unit(v_sub(light->orig, scene->rec.p));
    diffuse = get_diffuse(scene, light, &light_dir);
    specular = get_specular(scene, light, &light_dir);
    brightness = light->intensity * LUMEN;
    return (v_mul(v_sum(diffuse, specular), brightness));
}

t_color phong_lighting(t_scene *scene)
{
    t_color l_color;
    t_obj *light;

    l_color = color(0, 0, 0);
    light = scene->light.next;
    while (light)
    {
        l_color = v_sum(l_color, point_light_get(scene, light->element));
        light = light->next;
    }
    l_color = v_sum(l_color, scene->ambient);
    return (limit(mul_v(l_color, scene->rec.albedo), color(1, 1, 1)));
}