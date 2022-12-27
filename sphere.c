#include "minirt.h"

t_sphere *sphere(t_vec origin, double radius, t_color albedo)
{
    t_sphere *new;

    new = (t_sphere*)malloc(sizeof(t_sphere));
    new->o = origin;
    new->r = radius;
    new->albedo = albedo;
    return (new);
}

static int sphere_root(t_ray *ray, t_sphere *sp, t_hit_record *rec)
{

}

int hit_sphere(t_ray *ray, t_sphere *sp, t_hit_record *rec)
{
    t_vec oc;
    double half_b;
    double c;
    double discriminant;
    double sqrtd;
    double root;

    oc = v_sub(ray->o, sp->o);
    half_b = dot(ray->d, oc);
    c = len_pow(oc) - (sp->r * sp->r);
    discriminant = (half_b * half_b) - c;
    if (discriminant < 0)
        return (0);
    sqrtd = sqrt(discriminant);
    root = -half_b - sqrtd;
    if (root < rec->t_min || root > rec->t_max)
    {
        root = -half_b + sqrtd;
        if (root < rec->t_min || root > rec->t_max)
            return (0);
    }
    rec->t = root;
    rec->t_max = rec->t;
    rec->p = ray_at(ray, root);
    rec->n = v_div(v_sub(rec->p, sp->o), sp->r);
    rec->albedo = sp->albedo;
    return (1);
}