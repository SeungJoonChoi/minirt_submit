#include "minirt.h"

void set_face_normal(t_ray *ray, t_hit_record *rec)
{
    rec->front_face = vec_dot(ray->dir, rec->normal) < 0;
    //카메라와 정면으로 마주보고 있는지 기록해둠
    if (!rec->front_face)
        rec->normal = vec_mul(rec->normal, -1.0);
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

    hit_flag = 0; //맞았는지 확인
    cur = head->next;
    // rec->t_min = 0; //가시거리의 최소값
    // rec->t_max = INFINITY; //가시거리의 최댓값
    while (cur != NULL)
    {
        if (hit_obj(ray, cur, rec)) //오브젝트에 맞았다면 rec에 기록하고 1을 반환
            hit_flag = 1;
        cur = cur->next;
    }

    set_face_normal(ray, rec);
    //카메라가 충돌면의 뒷면을 보고 있다면 방향을 카메라쪽으로 바꿔줘야함(법선벡터의 방향을 바꿔줌)
    return (hit_flag);
}