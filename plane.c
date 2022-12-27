#include "minirt.h"

/*
평면의 방정식 
ax + by + cz + d = 0 (d는 상수)

평면의 법선벡터와 ray의 방향벡터가 수직이라면 
ray가 평행하게 지나기 때문에 교점을 구하지 않는다.
둘을 내적해서 0이 나온다면 평행 (plane.n * ray.dir = 0)

ax + by + cz + d = 0 (a,b,c는 법선벡터의 성분, d는 상수)
-> (n * P) + d = 0 (P는 평면위의 점 -> plane.orig를 사용함)
-> d = -(n * P)

ax + by + cz + d = 0
n * (A + tb) + d = 0
n * (A + tb) = -d
n * (A + tb) = n * P
(n * A) + (n * tb) = n * P
t = ((n * P) - (n * A)) / (n * b);
-> n * b는 평행한지 확인하는 식에서 미리 값을 구해놓음.

*/

t_plane *plane(t_vec origin, t_vec dir, t_color albedo)
{
    t_plane *new;

    new = (t_plane*)malloc(sizeof(t_plane));
    new->orig = origin;
    new->dir = vec_unit(dir);
    new->albedo = albedo;
    return (new);
}

int hit_plane(t_ray *ray, t_plane *plane, t_hit_record *rec)
{
    double parallel;
    double root;

    parallel = vec_dot(plane->dir, ray->dir);
    if (parallel == 0)
        return (0);
    root = (vec_dot(plane->dir, plane->orig) - vec_dot(plane->dir, ray->orig)) / parallel;
    if (root < rec->t_min || root > rec->t_max)
        return (0);
    rec->t = root;
    rec->t_max = rec->t;
    rec->p = ray_at(ray, root);
    rec->normal = plane->dir; // 검증
    rec->albedo = plane->albedo;

    return (1);
}