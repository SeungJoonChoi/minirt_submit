#include "minirt.h"

t_cylinder *cylinder(t_vec origin, t_vec dir, double diameter, double height, t_color albedo)
{
    t_cylinder *new;

    new = (t_cylinder*)malloc(sizeof(t_cylinder));
    new->o = origin;
    new->d = unit(dir);
    new->r = diameter * 0.5;
    new->half_h = height * 0.5;
    new->albedo = albedo;
    return (new);
}

static int circle_root(t_ray *ray, t_cylinder *cy, double *root)
{
    t_vec c;
    t_vec oc;

    c = v_sum(cy->o, v_mul(cy->d, cy->half_h));
    oc = v_sub(c, ray->o);
    *root = dot(unit(oc), cy->d) / dot(ray->d, cy->d);
    *root *= len(oc);
    if (len(v_sub(ray_at(ray, *root), c)) > cy->r)
        return (0);
    return (1);
}

static int hit_circle(t_ray *ray, t_cylinder *cy, t_hit_record *rec)
{
    double parallel;
    double root;

    parallel = dot(ray->d, cy->d);
    if (parallel == 0)
        return (0);
    if (parallel > 0)
        cy->d = v_mul(cy->d, -1);
    if (!circle_root(ray, cy, &root) || \
    root < rec->t_min || root > rec->t_max)
    {
        cy->d = v_mul(cy->d, -1);
        if (!circle_root(ray, cy, &root) || \
        root < rec->t_min || root > rec->t_max)
                return (0);
    }
    rec->p = ray_at(ray, root);
    rec->t = root;
    rec->t_max = rec->t;
    rec->n = cy->d;
    rec->albedo = cy->albedo;
    return (1);
}

static int cylinder_root(t_ray *ray, t_cylinder *cy, t_hit_record *rec, double *root, double *h)
{
    double a;
    double half_b;
    double c;
    double discriminant;

    a = len_pow(cross(ray->d, cy->d));
    half_b = dot(cross(ray->d, cy->d), cross(v_sub(ray->o, cy->o), cy->d));
    c = len_pow(cross(v_sub(ray->o, cy->o), cy->d)) - (cy->r * cy->r);
    discriminant = (half_b * half_b) - (a * c);
    if (discriminant < 0)
        return (0);
    else
    {
        *root = (-half_b - sqrt(discriminant)) / a;
        if (*root < rec->t_min || *root > rec->t_max)
        {    
            *root = (-half_b + sqrt(discriminant)) / a;
            if (*root < rec->t_min || *root > rec->t_max)
                return (0);
        }
        *h = sqrt(len_pow(v_sub(ray_at(ray, *root), cy->o)) - (cy->r * cy->r));
        if (*h > cy->half_h)
            return (0);
    }
    return (1);
}

int hit_cylinder(t_ray *ray, t_cylinder *cy, t_hit_record *rec)
{
    double root;
    double h;
    t_vec f;
    int ret;

    ret = 0;
    if (cylinder_root(ray, cy, rec, &root, &h))
    {
        ret = 1;
        rec->p = ray_at(ray, root);
        rec->t = root;
        rec->t_max = rec->t;
        if (dot(v_sub(rec->p, cy->o), cy->d) < 0)
            h *= -1;
        f = v_sum(cy->o, v_mul(cy->d, h));
        rec->n = v_div(v_sub(rec->p, f), cy->r);
        rec->albedo = cy->albedo;
    }
    if (hit_circle(ray, cy, rec))
        ret = 1;;
    return (ret);
}