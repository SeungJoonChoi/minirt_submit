#include "minirt.h"

t_image image(int width, int height)
{
    t_image ret;

    ret.image_width = width;
    ret.image_height = height;
    ret.aspect_ratio = (double)width / (double)height;
    return (ret);
}