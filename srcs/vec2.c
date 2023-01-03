#include "minirt.h"

double dot(t_vec vec1, t_vec vec2)
{
    return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

t_vec cross(t_vec vec1, t_vec vec2)
{
    t_vec ret;

    ret.x = vec1.y * vec2.z - vec1.z * vec2.y;
    ret.y = vec1.z * vec2.x - vec1.x * vec2.z;
    ret.z = vec1.x * vec2.y - vec1.y * vec2.x;
    return (ret);
}

double len_pow(t_vec vec)
{
    return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

double len(t_vec vec)
{
    return (sqrt(len_pow(vec)));
}

t_vec unit(t_vec vec)
{
    t_vec ret;
    double length;

    length = len(vec);
    ret.x = vec.x / length;
    ret.y = vec.y / length;
    ret.z = vec.z / length;
    return (ret);
}