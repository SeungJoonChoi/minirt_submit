#include "minirt.h"

void set_face_normal(t_ray *ray, t_hit_record *rec)
{
    rec->front_face = dot(ray->d, rec->n) < 0;
    if (!rec->front_face)
        rec->n = v_mul(rec->n, -1.0);
}

static int hit_obj(t_ray *ray, t_obj *obj, t_hit_record *rec)
{
    if (obj->type == SPHERE)
        return (hit_sphere(ray, obj->element, rec));
    else if (obj->type == PLANE)
        return (hit_plane(ray, obj->element, rec));
    else if (obj->type == CYLINDER)
        return (hit_cylinder(ray, obj->element, rec));
    return (0);
}

int hit(t_ray *ray, t_obj *head, t_hit_record *rec)
{
    t_obj *cur;
    int hit_flag;

    hit_flag = 0;
    cur = head->next;
    while (cur != NULL)
    {
        if (hit_obj(ray, cur, rec))
            hit_flag = 1;
        cur = cur->next;
    }
    set_face_normal(ray, rec);
    return (hit_flag);
}