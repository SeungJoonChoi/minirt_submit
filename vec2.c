#include "minirt.h"

double vec_dot(t_vec vec1, t_vec vec2)
{
    return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

t_vec vec_cross(t_vec vec1, t_vec vec2)
{
    t_vec ret;

    ret.x = vec1.y * vec2.z - vec1.z * vec2.y;
    ret.y = vec1.z * vec2.x - vec1.x * vec2.z;
    ret.z = vec1.x * vec2.y - vec1.y * vec2.x;
    return (ret);
}

double length_squared(t_vec vec)
{
    return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

double vec_length(t_vec vec)
{
    return (sqrt(length_squared(vec)));
}

t_vec vec_unit(t_vec vec)
{
    t_vec ret;
    double length;

    length = vec_length(vec);
    ret.x = vec.x / length;
    ret.y = vec.y / length;
    ret.z = vec.z / length;
    return (ret);
}