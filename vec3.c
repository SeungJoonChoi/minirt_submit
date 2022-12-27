#include "minirt.h"

t_vec vec_limit(t_vec vec, t_vec limit)
{
    t_vec ret;

    if (vec.x > limit.x)
        ret.x = limit.x;
    else
        ret.x = vec.x;
    if (vec.y > limit.y)
        ret.y = limit.y;
    else
        ret.y = vec.y;
    if (vec.z > limit.z)
        ret.z = limit.z;
    else
        ret.z = vec.z;
    return (ret);
}

t_vec vec_mul_v(t_vec vec1, t_vec vec2)
{
    t_vec ret;

    ret.x = vec1.x * vec2.x;
    ret.y = vec1.y * vec2.y;
    ret.z = vec1.z * vec2.z;
    return (ret);
}

t_vec vec_sum_t(t_vec vec, double t)
{
    t_vec ret;

    ret.x = vec.x + t;
    ret.y = vec.y + t;
    ret.z = vec.z + t;
    return (ret);
}