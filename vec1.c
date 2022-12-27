#include "minirt.h"

t_vec vec(double x, double y, double z)
{
    t_vec ret;
    
    ret.x = x;
    ret.y = y;
    ret.z = z;
    return (ret);
}

t_vec vec_sum(t_vec vec1, t_vec vec2)
{
    t_vec ret;

    ret.x = vec1.x + vec2.x;
    ret.y = vec1.y + vec2.y;
    ret.z = vec1.z + vec2.z;
    return (ret);
}

t_vec vec_sub(t_vec vec1, t_vec vec2)
{
    t_vec ret;

    ret.x = vec1.x - vec2.x;
    ret.y = vec1.y - vec2.y;
    ret.z = vec1.z - vec2.z;
    return (ret);
}

t_vec vec_mul(t_vec vec, double t)
{
    t_vec ret;

    ret.x = vec.x * t;
    ret.y = vec.y * t;
    ret.z = vec.z * t;
    return (ret);
}

t_vec vec_div(t_vec vec, double t)
{
    t_vec ret;

    ret.x = vec.x / t;
    ret.y = vec.y / t;
    ret.z = vec.z / t;
    return (ret);
}