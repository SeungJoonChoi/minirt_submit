#include "minirt.h"

/*
구의 방정식 x^2 + y^2 + z^2 = r^2
-> (x - C.x)^2 + (y - C.y)^2 + (z - C.z)^2 = r^2 (C는 구의 중심)
-> (P - C) * (P - C) = r^2 (P는 구위의 임의의 좌표)
-> |(P - C)|^2 = r^2
직선의 방정식 A + t*b (A원점 b방향벡터)
-> |(A + tb - C)|^2 = r^2
-> (b*b)t^2 + 2b*(A-C)t + (A-C)*(A-C) - r^2 = 0
짝수판별식 (b/2)^2 -ac
b가 단위벡터라고 가정하면
a = 1
b/2 = b*(A-C)
c = (A-C)*(A-C) - r^2
판별식이 양수일때만 픽셀의 색을 구해옴

!! b를 단위벡터라고 가정하고 쓰려면 ray.dir을 모두 단위벡터로 초기화 해야함
*/

// int hit_sphere(t_vec center, double radius, t_ray ray)
// {
//     t_vec oc;
//     t_vec unit_ray;
//     double b;
//     double c;
//     double discriminant;

//     oc = vec_sub(ray.orig, center);
//     unit_ray = vec_unit(ray.dir);
//     b = vec_dot(unit_ray, oc);
//     c = vec_dot(oc, oc) - (radius * radius);
//     discriminant = b * b - c;
//     if (discriminant >= 0)
//         return (1);
//     return (0);
// }

// double hit_sphere(t_vec center, double radius, t_ray ray)
// {
//     t_vec oc;
//     double half_b;
//     double c;
//     double discriminant;

//     oc = vec_sub(ray.orig, center);
//     half_b = vec_dot(ray.dir, oc);
//     c = length_squared(oc) - (radius * radius);
//     discriminant = (half_b * half_b) - c;
//     if (discriminant < 0)
//         return (0);
//     else
//         return (-half_b - sqrt(discriminant));
// }

t_sphere *sphere(t_vec origin, double radius, t_color albedo)
{
    t_sphere *new;

    new = (t_sphere*)malloc(sizeof(t_sphere));
    new->orig = origin;
    new->rad = radius;
    new->albedo = albedo;
    return (new);
}



int hit_sphere(t_ray *ray, t_sphere *sphere, t_hit_record *rec)
{
    t_vec oc;
    double half_b;
    double c;
    double discriminant;
    double sqrtd;
    double root;

    oc = vec_sub(ray->orig, sphere->orig);
    half_b = vec_dot(ray->dir, oc);
    c = length_squared(oc) - (sphere->rad * sphere->rad);
    discriminant = (half_b * half_b) - c;
    if (discriminant < 0)
        return (0);
    sqrtd = sqrt(discriminant);
    root = -half_b - sqrtd;
    /*
    가장 가까운 t(root)값을 구하기 위해 hit했다면 t_max를 t로 줄여주고
    이후에 만나는 오브젝트마다 검사해준다.
    */
    if (root < rec->t_min || root > rec->t_max)
    {
        root = -half_b + sqrtd;
        if (root < rec->t_min || root > rec->t_max)
            return (0);
    }
    //hit_record 업데이트
    rec->t = root;
    rec->t_max = rec->t; //충돌했다면 t_max 업데이트
    rec->p = ray_at(ray, root); //충돌한 정점좌표
    rec->normal = vec_div(vec_sub(rec->p, sphere->orig), sphere->rad);
    //법선벡터는 (C - A)의 단위벡터
    rec->albedo = sphere->albedo;
    //albedo 반사율은 모든 빛의 양을 구하고 반사율에 곱해서 최종적인 색을 결정한다.
    
    return (1);
}